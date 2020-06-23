/*
 * faWaveboardClusterfactory.cc
 *
 *  Created on: Dec 23, 2019
 *      Author: celentan
 */

#include "FTCalCluster_factory_TimeCorr.h"
#include "JANA/JEvent.h"
#include "FT/FTCalHitTimeCorr.h"
#include "FT/FTCalCluster.h"
#include <vector>
#include <iostream>
#include <functional>

//Finestra temporale cluster
double time_min_TimeCorr = -6;
double time_max_TimeCorr = 6;

//this will set the hits in DESCENDING order wrt energy
bool FTCalCluster_factory_TimeCorr::compareHits(const FTCalHit* a, const FTCalHit* b) {
	return (a->getHitEnergy() > b->getHitEnergy());
}

FTCalCluster_factory_TimeCorr::FTCalCluster_factory_TimeCorr() {
	// TODO Auto-generated constructor stub
	mTag = "TimeCorr";
}

FTCalCluster_factory_TimeCorr::~FTCalCluster_factory_TimeCorr() {
	// TODO Auto-generated destructor stub
}

void FTCalCluster_factory_TimeCorr::Init() {

}
void FTCalCluster_factory_TimeCorr::ChangeRun(const std::shared_ptr<const JEvent> &aEvent) {

}
void FTCalCluster_factory_TimeCorr::Process(const std::shared_ptr<const JEvent> &aEvent) {

	//Loop su gli hits di un evento
	std::vector<const FTCalHitTimeCorr*> hits = aEvent->Get<const FTCalHitTimeCorr>();

	std::sort(hits.begin(), hits.end(), FTCalCluster_factory_TimeCorr::compareHits);
	std::vector<FTCalCluster*> clusters;

	for (auto hit : hits) {
		bool flag = false;
		if (flag == false) {
			for (int j = 0; j < clusters.size(); j++) {
				FTCalCluster* cluster = clusters[j];
				if (cluster->containsHit(hit, time_min_TimeCorr, time_max_TimeCorr)) {
					cluster->push_hit(hit);
					flag = true;
					break;
				}
			}
		}
		if (flag == false) {
			FTCalCluster *cluster = new FTCalCluster(clusters.size());
			cluster->push_hit(hit);
			clusters.push_back(cluster);
		}
	}

	for (int i = 0; i < clusters.size(); i++) {
		//Idea: since this factory is responsible for creating the FTCalClusters,
		//we do once the calculation of ALL quantities of interest here,
		//then the "get" methods just return the computed values.
		clusters[i]->computeCluster();
		//std::cout <<"Is good cluster? " <<clusters[i]->isGoodCluster() <<" cluster size is " <<clusters[i]->getClusterSize() <<std::endl;
		if (clusters[i]->isGoodCluster() == true) {
			mData.push_back(clusters[i]);
		} else {
			delete clusters[i];
		}
	}
}
