/*
 * TriggerDecision_second_factory.cc
 *
 *  Created on: Jan 13, 2020
 *      Author: celentan
 */

#include "TriggerDecision_second_factory.h"

TriggerDecision_second_factory::TriggerDecision_second_factory(){
	mTag="second";//A.C. is this the right way to set the tag?
}

TriggerDecision_second_factory::~TriggerDecision_second_factory() {
	// TODO Auto-generated destructor stub
}


// Overloaded by user Factories
void TriggerDecision_second_factory::Init(){

}
void TriggerDecision_second_factory::ChangeRun(const std::shared_ptr<const JEvent> &aEvent){

}
void TriggerDecision_second_factory::Process(const std::shared_ptr<const JEvent> &aEvent){

	auto mTriggerDecision = new TriggerDecision();

	//mTriggerDecision->SetDecision(); //mark all to True
	mTriggerDecision->SetDescription("second trigger doing nothing - only existings to test the GetAll method in JANA");

	mData.push_back(mTriggerDecision);

}
