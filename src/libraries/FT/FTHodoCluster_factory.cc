/*
 * FTHODOClusterfactory.cc
 *
 *  Created on: Jan 23, 2019
 *      Author: valla
 */

#include "FTHodoCluster_factory.h"
#include "JANA/JEvent.h"
#include "FT/FTHodoHit.h"
#include "FT/FTHodoCluster.h"
#include <vector>
#include <map>
#include <iostream>
#include <functional>

//this will set the hits in DESCENDING order wrt energy
bool compareHits(const FTHodoHit* a, const FTHodoHit* b) { return (a->getHitEnergy() > b->getHitEnergy()); }




FTHodoCluster_factory::FTHodoCluster_factory() {
	// TODO Auto-generated constructor stub

}

FTHodoCluster_factory::~FTHodoCluster_factory() {
	// TODO Auto-generated destructor stub
}

void FTHodoCluster_factory::Init() {

}
void FTHodoCluster_factory::ChangeRun(const std::shared_ptr<const JEvent> &aEvent) {

}
void FTHodoCluster_factory::Process(const std::shared_ptr<const JEvent> &aEvent) {

	//Loop su gli hits di un evento
	std::vector<const FTHodoHit*> hits = aEvent->Get<const FTHodoHit>();


//	std::cout<<"Event start " <<aEvent->GetEventNumber() <<std::endl;

	std::sort(hits.begin(),hits.end(),compareHits);
	std::vector<FTHodoCluster*> clusters;

	for(auto hit : hits){
		bool flag = false;
		if(flag == false){
			for(int j=0; j<clusters.size(); j++){
				FTHodoCluster* cluster = clusters[j];
				if(cluster->containsHit(hit)){
					cluster->push_hit(hit);
					flag =true;
					break;
				}
			}
		}
		if (flag == false){
			FTHodoCluster *cluster = new FTHodoCluster(clusters.size());
			cluster->push_hit(hit);
			clusters.push_back(cluster);
		}
	}
//	std::cout <<"clusters.size()= " <<clusters.size() <<", # hits: "<< hits.size() <<std::endl;
//	for(auto hit : hits){
		//std::cout <<"Hit.x= " <<hit->getHitDx() <<", Hit.Y "<< hit->getHitDy() <<", Hit.T " <<4*hit->getHitTime().count() <<" nS, Hit.E " <<hit->getHitEnergy()  <<std::endl;
//	}
	for(int i=0; i <clusters.size(); i++){
		//Idea: since this factory is responsible for creating the FTHodoClusters,
		//we do once the calculation of ALL quantities of interest here,
		//then the "get" methods just return the computed values.
		clusters[i]->computeCluster();
		//std::cout <<"Is good cluster? " <<clusters[i]->isGoodCluster() <<" cluster size is " <<clusters[i]->getClusterSize() <<std::endl;
		if (clusters[i]->isGoodCluster()==true){
		/*		std::cout <<std::endl <<"Good cluster phisical quantities:" <<std::endl;
				std::cout <<"Cluster ID: " <<clusters[i]->getClusterId() <<std::endl;
				std::cout <<"Cluster size : " <<clusters[i]->getClusterSize() <<std::endl;
				std::cout <<"Cluster energy : " <<clusters[i]->getClusterEnergy() <<std::endl;
				std::cout <<"Cluster corrected energy: " <<clusters[i]->getClusterFullEnergy() <<std::endl;
				std::cout <<"Cluster seed energy: " <<clusters[i]->getClusterSeedEnergy() <<std::endl;
				std::cout <<"Cluster time: " <<clusters[i]->getClusterTime() <<std::endl;
				std::cout <<"Cluster center: " <<clusters[i]->getX() <<", " <<clusters[i]->getY() <<", "<<clusters[i]->getZ() <<std::endl;
				std::cout <<"Cluster width X: " <<clusters[i]->getWidthX() <<std::endl;
				std::cout <<"Cluster width Y: " <<clusters[i]->getWidthY() <<std::endl;
				std::cout <<"Cluster radius: " <<clusters[i]->getRadius() <<std::endl;
				std::cout <<"Cluster theta: " <<clusters[i]->getTheta() <<std::endl;
				std::cout <<"Cluster phi: " <<clusters[i]->getPhi() <<std::endl <<std::endl;*/
				mData.push_back(clusters[i]);
			}
	}
  /*
  for(int i=0; i <clusters.size(); i++){
		//Idea: since this factory is responsible for creating the FTHodoClusters,
		//we do once the calculation of ALL quantities of interest here,
		//then the "get" methods just return the computed values.
		if (clusters[i]->isGoodCluster()==true){
				mData.push_back(clusters[i]);
	  	}
	 */

//	std::cout <<"mData.size()= " <<mData.size() <<std::endl;
//	std::cout <<"Event end "<<std::endl<<std::endl<<std::endl;

}
