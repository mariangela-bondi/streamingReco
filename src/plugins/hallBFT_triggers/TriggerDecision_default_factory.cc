/*
 * TriggerDecision_default_factory.cc
 *
 *  Created on: Jan 13, 2020
 *      Author: celentan
 */

#include "TriggerDecision_default_factory.h"

#include "FT/FTCalHit.h"
#include "FT/FTCalCluster.h"
#include "FT/FTHodoHit.h"
#include "DAQ/faWaveboardHit.h"
#include "JANA/JEvent.h"



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
	
  //clustering parameters are defined in FTCalCluster.cc 
  //double minSeed = 10;
  //double minEnergy = 30;
  //double minSize = 2; //number of hits required for good cluster
  
  //Trigger Parameters
  int nCluster_th = 1;  // number of clusters required to do trigger
  //end clustering parameters
	
  int nCluster=0;
  auto mTriggerDecision = new TriggerDecision();

  //	mTriggerDecision->SetDecision(); //mark all to True
  mTriggerDecision->SetDescription("cluster trigger");
  
  
  auto calclus = aEvent->Get<FTCalCluster>();
  for(auto clus : calclus) {
    nCluster++;
  }
  /* for(int ii=0; ii<calclus.size();ii++){
     auto clus = calclus[ii];
     if(clus->getClusterSize()>=minSize && clus->getClusterSeedEnergy() >=minSeed && clus->getClusterEnergy()>=minEnergy){
     nCluster++;
     }
     }*/
  
  if (nCluster>=nCluster_th){
    mTriggerDecision->SetDecision();
    //    std::cout<<"trigger cluster has been founded "<<std::endl;
  }
  mData.push_back(mTriggerDecision);
}

