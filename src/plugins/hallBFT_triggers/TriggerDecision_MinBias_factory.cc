/*
 * TriggerDecision_MinBias_factory.cc
 *
 *  Created on: Jan 13, 2020
 *      Author: celentan
 *
 *  Modified on Aug. 15, 2020
 *              David Lawrence
 */

#include "TriggerDecision_MinBias_factory.h"

#include "JANA/JEvent.h"



//-----------------------------------------------
// TriggerDecision_MinBias_factory (constructor)
//-----------------------------------------------
TriggerDecision_MinBias_factory::TriggerDecision_MinBias_factory():Nevents(0){
  mTag="MinBias";//A.C. is this the right way to set the tag? (D.L. for the moment yes. SetTag() available in next release)
}

//-----------------------------------------------
// Init
//-----------------------------------------------
void TriggerDecision_MinBias_factory::Init(){

	PRESCALE_FACTOR     = 50; // trigger on one event out of this many
	
	mApp->SetDefaultParameter("TRIGGER:MinBias:PRESCALE_FACTOR", PRESCALE_FACTOR, "Prescale factor for min bias events. (n.b. 0 and 1 will both trigger on every event.");
	
	if( PRESCALE_FACTOR == 0 ) PRESCALE_FACTOR = 1; // protect from division by zero
}

//-----------------------------------------------
// Process
//-----------------------------------------------
void TriggerDecision_MinBias_factory::Process(const std::shared_ptr<const JEvent> &aEvent){
	
	// Create TriggerDecision object to publish the decision
	// Argument is trigger description. It will end up in metadata file so keep it simple.
	// I think a good convention here is to just give it the tag of the factory.
	auto mTriggerDecision = new TriggerDecision( mTag ); 
	mTriggerDecision->SetDecision( ((Nevents++)%PRESCALE_FACTOR) == 0 );
	mData.push_back(mTriggerDecision);
}


