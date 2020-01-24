/*
 * FTParticle_factory
 *
 *  Created on: Jan 24, 2020
 *      Author: svallarino
 */

#include "FTParticle_factory.h"
#include "JANA/JEvent.h"
#include "FT/FTCalHit.h"
#include "FT/FTParticle.h"
#include <vector>
#include <iostream>
#include <functional>


//Parameter for acceptable hodoscope and cluster association.
double deltaX=1;
double deltaY=1;
double deltat=1;
//this will set the hits in DESCENDING order wrt energy
//bool compareHits(const FTCalHit* a, const FTCalHit* b) { return (a->getHitEnergy() > b->getHitEnergy()); }

FTParticle_factory::FTParticle_factory() {
	// TODO Auto-generated constructor stub

}

FTParticle_factory::~FTParticle_factory() {
	// TODO Auto-generated destructor stub
}

void FTParticle_factory::Init() {

}
void FTParticle_factory::ChangeRun(const std::shared_ptr<const JEvent> &aEvent) {

}
void FTParticle_factory::Process(const std::shared_ptr<const JEvent> &aEvent) {

  std::vector<const FTCalCluster*> clusters =aEvent->Get<const FTCalCluster>();
  std::vector<const FTHodoCluster*> hodoscopes =aEvent->Get<const FTHodoCluster>();

	std::vector<FTParticle*> particles;

	for(auto cluster : clusters){
    FTParticle* particle=new FTParticle();
    particle->setParticleEnergy(cluster->getClusterEnergy());
    particle->setParticleTime(cluster->getClusterTime());
    particle->setParticleDx(cluster->getX());
    particle->setParticleDy(cluster->getY());
    particle->setParticleDz(cluster->getZ());
    particle->setParticleClusIndex(cluster->getClusterId());
    //Electrical charge is automatically assigned 0.
    //HodoIndex is -1 if particle is photon.
    for(auto hodoscope : hodoscopes){
      auto diffX=fabs(hodoscope->getX()-particle->getParticleDx());
      auto diffY=fabs(hodoscope->getY()-particle->getParticleDy());
      auto difft=fabs(hodoscope->getClusterTime()-particle->getParticleTime());
      //If cluster and hodoscope signals are close enough, particle is an electron
      if(diffX<deltaX && diffY<deltaY && difft<deltat){
        particle->setParticleCharge(-1);
        particle->setParticleHodoIndex(hodoscope->getClusterId());
        break;
      }
    }
    mData.push_back(particle);
  }
}
