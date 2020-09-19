/*
 * TriggerDecision_FTCalCluster_factory.cc
 *
 *  Created on: Jan 13, 2020
 *      Author: celentan
 *
 *  Modified on Aug. 15, 2020
 *              David Lawrence
 */


#include <algorithm>
#include <mutex>

#include <JANA/JApplication.h>
#include "TriggerDecision_FTCalCluster_factory.h"

#include "FT/FTCalHit.h"
#include "FT/FTCalCluster.h"
#include "FT/FTHodoHit.h"
#include "DAQ/faWaveboardHit.h"
#include "JANA/JEvent.h"
#include <JANA/Utils/JBacktrace.h>

static std::mutex mtx;


//-----------------------------------------------
// TriggerDecision_FTCalCluster_factory (constructor)
//-----------------------------------------------
TriggerDecision_FTCalCluster_factory::TriggerDecision_FTCalCluster_factory(){
  mTag="FTCalCluster";//A.C. is this the right way to set the tag? (D.L. for the moment yes. SetTag() available in next release)
}

//-----------------------------------------------
// ~TriggerDecision_FTCalCluster_factory (destructor)
//-----------------------------------------------
TriggerDecision_FTCalCluster_factory::~TriggerDecision_FTCalCluster_factory(){

}


//-----------------------------------------------
// Init
//-----------------------------------------------
void TriggerDecision_FTCalCluster_factory::Init(){

	ENABLED             = true;
	TRIGGER_MODE        = MODE_Ncluster;
	FACTORY_TAG         = "EneCorr";  // Tag used when accessing FTCalClus objects
	MIN_CLUSTERS        = 1;    //         TRIGGER_MODE = 0 and 1
	MIN_CLUSTER_SIZE    = 2;    //         TRIGGER_MODE = 1
	MIN_SEED_ENERGY     = 10.0; // units?  TRIGGER_MODE = 1
	MIN_CLUSTER_ENERGY  = 30.0; // units?  TRIGGER_MODE = 1

	std::lock_guard<std::mutex> lck(mtx);
	
	mApp->SetDefaultParameter("TRIGGER:FTCalClus:ENABLED", ENABLED, "Set to 0 to disable the FTCalCluster trigger completely (no TriggerDecision objects will be produced).");
	mApp->SetDefaultParameter("TRIGGER:FTCalClus:TRIGGER_MODE", TRIGGER_MODE, "Set to 0 for triggering only on number of FTCalCluster objects. Set to 1 for trigger to also consider MIN_CLUSTER_SIZE, MIN_SEED_ENERGY, and MIN_CLUSTER_ENERGY.");
	mApp->SetDefaultParameter("TRIGGER:FTCalClus:FACTORY_TAG", FACTORY_TAG, "Factory tag to use for FTCalCluster objects. Empty string for uncalibrated. TimeCorr for time corrected. EneCorr for Time+Energy corrected.");
	mApp->SetDefaultParameter("TRIGGER:FTCalClus:MIN_CLUSTERS", MIN_CLUSTERS, "Minimum number of FTCalCluster objects needed for trigger.");
	mApp->SetDefaultParameter("TRIGGER:FTCalClus:MIN_CLUSTER_SIZE", MIN_CLUSTER_SIZE, "Minimum number of blocks hit for cluster to be counted.");
	mApp->SetDefaultParameter("TRIGGER:FTCalClus:MIN_SEED_ENERGY", MIN_SEED_ENERGY, "Minimum seed energy for cluster to be counted.");
	mApp->SetDefaultParameter("TRIGGER:FTCalClus:MIN_CLUSTER_ENERGY", MIN_CLUSTER_ENERGY, "Minimum cluster energy for cluster to be counted.");

	// OK, I may be trying to get a little to cute here, but...
	// When I found this code there was an alternate trigger
	// algorithm that was commented out and not being used.
	// I decided to implment it as an alternative mode that
	// can be selected at run time by setting the JANA config
	// parameter TRIGGER:FTCalClus:TRIGGER_MODE. Both the default
	// trigger and this alternative trigger do basically the
	// same thing: fire if the number of FTCalCluster objects
	// exceeds some value. The alternative one though put cuts
	// on which FTCalCluster objects would be included in that
	// count while the default algorithm just counted all of 
	// them.
	// 
	// To make the Process method very compact (and efficient)
	// I define a lambda function here depending on which mode 
	// the user selected. This lets me use the standard C++
	// count_if algorithm in Process().

	if( TRIGGER_MODE == MODE_Ncluster ){
		// Count all clusters (filter nothing)
		lambda = [](const FTCalCluster* c){
			return true;
		};

	}else if( TRIGGER_MODE == MODE_Energy_Cut) {
		// Count only select clusters
		lambda = [this](const FTCalCluster* c){
			return
			   c->getClusterSize()>=MIN_CLUSTER_SIZE
			&& c->getClusterSeedEnergy()>=MIN_SEED_ENERGY
			&& c->getClusterEnergy()>=MIN_CLUSTER_ENERGY;
		};

	}else{
		LOG << "Unknown Trigger mode: " << TRIGGER_MODE << "!" << LOG_END;
		mApp->Quit();
	}

}

//-----------------------------------------------
// Process
//-----------------------------------------------
void TriggerDecision_FTCalCluster_factory::Process(const std::shared_ptr<const JEvent> &aEvent){
	if( !ENABLED ) return; // allow user to disable this via JANA config. param.
	
	// Decide if this trigger fired (see comments in Init)  
	auto calclus = aEvent->Get<FTCalCluster>( FACTORY_TAG );
	bool decision = count_if(calclus.begin(), calclus.end(), lambda) >= MIN_CLUSTERS;

	// Create TriggerDecision object to publish the decision
	// Argument is trigger description. It will end up in metadata file so keep it simple.
	// I think a good convention here is to just give it the tag of the factory.
	auto mTriggerDecision = new TriggerDecision( mTag ); 
	mTriggerDecision->SetDecision(decision);
	mTriggerDecision->SetID(0x01); // this will show up in 16 high order bit in TriggeredEvent::plugin_nseeds[] (lower 16 will be 0 or 1 depending on whether trigger fired)
	mData.push_back(mTriggerDecision);
}


