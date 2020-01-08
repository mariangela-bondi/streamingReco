/*
 * faWaveboardClusterfactory.cc
 *
 *  Created on: Dec 23, 2019
 *      Author: celentan
 */

#include "FTCalCluster_factory.h"
#include "JANA/JEvent.h"
#include "FT/FTCalHit.h"

FTCalCluster_factory::FTCalCluster_factory() {
	// TODO Auto-generated constructor stub

}

FTCalCluster_factory::~FTCalCluster_factory() {
	// TODO Auto-generated destructor stub
}

void FTCalCluster_factory::Init() {

}
void FTCalCluster_factory::ChangeRun(const std::shared_ptr<const JEvent> &aEvent) {

}
void FTCalCluster_factory::Process(const std::shared_ptr<const JEvent> &aEvent) {
	auto hits = aEvent->Get<FTCalHit>();

	for (auto hit : hits){



	}


}

