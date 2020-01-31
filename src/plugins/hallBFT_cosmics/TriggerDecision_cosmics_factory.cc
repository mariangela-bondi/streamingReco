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

TriggerDecision_cosmics_factory::TriggerDecision_cosmics_factory() {
	mTag = "cosmics"; //A.C. is this the right way to set the tag?
}

TriggerDecision_cosmics_factory::~TriggerDecision_cosmics_factory() {
	// TODO Auto-generated destructor stub
}

// Overloaded by user Factories
void TriggerDecision_cosmics_factory::Init() {

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
	double singleChThr = 7;  // Single channel selection

	//Create a map of the hits
	std::map<std::pair<int, int>, double> data;

	//Fill it - [] creates a new element, with value=0, and "=" set it
	for (auto hit : hits) {
		data[std::make_pair(hit->getHitIX(), hit->getHitIY())] = hit->getHitEnergy();
	}


	//Do the loop to search for cosmics. Instead of searching ALL columns, just search columns with hits on them.
	bool hasCosmics = false;
	int nHitsInColumn = 0;
	for (auto hit : hits) {
		if (hit->getHitEnergy() > singleChThr) {
			int iX = hit->getHitIX();
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
			}
			if (nHitsInColumn>=cosmicMult){
				hasCosmics=true;
				break;
			}
		}
	}

	//a cosmic has been found
	if (hasCosmics){
		mTriggerDecision->SetDecision();
	}
	mData.push_back(mTriggerDecision);

}
