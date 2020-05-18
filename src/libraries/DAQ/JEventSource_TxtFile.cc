#include "JEventSource_TxtFile.h"

#include "FT/FTCalHit.h"
#include "FT/FTHodoHit.h"
#include <iostream>
#include "JANA/Services/JParameterManager.h"
#include "JANA/Calibrations/JCalibration.h"
#include "JANA/Calibrations/JCalibrationManager.h"

double CRYS_DELTA = 11.5;
double CRYS_WIDTH = 15.3;													  // crystal width in mm
double CRYS_LENGTH = 200.;													  // crystal length in mm
double CRYS_ZPOS = 1898.;

//I am hard-coding the indexes here, since it will always be 8 sectors, 2 layers, 20 components.
double mpx[8][2][20];
double mpy[8][2][20];
double mpz[8][2][20];

double mips_charge[484];
double mips_energy[484];
double fadc_to_charge[484];

int isRead = 0;

JEventSourceTxtFile::JEventSourceTxtFile(std::string res_name, JApplication* app) :
		JEventSource(std::move(res_name), app) {
	idx = 0;
}

//-------------------------------------------------------------------------
// Open
//
// The Open method is called before events are read from this source. You
// could open the file in the constructor, but it is recommended to wait
// until Open is called. This is because JEventSource objects are made at
// the beginning of the job, though not all files will be read right away.
//-------------------------------------------------------------------------
void JEventSourceTxtFile::Open() {

	std::cout << this->GetResourceName() << std::endl;
	file.open(this->GetResourceName().c_str());
	idx = 0;

	//currEventTimeSlice = 0;
	std::cout << "JEventSourceTxtFile creator DONE: " << this << std::endl;

}
//-------------------------------------------------------------------------
// GetEvent
//
// This method is called to read in a single "event"
//-------------------------------------------------------------------------
void JEventSourceTxtFile::GetEvent(std::shared_ptr<JEvent> event) {

	// Create a JEvent object and fill in important info. It is expected that
	// the most common operation will be to read in a buffer and store a pointer
	// to it in the event object. You should not spend much effort here processing
	// the data since this method is called serially. Defer as much as possible
	// to the GetObjects method below which may be called in parallel.
	curRunNumber = 8000;
	event->SetRunNumber(curRunNumber);
	event->SetEventNumber(idx++);

	if (isRead == 0) {

		auto jcalib_manager = japp->GetService<JCalibrationManager>();
		auto jcalib = jcalib_manager->GetJCalibration(event->GetRunNumber());
		std::vector<std::vector<double>> data;
		//Load FT-CAL
		jcalib->Get("/calibration/ft/ftcal/charge_to_energy", data);
		//sector - layer - component - mips_charge - mips_energy - fadc_to_charge
		for (auto row : data) {
			auto component = int(row[2]);
			mips_charge[component-1]=row[3];
			mips_energy[component-1]=row[4];
			fadc_to_charge[component-1]=row[5];
		}

		//Load FT-HODO
		jcalib->Get("/geometry/ft/fthodo", data);
		for (auto row : data) {
			//sector - layer - component - x - y - z - width - thickness
			auto sector = int(row[0]);
			auto layer = int(row[1]);
			auto component = int(row[2]);
			mpx[sector - 1][layer - 1][component - 1] = row[3];
			mpy[sector - 1][layer - 1][component - 1] = row[4];
			mpz[sector - 1][layer - 1][component - 1] = row[5];
		}
		isRead = 1;

	}

	//TODO: allow for a user-defined run number

	std::string line, fields;
	std::getline(file, line);
	if (file.eof()) {
		file.close();
		std::cout << "END" << std::endl;
		throw JEventSource::RETURN_STATUS::kNO_MORE_EVENTS;
	}
	std::istringstream strm(line);

	int N;

	int id, sector, layer, component;
	double adc, tdc;

	FTCalHit *caloHit;
	FTHodoHit *hodoHit;

	strm >> N;
	for (int ii = 0; ii < N; ii++) {
		strm >> fields;
		std::replace(fields.begin(), fields.end(), ':', ' ');  // replace ':' by ' '
		std::istringstream strm2(fields);
		strm2 >> id >> sector >> layer >> component >> adc >> tdc;
		if (id == 0) {
			caloHit = new FTCalHit();
			caloHit->m_channel.sector = sector;
			caloHit->m_channel.layer = layer;
			caloHit->m_channel.component = component;
			caloHit->m_channel.iY = (caloHit->m_channel.component / 22) + 1;
			caloHit->m_channel.iX = (caloHit->m_channel.component + 1) - (caloHit->m_channel.iY - 1) * 22;

			caloHit->setHitEnergy(adc * fadc_to_charge[caloHit->m_channel.component - 1] * mips_energy[caloHit->m_channel.component - 1] / mips_charge[caloHit->m_channel.component  - 1] / 1000.);


			caloHit->setHitTime(tdc);
			caloHit->setHitX((caloHit->m_channel.iX - CRYS_DELTA) * CRYS_WIDTH);
			caloHit->setHitY((caloHit->m_channel.iY - CRYS_DELTA) * CRYS_WIDTH);
			caloHit->setHitZ(CRYS_ZPOS);

			event->Insert(caloHit);
		}
		if (id == 1) {
			hodoHit = new FTHodoHit();
			hodoHit->m_channel.sector = sector;
			hodoHit->m_channel.layer = layer;
			hodoHit->m_channel.component = component;
			hodoHit->setHitEnergy(adc);
			hodoHit->setHitTime(tdc);
			hodoHit->setDx(mpx[hodoHit->m_channel.sector - 1][hodoHit->m_channel.layer - 1][hodoHit->m_channel.component - 1]);
			hodoHit->setDy(mpy[hodoHit->m_channel.sector - 1][hodoHit->m_channel.layer - 1][hodoHit->m_channel.component - 1]);
			hodoHit->setDz(mpz[hodoHit->m_channel.sector - 1][hodoHit->m_channel.layer - 1][hodoHit->m_channel.component - 1]);

			event->Insert(hodoHit);
		}
	}
}

/*
 bool JEventSourceTxtFile::GetObjects(const std::shared_ptr<const JEvent>& aEvent, JFactory* aFactory) {

 //I organized this as follows.
 //From the ptEvent, in principle I can extract the faWaveboardHits and have the JEventSourceTxtFile providing these directly.
 //In the online part (JEventSource_Tridas), I don't do this.
 //The online factory, interacting with the TriDAS, provides directly the TridasEvent,
 //and then there are different factories providing the fadc hits (faWaveboardHit_factory and fa250VTPMode7Hit_factory).
 //

 }
 */
