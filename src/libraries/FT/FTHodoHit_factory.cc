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

#include "JANA/Services/JParameterManager.h"
#include "JANA/Calibrations/JCalibration.h"
#include "JANA/Calibrations/JCalibrationManager.h"
#include<vector>

//I am hard-coding the indexes here, since it will always be 8 sectors, 2 layers, 20 components.
double px[8][2][20];
double py[8][2][20];
double pz[8][2][20];

int hasLoaded = 0;

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
	std::cout << "FTHodoHit_factory::ChangeRun run number: " << aEvent->GetRunNumber() << " " << aEvent->GetEventNumber() <<" "<< this<<std::endl;

	if (m_tt!=0) m_tt = aEvent->GetSingle<TranslationTable>();
	if (hasLoaded == 0) {
		auto jcalib_manager = japp->GetService<JCalibrationManager>();
		auto jcalib = jcalib_manager->GetJCalibration(aEvent->GetEventNumber());

		//Load FT-HODO
		std::vector<std::vector<double>> data;
		jcalib->Get("/geometry/ft/fthodo", data);

		for (auto row : data) {
			//sector - layer - component - x - y - z - width - thickness
			auto sector = int(row[0]);
			auto layer = int(row[1]);
			auto component = int(row[2]);
			px[sector - 1][layer - 1][component - 1] = row[3];
			py[sector - 1][layer - 1][component - 1] = row[4];
			pz[sector - 1][layer - 1][component - 1] = row[5];
		}
		hasLoaded = 1;
	}

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
			ftHodoHit->setHitTime(4*faHit->m_time.count());

			//Assign the energy
			//TODO: eventually apply another correction, here I just take the energy as provided by VTP
			ftHodoHit->setHitEnergy(faHit->m_charge);

			//Set the hit position
			ftHodoHit->setDx(px[ftHodoHit->m_channel.sector - 1][ftHodoHit->m_channel.layer - 1][ftHodoHit->m_channel.component - 1]);
			ftHodoHit->setDy(py[ftHodoHit->m_channel.sector - 1][ftHodoHit->m_channel.layer - 1][ftHodoHit->m_channel.component - 1]);
			ftHodoHit->setDz(pz[ftHodoHit->m_channel.sector - 1][ftHodoHit->m_channel.layer - 1][ftHodoHit->m_channel.component - 1]);

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
			ftHodoHit->setHitTime(4*faHit->m_time.count());

			//Assign the energy
			//TODO: eventually apply another correction, here I just take the energy as provided by VTP
			ftHodoHit->setHitEnergy(faHit->m_charge);

			//Set the hit position
			ftHodoHit->setDx(px[ftHodoHit->m_channel.sector - 1][ftHodoHit->m_channel.layer - 1][ftHodoHit->m_channel.component - 1]);
			ftHodoHit->setDy(py[ftHodoHit->m_channel.sector - 1][ftHodoHit->m_channel.layer - 1][ftHodoHit->m_channel.component - 1]);
			ftHodoHit->setDz(pz[ftHodoHit->m_channel.sector - 1][ftHodoHit->m_channel.layer - 1][ftHodoHit->m_channel.component - 1]);

			mData.push_back(ftHodoHit);
		}
	}

}
