/*
 * faWaveboardHitfactory.cc
 *
 *  Created on: Dec 23, 2019
 *      Author: celentan
 */

#include "FTHodoHit_factory.h"
#include "JANA/JEvent.h"

#include "DAQ/faWaveboardHit.h"
#include "DAQ/fa250VTPMode7Hit.h"
#include "TT/TranslationTable.h"

FTHodoHit_factory::FTHodoHit_factory() {
	// TODO Auto-generated constructor stub
	m_tt = 0;
}

FTHodoHit_factory::~FTHodoHit_factory() {
	// TODO Auto-generated destructor stub
}

void FTHodoHit_factory::Init() {

}
void FTHodoHit_factory::ChangeRun(const std::shared_ptr<const JEvent> &aEvent) {

	//TODO: get the TT
	std::cout << "FTHodoHit_factory::ChangeRun run number: " << aEvent->GetRunNumber() << " " << aEvent->GetEventNumber() << std::endl;
	m_tt = aEvent->GetSingle<TranslationTable>();

}
void FTHodoHit_factory::Process(const std::shared_ptr<const JEvent> &aEvent) {

	TranslationTable::ChannelInfo m_channel;
	TranslationTable::csc_t m_csc;

	//Get the hits from FADC. Support bot the waveboard hit and the fa250VTPMode7 hit
	auto faHits_waveboard = aEvent->Get<faWaveboardHit>();
	auto faHits_fa250VTPMode7 = aEvent->Get<fa250VTPMode7Hit>();

	for (auto faHit : faHits_waveboard) {
		//Add here temporary code to change from the crate-slot-channel in the file I provided to Cristiano to
		//something that is realistic according to the real FT-Hodo geometry

#define TEST_CODE
		//Crate - slot - channel - id - x - y - hodo_sector - hodo_component - hodo_l1_slot - hodo_l1_channel - hodo_l2_slot - hodo_l2_channel
		//{ 70, 6, 5, 61, 17, 2, 7, 3, 6, 1, 6, 14 }  //fake to channel 0
		//{ 70, 6, 6, 83, 17, 3, 7, 4, 5, 0, 5, 9 }   //fake to channel 2
		//{ 70, 5, 14, 82, 16, 3, 7, 7, 5, 1, 5, 8 }   //fake to channel 4
		//{ 70, 5, 15, 60, 16, 2, 7, 6, 18, 3, 18, 9 }//fake to channel 6
#ifdef TEST_CODE
		if (faHit->m_channel.channel <= 6) {
			m_csc.crate = 70;
			switch (faHit->m_channel.channel) {
			case 0:
				m_csc.slot = 6;
				m_csc.channel = 5;
				break;
			case 2:
				m_csc.slot = 6;
				m_csc.channel = 6;
				break;
			case 4:
				m_csc.slot = 5;
				m_csc.channel = 14;
				break;
			case 6:
				m_csc.slot = 5;
				m_csc.channel = 15;
				break;
			}
		} else {
			m_csc.crate = 72; // hodo crate to not have the TT library reporting errors
			m_csc.slot = 6;
			if (faHit->m_channel.channel==10){
				m_csc.channel = 1;
			}else{
				m_csc.channel = 14;
			}
		}
#endif
		m_channel = m_tt->getChannelInfo(m_csc);

		if ((m_channel.det_sys == TranslationTable::FTHODO)) {
			//Convert the waveboard hit. Probably will never be used, unless we will perform FT tests with waveboard.
			//It is used to test the system with data from a waveboard

			//Create a new FTHodo Hit Object object
			auto ftHodoHit = new FTHodoHit();

			//Assign the channel
			//Since this comes from the TT, it is still sector-layer-component)
			ftHodoHit->m_channel = *(m_channel.FTHODO);


			//Assign the time
			ftHodoHit->setTime(faHit->m_time);

			//Assign the energy
			//TODO: eventually apply another correction, here I just take the energy as provided by VTP
			ftHodoHit->setEnergy(faHit->m_charge);

			mData.push_back(ftHodoHit);
		}
	}

	//Here is the important part - converting the faHit from VTPMode7 to ftHodoHit
	for (auto faHit : faHits_fa250VTPMode7) {
		m_channel = m_tt->getChannelInfo(faHit->m_channel);
		if ((m_channel.det_sys == TranslationTable::FTHODO)) {

			//Create a new FTHodo Hit Object object
			auto ftHodoHit = new FTHodoHit();

			//Assign the channel
			//Since this comes from the TT, it is still sector-layer-component)
			ftHodoHit->m_channel = *(m_channel.FTHODO);


			//Assign the time
			ftHodoHit->setTime(faHit->m_time);

			//Assign the energy
			//TODO: eventually apply another correction, here I just take the energy as provided by VTP
			ftHodoHit->setEnergy(faHit->m_charge);

			mData.push_back(ftHodoHit);
		}
	}

}
