/*
 * faWaveboardClusterfactory.cc
 *
 *  Created on: Dec 23, 2019
 *      Author: celentan
 */

#include "FTCalHitSummary_factory.h"
#include "JANA/JEvent.h"
#include "FT/FTCalHit.h"
#include "FT/FTCalHitSummary.h"
#include <vector>
#include <iostream>
#include <functional>


FTCalHitSummary_factory::FTCalHitSummary_factory() {
	// TODO Auto-generated constructor stub

}

FTCalHitSummary_factory::~FTCalHitSummary_factory() {
	// TODO Auto-generated destructor stub
}

void FTCalHitSummary_factory::Init() {

}
void FTCalHitSummary_factory::ChangeRun(const std::shared_ptr<const JEvent> &aEvent) {

}
void FTCalHitSummary_factory::Process(const std::shared_ptr<const JEvent> &aEvent) {

	//Loop su gli hits di un evento
	std::vector<const FTCalHit*> hits = aEvent->Get<const FTCalHit>();
	FTCalHitSummary *summary = new FTCalHitSummary();
	for (auto hit : hits){
		summary->addHit(hit);
	}
	mData.push_back(summary);
}
