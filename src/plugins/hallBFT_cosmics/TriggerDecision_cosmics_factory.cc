/*
 * TriggerDecision_cosmics_factory.cc
 *
 *  Created on: Jan 13, 2020
 *      Author: celentan
 */

#include "TriggerDecision_cosmics_factory.h"
#include "FT/FTCalHit.h"

#include "JANA/JEvent.h"
#include <map>

#include "JANA/Services/JGlobalRootLock.h"
#include "JANA/JApplication.h"

#include <TDirectory.h>
#include <TH2.h>
#include <TH1.h>
#include <TProfile2D.h>
#include <TStyle.h>
#include "TROOT.h"

/*
static TH1D *hTest = 0;
static TH1D *hCrystal_energy_cosmicTrigger=0;
static TH1D *hnHitsInColumn_cosmicTrigger=0;
static TH1D *hColumn_cosmicTrigger=0;
*/


TriggerDecision_cosmics_factory::TriggerDecision_cosmics_factory() {
	mTag = "cosmics"; //A.C. is this the right way to set the tag?
}

TriggerDecision_cosmics_factory::~TriggerDecision_cosmics_factory() {
	// TODO Auto-generated destructor stub
}

// Overloaded by user Factories
void TriggerDecision_cosmics_factory::Init() {
	/*
	m_root_lock = japp->GetService<JGlobalRootLock>();
	m_root_lock->acquire_write_lock();
	if (hTest != NULL) {
		m_root_lock->release_lock();
		return;
	}

	gROOT->cd();
	TDirectory *main = gDirectory;
	gDirectory->mkdir("HallB_cosmics")->cd();

	hTest = new TH1D("hTest", "hTest", 100, 0, 10);
	hCrystal_energy_cosmicTrigger = new TH1D("hCrystal_energy_cosmicTrigger", "hCrystal_energy_cosmicTrigger", 100, 0, 100);
	hnHitsInColumn_cosmicTrigger = new TH1D("hnHitsInColumn_cosmicTrigger","hnHitsInColumn_cosmicTrigger", 20,0,20);
	hColumn_cosmicTrigger = new TH1D("hColumn_cosmicTrigger", "hColumn_cosmicTrigger", 22, -11, 11);



	m_root_lock->release_lock();
*/

}
void TriggerDecision_cosmics_factory::ChangeRun(const std::shared_ptr<const JEvent> &aEvent) {

}
void TriggerDecision_cosmics_factory::Process(const std::shared_ptr<const JEvent> &aEvent) {

	auto mTriggerDecision = new TriggerDecision();

	//mTriggerDecision->SetDecision(); //mark all to True
	mTriggerDecision->SetDescription("cosmics trigger");

	auto hits = aEvent->Get<FTCalHit>();
	//Inspired from:
	//https://github.com/JeffersonLab/clas12calibration-ft/blob/master/ftCalLedAndCosmics/src/main/java/org/clas/ftcal/cosmic/FTCalCosmicModule.java

	int cosmicMult = 4;  // Horizonthal selection // number of crystals above threshold in a column for cosmics selection
	int cosmicRange = 5;
	double timeWindow = 20;
	double singleChThr = 7;  // Single channel selection

	int iXX=0;
	//Create a map of the hits
	std::map<std::pair<int, int>, double> data;
	std::map<std::pair<int, int>, double> data_time;

	//Fill it - [] creates a new element, with value=0, and "=" set it
	for (auto hit : hits) {
		data[std::make_pair(hit->getHitIX(), hit->getHitIY())] = hit->getHitEnergy();
		data[std::make_pair(hit->getHitIX(), hit->getHitIY())] = hit->getHitTime();
	}


	//Do the loop to search for cosmics. Instead of searching ALL columns, just search columns with hits on them.
	bool hasCosmics = false;
	int nHitsInColumn = 0;
	for (auto hit : hits) {
		nHitsInColumn = 0;
		if (hit->getHitEnergy() > singleChThr) {
			int iX = hit->getHitIX();
			double iTime = hit->getHitTime();
			nHitsInColumn++;
			for (int iY = 1; iY <= cosmicRange; iY++) {
				//UP
				auto it = data.find(std::make_pair(iX, hit->getHitIY() + iY));
				if (it != data.end()) {
					if (it->second >= singleChThr) nHitsInColumn++;
				}
				//DOWN
				it = data.find(std::make_pair(iX, hit->getHitIY() - iY));
				if (it != data.end()) {
					if (it->second >= singleChThr) nHitsInColumn++;
				}
			}   // add the time coincidence: signals in a time window of 10 ns
			if (nHitsInColumn>=cosmicMult){
				for (int iY = 1; iY <= cosmicRange; iY++) {
					int nHitsInTime=0;
					auto it_time = data_time.find(std::make_pair(iX, hit->getHitIY() + iY));
					if (it_time != data_time.end()) {
						if (fabs(it_time->second-iTime) <= timeWindow) nHitsInTime++;
					}
				//DOWN
					it_time = data_time.find(std::make_pair(iX, hit->getHitIY() - iY));
					if (it_time != data_time.end()) {
						if (fabs(it_time->second-iTime) <= timeWindow) nHitsInTime++;
					}
					if(nHitsInTime>=cosmicMult){
						hasCosmics=true;
						iXX = iX;
						break;
					}
				}
			}
		}
	}

	//a cosmic has been found
	if (hasCosmics){
		mTriggerDecision->SetDecision();

	}

	mData.push_back(mTriggerDecision);


	// from here monitoring histogram
	//lock
/*
	m_root_lock->acquire_write_lock();
	if (hasCosmics){

		hnHitsInColumn_cosmicTrigger->Fill(nHitsInColumn);
		hColumn_cosmicTrigger->Fill(iXX);

		for (auto hit : hits) {
			int hiX = hit->getHitIX();
			if(hiX==iXX){
				for (int hiY = 1; hiY <= 23; hiY++) {
					auto it = data.find(std::make_pair(hiX, hit->getHitIY() + hiY));
					if (it != data.end()) {
						hCrystal_energy_cosmicTrigger->Fill(it->second) ;
					}

				} // end for

			}

		}

	}

//	hTest->Fill(calclusters.size());
	m_root_lock->release_lock();
	//unlock
*/

}
