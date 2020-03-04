#include "JEventSource_PTFile.h"
#include "TRIDAS/s_dataformat_bdx.hpp"
#include <iostream>

JEventSourcePTFile::JEventSourcePTFile(std::string res_name, JApplication* app) :
		JEventSource(std::move(res_name), app), ptReader(0) {

}

//-------------------------------------------------------------------------
// Open
//
// The Open method is called before events are read from this source. You
// could open the file in the constructor, but it is recommended to wait
// until Open is called. This is because JEventSource objects are made at
// the beginning of the job, though not all files will be read right away.
//-------------------------------------------------------------------------
void JEventSourcePTFile::Open() {

	std::cout << this->GetResourceName() << std::endl;
	ptReader = new PtFileReader<sample::uncompressed>(this->GetResourceName());

	//point to the first time slice
	it_ptReader = ptReader->begin();
	nEventsTimeSlice = (*it_ptReader).nEvents();

	//Create a new time slice
	ptTimeSlice = new TimeSlice<sample::uncompressed>(*it_ptReader);
	it_ptTimeSlice = ptTimeSlice->begin();

	//currEventTimeSlice = 0;
	std::cout << "JEventSourcePTFile creator DONE: " << this << std::endl;

}
//-------------------------------------------------------------------------
// GetEvent
//
// This method is called to read in a single "event"
//-------------------------------------------------------------------------
void JEventSourcePTFile::GetEvent(std::shared_ptr<JEvent> event) {

	// Create a JEvent object and fill in important info. It is expected that
	// the most common operation will be to read in a buffer and store a pointer
	// to it in the event object. You should not spend much effort here processing
	// the data since this method is called serially. Defer as much as possible
	// to the GetObjects method below which may be called in parallel.

	if (it_ptTimeSlice == ptTimeSlice->end()) {
		it_ptReader++;
		delete ptTimeSlice;
		//It the iterator on time slices is at the end, the source is completely read.
		if (it_ptReader == ptReader->end()) {
			std::cout << "Source done" << std::endl;
			fflush(stdout);
			throw JEventSource::RETURN_STATUS::kNO_MORE_EVENTS;
		} else {
			nEventsTimeSlice = (*it_ptReader).nEvents();
			ptTimeSlice = new TimeSlice<sample::uncompressed>(*it_ptReader);
			it_ptTimeSlice = ptTimeSlice->begin();
			//currEventTimeSlice = 0;
		}
	}

	curRunNumber = ptReader->runNumber();
	ptEvent = new Event<sample::uncompressed>(*it_ptTimeSlice++);

	//TODO: allow for a user-defined run number
	event->SetRunNumber(curRunNumber);
	event->SetEventNumber(ptEvent->id());
//	event.SetEventTS(ptTimeSlice->id());
//	event->Insert(ptEvent);

	TridasEvent *tridasEvent = new TridasEvent();

	//add the trigger word
	tridasEvent->triggerWords.push_back(tridas::bdx::MAX_TRIGGERS_NUMBER); //currently 5
	for (int ii = 0; ii < tridas::bdx::MAX_TRIGGERS_NUMBER; ii++) {
		tridasEvent->triggerWords.push_back(ptEvent->nseeds(ii));
	}
	tridasEvent->triggerWords.push_back(tridas::bdx::MAX_PLUGINS_NUMBER); //currently 8
	for (int ii = 0; ii < tridas::bdx::MAX_PLUGINS_NUMBER; ii++) {
		tridasEvent->triggerWords.push_back(ptEvent->plugin_nseeds(ii));
	}
	for (int ii = 0; ii < tridas::bdx::MAX_PLUGINS_NUMBER; ii++) {
		tridasEvent->triggerWords.push_back(ptEvent->plugin_trigtype(ii));
	}



	for (Event<sample::uncompressed>::iterator it = ptEvent->begin(); it != ptEvent->end(); ++it) {
		Hit<sample::uncompressed> hit = (*it);	//This is the HIT

		fadcHit fhit;

		fhit.crate = hit.frameHeader(0).TowerID;
		fhit.slot = hit.frameHeader(0).EFCMID;
		fhit.channel = hit.frameHeader(0).PMTID;

		//add the time
		T4nsec t(hit.frameHeader(0).T4ns);
		fhit.time = t;

		//add the charge
		fhit.charge = 0;
		for (int q = 0; q < hit.nFrames(); q++)
			fhit.charge += hit.frameHeader(q).Charge;

		//add the samples
		for (auto it_ptSample = hit.begin(); it_ptSample != hit.end(); it_ptSample++) {
			fhit.data.push_back(*it_ptSample);
		}

		/*	At the moment (2020), TriDAS can be feed by three hardware sources:

		 - Waveboard (V1)
		 - Waveboard (V2)
		 - fa250 stream trough VTP

		 In the future, there may be more than one hit type per event, if the readout architecture is mixed.
		 Ideally, one would recognize the hit type from the hit itself, and have one JANA2 factory per hit - hits may be later processed differently.
		 One can judge this from the crate/slot/channel combination, but this is setup-dependent.
		 For the moment, this is not supported. Hence, for the moment I differentiate between waveboard and fa250 by considering that the fa250 has no samples, only time and charge.
		 */
		if (fhit.data.size() == 0)
			fhit.type = fadcHit_TYPE::FA250VTPMODE7;
		else
			fhit.type = fadcHit_TYPE::WAVEBOARD;

		tridasEvent->hits.push_back(fhit);
	}
	event->Insert(tridasEvent);

	delete ptEvent;
	ptEvent = 0;
}

/*
 bool JEventSourcePTFile::GetObjects(const std::shared_ptr<const JEvent>& aEvent, JFactory* aFactory) {

 //I organized this as follows.
 //From the ptEvent, in principle I can extract the faWaveboardHits and have the JEventSourcePTFile providing these directly.
 //In the online part (JEventSource_Tridas), I don't do this.
 //The online factory, interacting with the TriDAS, provides directly the TridasEvent,
 //and then there are different factories providing the fadc hits (faWaveboardHit_factory and fa250VTPMode7Hit_factory).
 //

 }
 */
