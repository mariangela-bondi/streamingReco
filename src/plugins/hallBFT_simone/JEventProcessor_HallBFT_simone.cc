//
//    File: HallBFT_simone/JEventProcessor_HallBFT_simone.cc
// Created: Thu Jan  9 19:37:42 CET 2020
// Creator: celentan (on Linux apcx4 3.10.0-957.el7.x86_64 x86_64)
//
// ------ Last repository commit info -----
// [ Date ]
// [ Author ]
// [ Source ]
// [ Revision ]
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Jefferson Science Associates LLC Copyright Notice:
// Copyright 251 2014 Jefferson Science Associates LLC All Rights Reserved. Redistribution
// and use in source and binary forms, with or without modification, are permitted as a
// licensed user provided that the following conditions are met:
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice, this
//    list of conditions and the following disclaimer in the documentation and/or other
//    materials provided with the distribution.
// 3. The name of the author may not be used to endorse or promote products derived
//    from this software without specific prior written permission.
// This material resulted from work developed under a United States Government Contract.
// The Government retains a paid-up, nonexclusive, irrevocable worldwide license in such
// copyrighted data to reproduce, distribute copies to the public, prepare derivative works,
// perform publicly and display publicly and to permit others to do so.
// THIS SOFTWARE IS PROVIDED BY JEFFERSON SCIENCE ASSOCIATES LLC "AS IS" AND ANY EXPRESS
// OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
// JEFFERSON SCIENCE ASSOCIATES, LLC OR THE U.S. GOVERNMENT BE LIABLE TO LICENSEE OR ANY
// THIRD PARTES FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
// OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "JEventProcessor_HallBFT_simone.h"

#include "FT/FTCalHit.h"
#include "FT/FTHodoHit.h"
#include "FT/FTCalCluster.h"

#include "JANA/Services/JGlobalRootLock.h"
#include "JANA/JApplication.h"

#include "DAQ/TridasEvent.h"

#include <TDirectory.h>
#include <TH2.h>
#include <TH1.h>
#include <TProfile2D.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TClass.h>
#include <TFile.h>
#include <TCollection.h>
#include <TKey.h>
#include <TPad.h>
#include <THStack.h>

/*Here goes the histograms*/
static TH1D *hTest = 0; //Cancello tutto, posso sempre recuperarli da hallBFT_monitoring. Lascio solo htest
static TH2D *hHitPosition = 0;
static TH2D *hFirstHalfHitPosition = 0;
static TH2D *hSecondHalfHitPosition = 0;
static TH2D *hClusterPosition = 0;
static TH1D *hdTimeFromMaxEnergy = 0;
static TH1D *hdTimeFromSeed = 0;
static TH2D *hdTimeVsEnergy = 0;
static TH1D *hdTimeFromMaxEnergy_no120 = 0;
static TH1D *hdTimeFromMaxEnergy_samechannel = 0;
static TH1D *hdTimeFromMaxEnergy_samechannel_2version = 0;
static TH2D *hdEnergyVsEnergy120 = 0;
static TH2D *hdEnergyVsEnergy120_2version = 0;
static TH1D *hClusteringEfficiency = 0;
static TH1D *hGoodCluster = 0;
static TH1D *hAllCluster = 0;
static TH1D *hGoodOverAllCluster = 0;

static TH2D *hClusXY_Trigger = 0; //Position of clusters of event that verify the trigger
static TH1D *hClusM_Trigger = 0; //pi0 mass
static TH2D *hClusAngle_M_Trigger = 0;

static TH2D *hClusXY_Trigger_noncorr = 0; //Position of corrected clusters of event that verify the trigger
static TH1D *hClusM_Trigger_noncorr = 0; //pi0 mass corrected
static TH2D *hClusAngle_M_Trigger_noncorr = 0;

static TH1D *hMpi0_SelectedCluster = 0;
static TH1D *hAllDistance = 0;
static TH1D *hSelectedDistance = 0;

//---------------------------------
// JEventProcessor_HallBFT_simone    (Constructor)
//---------------------------------
JEventProcessor_HallBFT_simone::JEventProcessor_HallBFT_simone() {

}

//---------------------------------
// ~JEventProcessor_HallBFT_simone    (Destructor)
//---------------------------------
JEventProcessor_HallBFT_simone::~JEventProcessor_HallBFT_simone() {

}

//------------------
// Init
//------------------
void JEventProcessor_HallBFT_simone::Init(void) {
	// This is called once at program startup.
	m_root_lock = japp->GetService<JGlobalRootLock>();

	m_root_lock->acquire_write_lock();
	if (hTest != NULL) {
		m_root_lock->release_lock();
		return;
	}

	gROOT->cd();
	TDirectory *main = gDirectory;
	gDirectory->mkdir("HallBFT_simone")->cd();

	hTest = new TH1D("hTest", "hTest", 10, -.5, 9.5);
	hHitPosition = new TH2D("hHitPosition", "hHitPosition", 24, -.5, 23.5, 24, -.5, 23.5);
	hFirstHalfHitPosition = new TH2D("hFirstHalfHitPosition", "hFirstHalfHitPosition", 24, -.5, 23.5, 24, -.5, 23.5);
	hSecondHalfHitPosition = new TH2D("hSecondHalfHitPosition", "hSecondHalfHitPosition", 24, -.5, 23.5, 24, -.5, 23.5);
	hClusterPosition = new TH2D("hClusterPosition", "hClusterPosition", 40, -200, 200, 40, -200, 200);
	hdTimeFromMaxEnergy = new TH1D("hdTimeFromMaxEnergy", "hdTimeFromMaxEnergy", 800, -400, 400);
	hdTimeFromSeed = new TH1D("hdTimeFromSeed", "hdTimeFromSeed", 800, -400, 400);
	hdTimeFromMaxEnergy_no120 = new TH1D("hdTimeFromMaxEnergy_no120 ", "hdTimeFromMaxEnergy_no120 ", 800, -400, -400);
	hdTimeFromMaxEnergy_samechannel = new TH1D("hdTimeFromMaxEnergy_samechannel ", "hdTimeFromMaxEnergy_samechannel", 800, -400, -400);
	hdTimeFromMaxEnergy_samechannel_2version = new TH1D("hdTimeFromMaxEnergy_samechannel_2version ", "hdTimeFromMaxEnergy_samechannel_2version", 800, -400, -400);
	hdTimeVsEnergy = new TH2D("hdTimeVsEnergy", "hdTimeVsEnergy", 800, -400, 400, 5000, 0, 10000);
	hdEnergyVsEnergy120 = new TH2D("hdEnergyVsEnergy120", "hdEnergyVsEnergy120", 5000, -1000, 9000, 5000, -1000, 9000);
	hdEnergyVsEnergy120_2version = new TH2D("hdEnergyVsEnergy120_2version", "hdEnergyVsEnergy120_version", 5000, -1000, 9000, 5000, -1000, 9000);
	hClusteringEfficiency = new TH1D("hClusteringEfficiency", "hClusteringEfficiency", 10, -0.5, 9.5);
	hGoodCluster = new TH1D("hGoodCluster", "hGoodCluster", 10000, -0.5, 9999.5);
	hAllCluster = new TH1D("hAllCluster", "hAllCluster", 10000, -0.5, 9999.5);
	hGoodOverAllCluster = new TH1D("hGoodOverAllCluster", "hGoodOverAllCluster", 10000, -0.5, 9999.5);

	hClusM_Trigger = new TH1D("hClusM_Trigger", "hClusM_Trigger", 500, 0, 500);
	hClusXY_Trigger = new TH2D("hClusXY_Trigger", "hClusXY_Trigger", 200, -200, 200, 200, -200, 200);
	hClusAngle_M_Trigger = new TH2D("hClusAngle_M_Trigger", "hClusAngle_M_Trigger", 500, 0, 500, 1000, 0.9, 1);
	hClusM_Trigger_noncorr = new TH1D("hClusM_Trigger_noncorr", "hClusM_Trigger_noncorr", 500, 0, 500);
	hClusXY_Trigger_noncorr = new TH2D("hClusXY_Trigger_noncorr", "hClusXY_Trigger_noncorr", 200, -200, 200, 200, -200, 200);
	hClusAngle_M_Trigger_noncorr = new TH2D("hClusAngle_M_Trigger_noncorr", "hClusAngle_M_Trigger_noncorr", 500, 0, 500, 1000, 0.9, 1);

	hMpi0_SelectedCluster = new TH1D("hMpi0_SelectedCluster", "hMpi0_SelectedCluster", 500, 0, 500);
	hAllDistance = new TH1D("hAllDistance", "hAllDistance", 1000, 0, 1000);
	hSelectedDistance = new TH1D("hSelecetdDistance", "hSelecetdDistance", 1000, 0, 1000);

	gDirectory->cd();
	m_root_lock->release_lock();

}

//------------------
// Process
//------------------
void JEventProcessor_HallBFT_simone::Process(const std::shared_ptr<const JEvent>& aEvent) {

	// conditions to be a good cluster; //Condition on clusters are implemented in FTCalCluster.cc, if there are not yet an external file reading.
	//double minSeed = 10;
	//double minEnergy = 30;
	//double minSize = 2;

	//Variables declaration

	auto maxHitEnergyTime = 0;
	auto maxHitEnergy = 0;
	auto firstSeedTime = 100000000000.;

	auto hits = aEvent->Get<FTCalHit>(); //vector degli hits dell'evento

	//Selezione hit per massa pi0 (Energia corretta)
	auto clusters = aEvent->Get<FTCalCluster>("EneCorr"); //vector dei clusters con energia corretta
	auto clusters_noncorr = aEvent->Get<FTCalCluster>(); //vector dei clusters dell'evento

	//Selezione hit per efficienza (Energia non corretta)
	//auto clusters = aEvent->Get<FTCalCluster>(); //vector dei clusters non corretti
	//auto clusters_noncorr = aEvent->Get<FTCalCluster>("EneCorr"); //vector dei clusters dell'evento

	//Servono per riconoscere seed, non posso impostarli a hit[0] perché non è detto che ci sia.
	auto minHitTime = 99999999999999;
	auto maxHitTime = -99999999999999;
	int maxHitEnergyX = 0;
	int maxHitEnergyY = 0;

	//Numero di cluster per analisi efficienza
	int nCluster3GeV = 0;
	int nCluster2GeV = 0;

	//Dichiarazione TriggerWord
	vector<const TridasEvent*> tridas_events;
	try {
		tridas_events = aEvent->Get<TridasEvent>();
	} catch (JException &e) {
		return;
	}
	if (tridas_events.size() != 1) {
		return;
	}
	auto tridas_event = tridas_events[0];
	vector<uint32_t> word = tridas_event->triggerWords;

	//Variabili per massa pi0 selezionando i cluster
	int dist_min = 10000;
	int i_min;
	int j_min;
	int z_ele;
	bool minDist_flag = false;
	double dphi;
	TVector3 pi0;

	//lock
	m_root_lock->acquire_write_lock();

	/*	hTest->Fill(0);
	 if (hits.size() > 0)
	 hTest->Fill(1);
	 if (clusters.size() > 0) {
	 hTest->Fill(2);
	 //std::cout << "Ci sono " << clusters.size() << " clusters, posizionati in:" << std::endl;
	 for (auto cluster : clusters) {
	 hClusterPosition->Fill(cluster->getX(), cluster->getY());
	 //std::cout << cluster->getX() << "  " << cluster->getY() << std::endl;
	 }
	 //std::cout << std::endl;
	 }
	 //std::cout << "Ci sono " <<hits.size() << " hits, posizionati in:" << std::endl;
	 */

	//CICLO SUGLI HIT
	for (auto hit : hits) {
		//std::cout << hit->getHitIX() << "  " << hit->getHitIY() << std::endl;
	}

	for (int i = 0; i < hits.size(); i++) {
		auto hit = hits[i];

		hHitPosition->Fill(hit->getHitIX(), hit->getHitIY());
		if (hit->getHitEnergy() > maxHitEnergy) {
			maxHitEnergyTime = hit->getHitTime();
			maxHitEnergy = hit->getHitEnergy();
			maxHitEnergyX = hit->getHitIX();
			maxHitEnergyY = hit->getHitIY();

		}
		if (hit->getHitEnergy() > 2000 && hit->getHitTime() < firstSeedTime) {
			firstSeedTime = hit->getHitTime();
		}
		if (hit->getHitTime() < minHitTime) {
			minHitTime = hit->getHitTime();
		}
		if (hit->getHitTime() > maxHitTime) {
			maxHitTime = hit->getHitTime();
		}

		hdTimeFromMaxEnergy->Fill(hits[i]->getHitTime() - maxHitEnergyTime);
		hdTimeVsEnergy->Fill(hits[i]->getHitTime() - maxHitEnergyTime, hits[i]->getHitEnergy());
		hdTimeFromSeed->Fill(hits[i]->getHitTime() - firstSeedTime);

		if (hits[i]->getHitIX() == maxHitEnergyX && hits[i]->getHitIY() == maxHitEnergyY) {
			//std::cout<<"MaxHitX " <<maxHitEnergyX <<"  MaxHitY " <<maxHitEnergyY <<std::endl;
			//std::cout<<"ThisHitX " <<hits[i]->getHitX()) <<"  ThisHitY " <<hits[i]->getHitY() <<std::endl;
			hdTimeFromMaxEnergy_samechannel_2version->Fill(hits[i]->getHitTime() - maxHitEnergyTime);
			if (hits[i]->getHitEnergy() != maxHitEnergy && hits[i]->getHitTime() != maxHitEnergyTime) {
				hdEnergyVsEnergy120_2version->Fill(maxHitEnergy, hits[i]->getHitEnergy());
			}
		}

		/*		if (i < (hits.size() / 2)) {
		 hFirstHalfHitPosition->Fill(hits[i]->getHitIX(),
		 hits[i]->getHitIY());
		 } else {
		 hSecondHalfHitPosition->Fill(hits[i]->getHitIX(),
		 hits[i]->getHitIY());
		 }*/
		bool flag = true;
		for (int j = 0; j < hits.size(); j++) {
			if (hits[i]->getHitX() == hits[j]->getHitX() && hits[i]->getHitY() == hits[j]->getHitY() && ((hits[i]->getHitTime() - hits[j]->getHitTime()) < 140) && i != j
					&& ((hits[i]->getHitTime() - hits[j]->getHitTime()) > 0)) {
				flag = false;
				hdTimeFromMaxEnergy_samechannel->Fill(hits[i]->getHitTime() - maxHitEnergyTime);
				hdTimeFromMaxEnergy_samechannel->Fill(hits[j]->getHitTime() - maxHitEnergyTime);
				hdEnergyVsEnergy120->Fill(hits[i]->getHitEnergy(), hits[j]->getHitEnergy());
			}
		}
		if (flag == true) {
			hdTimeFromMaxEnergy_no120->Fill(hits[i]->getHitTime() - maxHitEnergyTime);
		}

	}

	for (auto cluster : clusters) {
		if (cluster->getClusterEnergy() > 3000) {
			nCluster3GeV++;
		}
		if (cluster->getClusterEnergy() > 2000) {
			nCluster2GeV++;
		}
		if (clusters.size() == 1) {
			hAllCluster->Fill(cluster->getClusterEnergy());
		}
	}

	if (word[9] == 1) { //Colonna 4: triggerwords[9] attiva
		hClusteringEfficiency->Fill(4);
		if (clusters.size() == 1) {
			hGoodCluster->Fill(clusters[0]->getClusterEnergy());
		}

	}

	hClusteringEfficiency->Fill(0); //Colonna 0: numero di eventi
	if (nCluster3GeV >= 1) {
		hClusteringEfficiency->Fill(1); //Colonna 1: numero di eventi con almeno 1 cluster da 3 GeV
		if (word[9] == 1) { //Colonna 4: triggerwords[9] attiva
			hClusteringEfficiency->Fill(5);
		}
	}

	if (nCluster3GeV >= 2) {
		hClusteringEfficiency->Fill(2); //Colonna 3: numero di eventi con almeno 2 cluster da 3 GeV
		if (word[9] == 1) { //Colonna 4: triggerwords[9] attiva
			hClusteringEfficiency->Fill(6);
		}
	}
	if (nCluster3GeV >= 3) {
		hClusteringEfficiency->Fill(3); //Colonna 5 : numero di eventi con almeno 3 cluster da 2 GeV
		if (word[9] == 1) { //Colonna 4: triggerwords[9] attiva
			hClusteringEfficiency->Fill(7);
		}
	}

	//Histogram to find pi0 mass.

	if (clusters.size() > 1) {
		for (int ii = 0; ii < clusters.size(); ii++) {
			auto cluster1 = clusters[ii];
			if (cluster1->getClusterEnergy() < 1.)
				continue;
			hClusXY_Trigger->Fill(cluster1->getX(), cluster1->getY());
			for (int jj = (ii + 1); jj < clusters.size(); jj++) {
				auto cluster2 = clusters[jj];
				if (cluster2->getClusterEnergy() < 1.)
					continue;
				auto z = cos(cluster1->getCentroid().Angle(cluster2->getCentroid()));
				auto M = sqrt(2 * cluster1->getClusterEnergy() * cluster2->getClusterEnergy() * (1 - z));
				hClusM_Trigger->Fill(M);
				hClusAngle_M_Trigger->Fill(M, z);
			}
		}
	}

	if (clusters_noncorr.size() > 1) {
		for (int ii = 0; ii < clusters_noncorr.size(); ii++) {
			auto cluster1 = clusters_noncorr[ii];
			if (cluster1->getClusterEnergy() < 1.)
				continue;
			hClusXY_Trigger_noncorr->Fill(cluster1->getX(), cluster1->getY());
			for (int jj = (ii + 1); jj < clusters_noncorr.size(); jj++) {
				auto cluster2 = clusters_noncorr[jj];
				if (cluster2->getClusterEnergy() < 1.)
					continue;
				auto z = cos(cluster1->getCentroid().Angle(cluster2->getCentroid()));
				auto M = sqrt(2 * cluster1->getClusterEnergy() * cluster2->getClusterEnergy() * (1 - z));
				hClusM_Trigger_noncorr->Fill(M);
				hClusAngle_M_Trigger_noncorr->Fill(M, z);
			}
		}
	}

	if (clusters.size() == 3) {
		for (int i = 0; i < clusters.size(); i++) {
			auto cluster1 = clusters[i];
			auto r1 = cluster1->getCentroid();
			if (cluster1->getClusterEnergy() < 1.) {
				break; //Ho sostituito continue con break, perché avendo scelto solo eventi con esattamente 3 cluster, 1 singolo cluster a E < 1 rende l'evento inutile.
			}
			for (int j = i + 1; j < clusters.size(); j++) {
				auto cluster2 = clusters[j];
				if (cluster2->getClusterEnergy() < 1.) {
					break;
				}
				auto r2 = cluster2->getCentroid();
				//auto dist = sqrt(r1.Mag2() + r2.Mag2() - 2 * r1.Mag() * r2.Mag() * (sin(r1.Theta()) * sin(r2.Theta()) * cos(r1.Phi() - r2.Phi()) - cos(r1.Theta()) * cos(r2.Theta())));
				auto dist = sqrt(pow(cluster1->getX() - cluster2->getX(), 2) + pow(cluster1->getY() - cluster2->getY(), 2));
				hAllDistance->Fill(dist);
				if (dist < dist_min) {
					dist_min = dist;
					i_min = i;
					j_min = j;
					minDist_flag = true;
					pi0 = 0.5 * (r1 + r2);
				}
			}
		}
	}

	if (minDist_flag == true) {
		for (int z = 0; z < 3; z++) {
			if (z != i_min && z != j_min) {
				z_ele = z;
			}
		}
		auto cosPi = cos(pi0.Phi());
		auto cosEl = cos(clusters[z_ele]->getCentroid().Phi());
		auto senPi = sin(pi0.Phi());
		auto senEl = sin(clusters[z_ele]->getCentroid().Phi());
		if (senPi * senEl < 0 && cosPi * cosEl < 1) {

			auto z = cos(clusters[i_min]->getCentroid().Angle(clusters[j_min]->getCentroid()));
			auto M = sqrt(2 * clusters[i_min]->getClusterEnergy() * clusters[j_min]->getClusterEnergy() * (1 - z));
			hMpi0_SelectedCluster->Fill(M);
			hSelectedDistance->Fill(dist_min);

		}
	}
	//std::cout << std::endl << std::endl;
	m_root_lock->release_lock();
//unlock

}

//------------------
// Finish
//------------------
void JEventProcessor_HallBFT_simone::Finish(void) {
// This is called when at the end of event processing

	hGoodOverAllCluster->Divide(hGoodCluster, hAllCluster, 1, 1);

	hdEnergyVsEnergy120_2version->SetXTitle("maxHitEnergy");
	hdEnergyVsEnergy120_2version->SetYTitle("sameChannelHitsEnergy");
	hdEnergyVsEnergy120->SetXTitle("Energy_hit");
	hdEnergyVsEnergy120->SetYTitle("Energy_retarded_hit");

	hHitPosition->SetXTitle("X");
	hHitPosition->SetYTitle("Y");
	hClusterPosition->SetXTitle("X");
	hClusterPosition->SetYTitle("Y");
	hdTimeFromMaxEnergy->SetXTitle("t_events-t_MaxEnergy");
	;
	hdTimeFromMaxEnergy->SetYTitle("Number of events");
	;
	hGoodCluster->SetXTitle("Energy [MeV]");
	hGoodCluster->SetYTitle("Number of cluster");
	hAllCluster->SetXTitle("Energy [MeV]");
	hAllCluster->SetYTitle("Number of cluster");
	hGoodOverAllCluster->SetXTitle("Energy [MeV]");
	hGoodOverAllCluster->SetYTitle("Number of cluster");

	hClusM_Trigger->SetXTitle("Missing Mass [MeV]");
	hMpi0_SelectedCluster->SetXTitle("Missing Mass[MeV]");
	;

	auto app = japp;
	std::string outFileName;
	TFile *fout;
	if (app->GetJParameterManager()->Exists("hallBFT_simone:output_file") == true) {
		gROOT->cd();
		TDirectory *main = gDirectory;

		app->GetJParameterManager()->GetParameter("hallBFT_simone:output_file", outFileName);
		std::cout << "JEventProcessor_HallBFT_simone::Finish " << this << " " << outFileName << std::endl;
		fout = new TFile(outFileName.c_str(), "recreate");

		main->cd("HallBFT_simone");
		TIter next(gDirectory->GetList());
		TObject* object = 0;
		fout->cd();

		while (object = next()) {
			if (object->InheritsFrom(TH1::Class())) {
				fout->cd();
				object->Write();
				std::cout << "JEventProcessor_HallBFT_simone::wrote " << object->GetName() << std::endl;
			}

		}

		fout->Write();
		fout->Close();
	}
}
