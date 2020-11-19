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
bool FTHodoCluster_factory::compareHits(const FTHodoHit* a, const FTHodoHit* b) {
	return (a->getHitEnergy() > b->getHitEnergy());
}

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

	std::sort(hits.begin(), hits.end(), FTHodoCluster_factory::compareHits);
	std::vector<FTHodoCluster*> clusters;

	for (auto hit : hits) {
		bool flag = false;
		if (flag == false) {
			for (int j = 0; j < clusters.size(); j++) {
				FTHodoCluster* cluster = clusters[j];
				if (cluster->containsHit(hit)) {
					cluster->push_hit(hit);
					flag = true;
					break;
				}
			}
		}
		if (flag == false) {
			FTHodoCluster *cluster = new FTHodoCluster(clusters.size());
			cluster->push_hit(hit);
			clusters.push_back(cluster);
		}
	}
	for (int i = 0; i < clusters.size(); i++) {
		//Idea: since this factory is responsible for creating the FTHodoClusters,
		//we do once the calculation of ALL quantities of interest here,
		//then the "get" methods just return the computed values.
		clusters[i]->computeCluster();
		if (clusters[i]->isGoodCluster() == true) {
			mData.push_back(clusters[i]);
		}else{
			delete clusters[i];
		}
	}
}
