/*
 * TriggerDecision_default_factory.cc
 *
 *  Created on: Jan 13, 2020
 *      Author: celentan
 */

#include "TriggerDecision_default_factory.h"

TriggerDecision_default_factory::TriggerDecision_default_factory(){
	mTag="default";//A.C. is this the right way to set the tag?
}

TriggerDecision_default_factory::~TriggerDecision_default_factory() {
	// TODO Auto-generated destructor stub
}


// Overloaded by user Factories
void TriggerDecision_default_factory::Init(){

}
void TriggerDecision_default_factory::ChangeRun(const std::shared_ptr<const JEvent> &aEvent){

}
void TriggerDecision_default_factory::Process(const std::shared_ptr<const JEvent> &aEvent){

	auto mTriggerDecision = new TriggerDecision();

	mTriggerDecision->SetDecision(); //mark all to True
	mTriggerDecision->SetDescription("default trigger doing nothing");

	mData.push_back(mTriggerDecision);

}
