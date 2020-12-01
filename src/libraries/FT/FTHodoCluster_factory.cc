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

using namespace std;

double EN_THRES = 0.25;
//this will set the hits in DESCENDING order wrt energy
bool FTHodoCluster_factory::compareHits(const FTHodoHit* a, const FTHodoHit* b) {
	return (a->getHitEnergy() > b->getHitEnergy());
}

bool passHitSelection(const FTHodoHit *hit) {
	// a selection cut to pass the hit.
	if(hit->getHitEnergy() > EN_THRES) {
		return true;
	} else {
		return false;
	}
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
	std::vector<const FTHodoHit*> hits_hodo = aEvent->Get<const FTHodoHit>();
	std::vector<const FTHodoHit*> hits;

	for (auto hit : hits_hodo) {
		if(passHitSelection(hit)) {
		           hits.push_back(hit);
		                }
	               }

	std::sort(hits.begin(), hits.end(), FTHodoCluster_factory::compareHits);
	std::vector<FTHodoCluster*> clusters;
    cout << "new "<<endl;
	for (auto hit : hits) {
		cout <<hit->m_channel.layer<<" "<<hit->getHitDx()<< " "<<hit->getHitDy()<< " "<< hit->getHitTime()<< " "<<hit->getHitEnergy()<<endl;
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
			cout<< clusters[i]->getX()<< " "<<clusters[i]->getY()<<endl;
		}else{
			delete clusters[i];
		}
	}
}
