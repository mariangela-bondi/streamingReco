/*
 * faWaveboardHitfactory.cc
 *
 *  Created on: Dec 23, 2019
 *      Author: celentan
 */

#include "FTCalHit_factory.h"
#include "JANA/JEvent.h"

#include "DAQ/faWaveboardHit.h"
#include "DAQ/fa250VTPMode7Hit.h"
#include "TT/TranslationTable.h"

FTCalHit_factory::FTCalHit_factory() {
	// TODO Auto-generated constructor stub
	m_tt=0;
}

FTCalHit_factory::~FTCalHit_factory() {
	// TODO Auto-generated destructor stub
}

void FTCalHit_factory::Init() {

}
void FTCalHit_factory::ChangeRun(const std::shared_ptr<const JEvent> &aEvent) {

	//TODO: get the TT
	std::cout<< "FTCalHit_factory::ChangeRun run number: "<<aEvent->GetRunNumber()<<" "<<aEvent->GetEventNumber()<<std::endl;
	m_tt = aEvent->GetSingle<TranslationTable>();


}
void FTCalHit_factory::Process(const std::shared_ptr<const JEvent> &aEvent) {

	TranslationTable::ChannelInfo m_channel;
	TranslationTable::csc_t m_csc;

	//Get the hits from FADC. Support bot the waveboard hit and the fa250VTPMode7 hit
	auto faHits_waveboard = aEvent->Get<faWaveboardHit>();
	auto faHits_fa250VTPMode7 = aEvent->Get<fa250VTPMode7Hit>();

	for (auto faHit : faHits_waveboard) {
		m_channel = m_tt->getChannelInfo(faHit->m_channel);
		if ((m_channel.det_sys == TranslationTable::FTCAL)) {
			//Convert the waveboard hit. Probably will never be used, unless we will perform FT tests with waveboard.
		}
	}

	for (auto faHit : faHits_fa250VTPMode7) {
		m_channel = m_tt->getChannelInfo(faHit->m_channel);
		if ((m_channel.det_sys == TranslationTable::FTCAL)) {

			//Create a new FTCal Hit Object object
			auto ftCalHit = new FTCalHit();

			//Assign the channel
			//Since this comes from the TT, it is still sector-layer-component)
			ftCalHit->m_channel=*(m_channel.FTCAL);

			//Here set iX and iY
			//(see https://github.com/JeffersonLab/clas12-offline-software/blob/development/reconstruction/ft/src/main/java/org/jlab/rec/ft/cal/FTCALHit.java#L40-L41)
			ftCalHit->m_channel.iY = (ftCalHit->m_channel.component/22) + 1;
			ftCalHit->m_channel.iX = (ftCalHit->m_channel.component+1) - (ftCalHit->m_channel.iY-1)*22;



			//Assign the time
			ftCalHit->setTime(faHit->m_time);

			//Assign the energy
			//TODO: eventually apply another correction, here I just take the energy as provided by VTP
			ftCalHit->setEnergy(faHit->m_charge);


			mData.push_back(ftCalHit);
		}
	}


}

