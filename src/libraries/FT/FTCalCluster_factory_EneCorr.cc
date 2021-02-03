/*
 * faWaveboardClusterfactory.cc
 *
 *  Created on: Dec 23, 2019
 *      Author: celentan
 */

#include "FTCalCluster_factory_EneCorr.h"
#include "JANA/JEvent.h"
#include "FT/FTCalHitEneCorr.h"
#include "FT/FTCalCluster.h"
#include <vector>
#include <iostream>
#include <functional>

#include "JANA/Services/JParameterManager.h"
#include "JANA/Calibrations/JCalibration.h"
#include "JANA/Calibrations/JCalibrationManager.h"

//Parametri finestra temporale cluster
double time_min_EneCorr = -6;
double time_max_EneCorr = 6;

int minClusterSize = 3; //Need size >= to min for accept cluster.
double minClusterEnergy = 300; //Need size > to min for accept cluster. Not >=.
double minSeedEnergy = 50;

//this will set the hits in DESCENDING order wrt energy
bool FTCalCluster_factory_EneCorr::compareHits(const FTCalHit* a, const FTCalHit* b) {
	return (a->getHitEnergy() > b->getHitEnergy());
}

FTCalCluster_factory_EneCorr::FTCalCluster_factory_EneCorr() {
	// TODO Auto-generated constructor stub
	mTag = "EneCorr";
}

FTCalCluster_factory_EneCorr::~FTCalCluster_factory_EneCorr() {
	// TODO Auto-generated destructor stub
}

void FTCalCluster_factory_EneCorr::CorrectClusterEnergy(FTCalCluster *clus) {
	auto *seed = clus->getHit(0);
	auto component = seed->m_channel.component;

	auto cc0 = this->c0[component];
	auto cc1 = this->c1[component];
	auto cc2 = this->c2[component];
	auto cc3 = this->c3[component];
	auto cc4 = this->c4[component];

	auto rawEne = clus->getClusterEnergy(); //MeV
	rawEne /= 1000.;

	auto corr = (cc0 + cc1 * rawEne + cc2 * rawEne * rawEne + cc3 * rawEne * rawEne * rawEne + cc4 * rawEne * rawEne * rawEne * rawEne) / 1000.;
	rawEne += corr;
 //  cout << rawEne<< " "<<corr<<endl;
	clus->setClusterFullEnergy(rawEne * 1000); //MeV again

	return;

}

void FTCalCluster_factory_EneCorr::Init() {

}
void FTCalCluster_factory_EneCorr::ChangeRun(const std::shared_ptr<const JEvent> &aEvent) {
	static int hasLoaded = 0;
	if (hasLoaded == 0) {
		auto jcalib_manager = japp->GetService<JCalibrationManager>();
		static int runN = 11324;
		auto jcalib = jcalib_manager->GetJCalibration(11324);

		//Load FT-HODO
		std::vector<std::vector<double>> data;
		jcalib->Get("/calibration/ft/ftcal/energycorr", data);

		for (auto row : data) {
			//sector - layer - component - c0 - c1 - c2 - c3 - c4
			auto sector = int(row[0]);
			auto layer = int(row[1]);
			auto component = int(row[2]);
			c0[component] = row[3];
			c1[component] = row[4];
			c2[component] = row[5];
			c3[component] = row[6];
			c4[component] = row[7];
			//cout<< sector<< " "<<layer<<" "<<component<<" "<<c0[component]<< " "<<c1[component]<<" "<<c2[component]<<" "<<c3[component]<<" "<<c4[component]<<endl;
		}
	}
}

void FTCalCluster_factory_EneCorr::Process(const std::shared_ptr<const JEvent> &aEvent) {

	//Loop su gli hits di un evento
	std::vector<const FTCalHitEneCorr*> hits = aEvent->Get<const FTCalHitEneCorr>();

	std::sort(hits.begin(), hits.end(), FTCalCluster_factory_EneCorr::compareHits);
	std::vector<FTCalCluster*> clusters;


	for (auto hit : hits) {
		std::vector<std::pair<int, float>> distance_seed_hit;
		bool flag = false;
		if (flag == false) {
			for (int j = 0; j < clusters.size(); j++) {
				FTCalCluster* cluster = clusters[j];
				if (cluster->containsHit(hit, time_min_EneCorr, time_max_EneCorr)) {
					cluster->push_hit(hit);
					flag = true;
					break;
					/*
					std::pair<int, float> distance;
					distance.first = j;
					distance.second = sqrt(pow((cluster->getHit(0)->getHitX() - hit->getHitX()),2)+pow((cluster->getHit(0)->getHitY() - hit->getHitY()),2));
					distance_seed_hit.push_back(distance);
					*/
				}
			}
			/*
			if(distance_seed_hit.size()>1){
				auto min_value = 1000;
				auto idx_min = 0;
				for(int v=0; v<distance_seed_hit.size(); v++){
					if(distance_seed_hit[v].second<min_value) {
						idx_min = distance_seed_hit[v].first;
					    min_value = distance_seed_hit[v].second;
					}
				}
				clusters[idx_min]->push_hit(hit);
			}
			if(distance_seed_hit.size()==1) clusters[distance_seed_hit[0].first]->push_hit(hit);
*/
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
		clusters[i]->computeCluster(minClusterSize, minClusterEnergy,minSeedEnergy );
		this->CorrectClusterEnergy(clusters[i]);
		//std::cout <<"Is good cluster? " <<clusters[i]->isGoodCluster() <<" cluster size is " <<clusters[i]->getClusterSize() <<std::endl;
		if (clusters[i]->isGoodCluster() == true) {
			mData.push_back(clusters[i]);
		} else {
			delete clusters[i];
		}
	}
}
