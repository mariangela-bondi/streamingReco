//
//    File: HallBFT_Mariangela/JEventProcessor_HallBFT_Mariangela.cc
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

#include "JEventProcessor_HallBFT_Mariangela.h"

#include "FT/FTCalHit.h"
#include "FT/FTCalHitEneCorr.h"
#include "FT/FTCalHitTimeCorr.h"
#include "FT/FTHodoHit.h"
#include "FT/FTCalCluster.h"

#include "JANA/Services/JGlobalRootLock.h"
#include "JANA/JApplication.h"

#include "DAQ/TridasEvent.h"

#include <TDirectory.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include "TTree.h"
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TProfile2D.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TClass.h>
#include <TFile.h>
#include <TCollection.h>
#include <TKey.h>
#include <TPad.h>
#include <THStack.h>
#include <TLorentzVector.h>
#include <TVector3.h>

using namespace std;

/*Here goes the histograms*/
static TH1D *hTest = 0;

//Selezione eventi "basica"
const int firstEvent = 0;
const int lastEvent = 50;
static int eventCounter = 0;

//Analisi versione definitiva
//Analisi generiche sugli eventi
static TH1D *hDelayFromSeed = 0;
static TH1D *hHitsEnergy = 0;
static TH2D *hHitsPosition = 0;
static TH2D *hHitsEnergyPosition = 0;
static TH1D *hHitsMolt = 0;
static TH1D *hClustersMolt = 0;

//Analisi eventi a singolo cluster
static TH1D *hSCDelayFromSeed = 0;
static TH1D *hSCHitsMolt = 0;
static TH1D *hSCHitsEnergy = 0;
static TH1D *hSCClusterEnergy = 0;
static TH2D *hSCSeedPosition = 0;
static TH2D *hSCClusterPosition = 0;
static TH2D *hSCEnergyPosition = 0;
static TH2D *hSCClusterEnergyVsSeedEnergy = 0;

//Analisi eventi a doppio cluster
static TH1D *hDCClustersDeltaTime = 0;
static TH1D *hDCBigClusterMolt = 0;
static TH1D *hDCSmallClusterMolt = 0;
static TH2D *hDCClusterMolt = 0;
static TH1D *hDCBigClusterEnergy = 0;
static TH1D *hDCSmallClusterEnergy = 0;
static TH2D *hDCClusterEnergy = 0;
static TH2D *hDCClusterPosition = 0;
static TH2D *hDCEnergyPosition = 0;
static TH2D *hDCBigClusterEnergyVsSeedEnergy = 0;
static TH2D *hDCSmallClusterEnergyVsSeedEnergy = 0;
static TH2D *hDCClusterEnergyVsSeedEnergy = 0;
static TH1D *hDCInvariantMass = 0;
static TH1D *hDCSelectedInvariantMass = 0;

//Analisi eventi a tre cluster
static TH2D *hTCClustersDeltaTime = 0;
static TH1D *hTCInvariantMass = 0;
static TH1D *hTCSelectedInvariantMass = 0;

//AnalisiCristiano
static TH1D *h_tcoinc_combo = 0;
static TH1D *h_minv = 0;
static TH1D *h_minv_nocuts = 0;

int Nclusters = -99;
double Eseed[3] = {-99, -99, -99};
double Eclus[3] = {-99, -99, -99};
double Tseed[3]= {-99, -99, -99};
double Tclus[3]= {-99, -99, -99};
double Xseed[3]= {-99, -99, -99};
double Yseed[3]= {-99, -99, -99};
double Xclus[3]= {-99, -99, -99};
double Yclus[3]= {-99, -99, -99};


static TTree *tout =0;

//TimeWalk correction
//static vector<TH2D *> CorrectionCurve;

//---------------------------------
// JEventProcessor_HallBFT_Mariangela    (Constructor)
//---------------------------------
JEventProcessor_HallBFT_Mariangela::JEventProcessor_HallBFT_Mariangela() {

}

//---------------------------------
// ~JEventProcessor_HallBFT_Mariangela    (Destructor)
//---------------------------------
JEventProcessor_HallBFT_Mariangela::~JEventProcessor_HallBFT_Mariangela() {

}

//------------------
// Init
//------------------
void JEventProcessor_HallBFT_Mariangela::Init(void) {
	// This is called once at program startup.
	m_root_lock = japp->GetService<JGlobalRootLock>();

	m_root_lock->acquire_write_lock();
	if (hTest != NULL) {
		m_root_lock->release_lock();
		return;
	}

	gROOT->cd();
	TDirectory *main = gDirectory;
	gDirectory->mkdir("HallBFT_Mariangela")->cd();

	hTest = new TH1D("hTest", "hTest", 25, -.5, 24.5);

	//AnalisiCristiano
//	h_tcoinc_combo = new TH1D("h_tcoinc_combo", "h_tcoinc_combo", 400, -200, 200);
//	h_minv = new TH1D("h_minv", "h_minv", 500, 0, 500);
//	h_minv_nocuts = new TH1D("h_minv_nocuts", "h_minv_nocuts", 500, 0, 500);

//Analisi generica sull'evento
	hDelayFromSeed = new TH1D("hDelayFromSeed", "hDelayFromSeed", 440, -220, 220);
	hHitsEnergy = new TH1D("hHitsEnergy", "hHitsEnergy", 1000, 0, 10000);
	hHitsPosition = new TH2D("hHitsPosition", "hHitsPosition", 25, -.5, 24.5, 25, -0.5, 24.5);
	hHitsEnergyPosition = new TH2D("hHitsEnergyPOsition", "hHitsEnergyPosition", 25, -.5, 24.5, 25, -.5, 24.5);
	hHitsMolt = new TH1D("hHitsMolt", "hHitsMolt", 31, -.5, 30.5);
	hClustersMolt = new TH1D("hClustersMolt", "hClustersMolt", 11, -.5, 10.5);

	//Single cluster events
	hSCDelayFromSeed = new TH1D("hSCDelayFromSeed", "hSCDelayFromSeed", 51, -.5, 50.5);
	hSCHitsMolt = new TH1D("hSCHitsMolt", "hSCHitsMolt", 31, -.5, 30.5);
	hSCHitsEnergy = new TH1D("hSCHitsEnergy", "hSCHitsEnergy", 1000, 0, 10000);
	hSCClusterEnergy = new TH1D("hSCClusterEnergy", "hSCClusterEnergy", 1500, 0, 15000);
	hSCSeedPosition = new TH2D("hSCSeedPosition", "hSCSeedPosition", 25, -.5, 24.5, 25, -0.5, 24.5);
	//	hSCClusterPosition = new TH2D("hSCClusterPosition", "hSCClusterPosition", 25, -.5, 24.5, 25, -0.5, 24.5);
	//	hSCEnergyPosition = new TH2D("hSCEnergyPosition", "hSCEnergyPosition", 25, -.5, 24.5, 25, -0.5, 24.5);
	hSCClusterPosition = new TH2D("hSCClusterPosition", "hSCClusterPosition", 200, -200, 200, 200, -200, 200);
	hSCEnergyPosition = new TH2D("hSCEnergyPosition", "hSCEnergyPosition", 200, -200, 200, 200, -200, 200);
	hSCClusterEnergyVsSeedEnergy = new TH2D("hSCClusterEnergyVsSeedEnergy", "hSCClusterEnergyVsSeedEnergy", 1500, 0, 15000, 1500, 0, 15000);

	//Double clusters events
	hDCClustersDeltaTime = new TH1D("hDCClustersDeltaTime", "hDCClustersDeltaTime", 400, -200, 200);
	hDCBigClusterMolt = new TH1D("hDCBigClusterMolt", "hDCBigClusterMolt", 16, -.5, 15.5);
	hDCSmallClusterMolt = new TH1D("hDCSmallClusterMolt", "hDCSmallClusterMolt", 16, -.5, 15.5);
	hDCClusterMolt = new TH2D("hDCClusterMolt", "hDCClusterMolt", 16, -.5, 15.5, 16, -.5, 15.5);
	hDCBigClusterEnergy = new TH1D("hDCBigClusterEnergy", "hDCBigClusterEnergy", 1500, 0, 15000);
	hDCSmallClusterEnergy = new TH1D("hDCSmallClusterEnergy", "hDCSmallClusterEnergy", 1500, 0, 15000);
	hDCClusterEnergy = new TH2D("hDCClusterEnergy", "hDCClusterEnergy", 1500, 0, 15000, 1500, 0, 15000);
	hDCClusterPosition = new TH2D("hDCClusterPosition", "hDCClusterPosition", 200, -200, 200, 200, -200, 200);
	hDCEnergyPosition = new TH2D("hDCEnegyPosition", "hDCEnergyPosition", 200, -200, 200, 200, -200, 200);
	hDCBigClusterEnergyVsSeedEnergy = new TH2D("hDCBigClusterEnergyVsSeedEnergy", "hDCBigClusterEnergyVsSeedEnergy", 1500, 0, 15000, 1500, 0, 15000);
	hDCSmallClusterEnergyVsSeedEnergy = new TH2D("hDCSmallClusterEnergyVsSeedEnergy", "hDCSmallClusterEnergyVsSeedEnergy", 1500, 0, 15000, 1500, 0, 15000);
	hDCClusterEnergyVsSeedEnergy = new TH2D("hDCClusterEnergyVsSeedEnergy", "hDCClusterEnergyVsSeedEnergy", 1500, 0, 15000, 1500, 0, 15000);
	hDCInvariantMass = new TH1D("hDCInvariantMass", "hDCInvariantMass", 500, 0, 500);
	//	hDCSelectedInvariantMass = new TH1D("hDCSelectedInvariantMass", "hDCSelectedInvariantMass", 500, 0, 500);

	//Triple clusters events
	hTCClustersDeltaTime = new TH2D("hTCClustersDeltaTime", "hTCClustersDeltaTime", 201, -0.5, 200.5, 201, -0.5, 200.5);
	hTCInvariantMass = new TH1D("hTCInvariantMass", "hTCInvariantMass", 500, 0, 500);
	hTCSelectedInvariantMass = new TH1D("hTCSelectedInvariantMass", "hTCSelectedInvariantMass", 500, 0, 500);
/*
	for (int j = 0; j < 500; j++) {
	 TH2D *hCorrectionCurve = new TH2D(Form("hCorrectionCurve%d", j), Form("hCorrectionCurve%d", j), 1000, 0, 10000, 60, -25.5, 34.5);
		CorrectionCurve.push_back(hCorrectionCurve);
                 }
*/

	tout=new TTree("tout","tout");

	tout->Branch("Nclusters",&Nclusters);
	tout->Branch("Eseed", &Eseed, "Eseed[3]/D");
	tout->Branch("Eclus", &Eclus, "Eclus[3]/D");
	tout->Branch("Tseed", &Tseed, "Tseed[3]/D");
	tout->Branch("Tclus", &Tclus, "Tclus[3]/D");
	tout->Branch("Tseed", &Tseed, "Tseed[3]/D");
	tout->Branch("Xseed", &Xseed, "Xseed[3]/D");
	tout->Branch("Yseed", &Yseed, "Yseed[3]/D");
	tout->Branch("Xclus", &Xclus, "Xclus[3]/D");
	tout->Branch("Yclus", &Yclus, "Yclus[3]/D");


	gDirectory->cd();
	m_root_lock->release_lock();

}

//------------------
// Process
//------------------
void JEventProcessor_HallBFT_Mariangela::Process(const std::shared_ptr<const JEvent>& aEvent) {


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

//Hits dell'evento
//	auto hits = aEvent->Get<FTCalHit>(); //vector degli hits dell'evento
//	auto hits_EneCorr = aEvent->Get<FTCalHitEneCorr>();
	auto hits = aEvent->Get<FTCalHitEneCorr>();
//	auto hits_TimeCorr = aEvent->Get<FTCalHitTimeCorr>();

//Clusters dell'evento
//	auto clusters = aEvent->Get<FTCalCluster>();
	auto clusters = aEvent->Get < FTCalCluster > ("EneCorr");
//	auto clusters_TimeCorr = aEvent->Get < FTCalCluster > ("TimeCorr");
//	auto clusters_EneCorr = aEvent->Get < FTCalCluster > ("EneCorr"); //vector dei clusters dell'evento con correzione sull'energia degli hit
//	auto clusters_TimeCorr = aEvent->Get<FTCalCluster>();
//	auto clusters_EneCorr = aEvent->Get<FTCalCluster>(); //vector dei clusters dell'evento con correzione sull'energia degli hit

//Numero dell'evento
	auto eventNumber = aEvent->GetEventNumber();

//lock
	m_root_lock->acquire_write_lock();


	 Nclusters = -999;
	 for(int i=0; i<3; i++){
	 Eseed[i] =-999;
	 Eclus[i] =-999;
	 Tseed[i]=-999;
	 Tclus[i]=-999;
	 Xseed[i]=-999;
	 Yseed[i]=-999;
	 Xclus[i]=-999;
	 Yclus[i]=-999;
	 }



	/*	double dist_min = 1000000; //mm
	 double dist_fid = 2. * 15. * sqrt(2.); //fiducial cut //mm
	 double dist_thr = 100;
	 double twindow = 12;
	 TLorentzVector P4_gamma1, P4_gamma2, P4_pi0;
	 TLorentzVector X4_gamma1, X4_gamma2;
	 double t_ene, t_phi, t_theta, t_X, t_Y, t_Z, t_time, max_extra_ene(-9.);
	 double deltat, tmp_dist, deltaphi;
	 bool good_event = false;
	 for (int i = 0; i < clusters_EneCorr.size(); i++) {
	 auto cluster1 = clusters_EneCorr[i];
	 t_ene = cluster1->getClusterEnergy();
	 t_phi = cluster1->getPhi() * M_PI / 180.;
	 t_theta = cluster1->getTheta() * M_PI / 180.;
	 t_time = cluster1->getClusterTime();
	 t_X = cluster1->getX();
	 t_Y = cluster1->getY();
	 t_Z = cluster1->getZ();
	 P4_gamma1.SetPxPyPzE(t_ene * sin(t_theta) * cos(t_phi), t_ene * sin(t_theta) * sin(t_phi), t_ene * cos(t_theta), t_ene);
	 X4_gamma1.SetXYZT(t_X, t_Y, t_Z, t_time);
	 for (int j = i + 1; j < clusters_EneCorr.size(); j++) {
	 auto cluster2 = clusters_EneCorr[j];
	 t_ene = cluster2->getClusterEnergy();
	 t_phi = cluster2->getPhi() * M_PI / 180.;
	 t_theta = cluster2->getTheta() * M_PI / 180.;
	 t_time = cluster2->getClusterTime();
	 t_X = cluster2->getX();
	 t_Y = cluster2->getY();
	 t_Z = cluster2->getZ();
	 P4_gamma2.SetPxPyPzE(t_ene * sin(t_theta) * cos(t_phi), t_ene * sin(t_theta) * sin(t_phi), t_ene * cos(t_theta), t_ene);
	 X4_gamma2.SetXYZT(t_X, t_Y, t_Z, t_time);
	 P4_pi0 = P4_gamma1 + P4_gamma2;
	 deltat = abs(X4_gamma1.T() - X4_gamma2.T());
	 tmp_dist = (cluster2->getCentroid() - cluster1->getCentroid()).Mag(); //TVector3
	 if (tmp_dist > dist_fid && deltat < twindow)
	 good_event = true;
	 h_minv_nocuts->Fill(P4_pi0.M());
	 if (good_event)
	 h_minv->Fill(P4_pi0.M());
	 h_tcoinc_combo->Fill(X4_gamma1.T() - X4_gamma2.T());
	 } //-------photon2
	 } //------photon1*/

	//Analisi sull'evento
	double eventSeedTime = 1e20;
	hHitsMolt->Fill(hits.size());
	hClustersMolt->Fill(clusters.size());
	for (auto hit : hits) {
		if (hit->getHitEnergy() > 2000 && hit->getHitTime() < eventSeedTime) {
			eventSeedTime = hit->getHitTime();
		}
		hHitsEnergy->Fill(hit->getHitEnergy());
		hHitsPosition->Fill(hit->getHitIX(), hit->getHitIY());
		hHitsEnergyPosition->Fill(hit->getHitIX(), hit->getHitIY(), hit->getHitEnergy());
	}

	for (auto hit : hits) {
		hDelayFromSeed->Fill(hit->getHitTime() - eventSeedTime);
	}

	cout << "before"<< Nclusters<<endl;
	Nclusters = clusters.size();
	cout << "after"<< Nclusters<<endl;
	if (clusters.size() == 1) {

		auto cluster = clusters[0];
		auto seed = cluster->getHit(0);
		hSCHitsMolt->Fill(cluster->getClusterSize());
		hSCHitsEnergy->Fill(seed->getHitEnergy());
		for (int i = 1; i < cluster->getClusterSize(); i++) {
			auto hit = cluster->getHit(i);
			hSCDelayFromSeed->Fill(hit->getHitTime() - seed->getHitTime());
			hSCHitsEnergy->Fill(hit->getHitEnergy());
		}
		hSCClusterEnergy->Fill(cluster->getClusterFullEnergy());
		hSCSeedPosition->Fill(seed->getHitIX(), seed->getHitIY());
		//hSCClusterPosition->Fill((cluster->getX() + 170) / 15.4545 + 1, (cluster->getY() + 170) / 15.4545 + 1);
		//hSCEnergyPosition->Fill((cluster->getX() + 170) / 15.4545 + 1, (cluster->getY() + 170) / 15.4545 + 1, cluster->getClusterFullEnergy());
		hSCClusterPosition->Fill(cluster->getX(), cluster->getY());
		hSCEnergyPosition->Fill(cluster->getX(), cluster->getY(), cluster->getClusterFullEnergy());
		hSCClusterEnergyVsSeedEnergy->Fill(seed->getHitEnergy(), cluster->getClusterFullEnergy());

		Eseed[0] = seed->getHitEnergy();
		Eclus[0] = cluster->getClusterFullEnergy();
		Tseed[0] = seed->getHitTime();
		Tclus[0] = cluster->getClusterTime();
		Xseed[0] = seed->getHitIX();
		Yseed[0] = seed->getHitIY();
		Xclus[0] = cluster->getX();
		Yclus[0] = cluster->getY();

	}

	if (clusters.size() == 2) {
		//NOTA: il cluster 0 viene sempre scelto come il più energetico
		auto cluster0 = clusters[0];
		auto cluster1 = clusters[1];
		if (cluster0->getClusterFullEnergy() > cluster1->getClusterFullEnergy()) {
		} else {
			cluster0 = clusters[1];
			cluster1 = clusters[0];
		}
		auto seed0 = cluster0->getHit(0);
		auto seed1 = cluster1->getHit(0);
		hDCClustersDeltaTime->Fill(cluster0->getClusterTime() - cluster1->getClusterTime());
		if (abs(cluster0->getClusterTime() - cluster1->getClusterTime()) < 2) {
			hDCBigClusterMolt->Fill(cluster0->getClusterSize());
			hDCSmallClusterMolt->Fill(cluster1->getClusterSize());
			hDCClusterMolt->Fill(cluster0->getClusterSize(), cluster1->getClusterSize());
			hDCBigClusterEnergy->Fill(cluster0->getClusterFullEnergy());
			hDCSmallClusterEnergy->Fill(cluster1->getClusterFullEnergy());
			hDCClusterEnergy->Fill(cluster0->getClusterFullEnergy(), cluster1->getClusterFullEnergy());

			hDCBigClusterEnergyVsSeedEnergy->Fill(seed0->getHitEnergy(), cluster0->getClusterFullEnergy());
			hDCSmallClusterEnergyVsSeedEnergy->Fill(seed1->getHitEnergy(), cluster1->getClusterFullEnergy());
			hDCClusterEnergyVsSeedEnergy->Fill(seed0->getHitEnergy(), cluster0->getClusterFullEnergy());
			hDCClusterEnergyVsSeedEnergy->Fill(seed1->getHitEnergy(), cluster1->getClusterFullEnergy());
			hDCClusterPosition->Fill(cluster0->getX(), cluster0->getY());
			hDCClusterPosition->Fill(cluster1->getX(), cluster1->getY());
			hDCEnergyPosition->Fill(cluster0->getX(), cluster0->getY(), cluster0->getClusterFullEnergy());
			hDCEnergyPosition->Fill(cluster1->getX(), cluster1->getY(), cluster1->getClusterFullEnergy());

			double z = cos(cluster0->getCentroid().Angle(cluster1->getCentroid()));
			double M = sqrt(2 * cluster0->getClusterFullEnergy() * cluster1->getClusterFullEnergy() * (1 - z));
			hDCInvariantMass->Fill(M);
		}

		Eseed[0] = seed0->getHitEnergy();
		Eclus[0] = cluster0->getClusterFullEnergy();
		Tseed[0] = seed0->getHitTime();
		Tclus[0] = cluster0->getClusterTime();
		Xseed[0] = seed0->getHitIX();
		Yseed[0] = seed0->getHitIY();
		Xclus[0] = cluster0->getX();
		Yclus[0] = cluster0->getY();

		Eseed[1] = seed1->getHitEnergy();
		Eclus[1] = cluster1->getClusterFullEnergy();
		Tseed[1] = seed1->getHitTime();
		Tclus[1] = cluster1->getClusterTime();
		Xseed[1] = seed1->getHitIX();
		Yseed[1] = seed1->getHitIY();
		Xclus[1] = cluster1->getX();
		Yclus[1] = cluster1->getY();

	}

	if (clusters.size() == 3) {
		auto cluster0 = clusters[0];
		auto cluster1 = clusters[1];
		auto cluster2 = clusters[2];
		if (cluster1->getClusterFullEnergy() > cluster0->getClusterFullEnergy() && cluster1->getClusterFullEnergy() > cluster2->getClusterFullEnergy()) {
			if (cluster2->getClusterFullEnergy() > cluster0->getClusterFullEnergy()) {
				cluster0 = clusters[1];
				cluster1 = clusters[2];
				cluster2 = clusters[0];
			} else {
				cluster0 = clusters[1];
				cluster1 = clusters[0];
			}
		} else if (cluster2->getClusterFullEnergy() > cluster0->getClusterFullEnergy() && cluster2->getClusterFullEnergy() > cluster1->getClusterFullEnergy()) {
			if (cluster1->getClusterFullEnergy() > cluster0->getClusterFullEnergy()) {
				cluster0 = clusters[2];
				cluster1 = clusters[1];
				cluster2 = clusters[0];
			} else {
				cluster0 = clusters[2];
				cluster1 = clusters[0];
				cluster2 = clusters[1];
			}
		} else {
			if (cluster2->getClusterFullEnergy() > cluster1->getClusterFullEnergy()) {
				cluster1 = clusters[2];
				cluster2 = clusters[1];
			} else {
			}
		}
		auto dTime01 = abs(cluster0->getClusterTime() - cluster1->getClusterTime());
		auto dTime02 = abs(cluster0->getClusterTime() - cluster2->getClusterTime());
		auto dTime12 = abs(cluster1->getClusterTime() - cluster2->getClusterTime());
		hTCClustersDeltaTime->Fill(dTime01, dTime02);
		if (dTime01 < 3 && dTime02 < 3 && dTime12 < 3) {
			auto z01 = cos(cluster0->getCentroid().Angle(cluster1->getCentroid()));
			double M01 = sqrt(2 * cluster0->getClusterFullEnergy() * cluster1->getClusterFullEnergy() * (1 - z01));
			hTCInvariantMass->Fill(M01);

			auto z02 = cos(cluster0->getCentroid().Angle(cluster2->getCentroid()));
			double M02 = sqrt(2 * cluster0->getClusterFullEnergy() * cluster2->getClusterFullEnergy() * (1 - z02));
			hTCInvariantMass->Fill(M02);

			auto z12 = cos(cluster1->getCentroid().Angle(cluster2->getCentroid()));
			double M12 = sqrt(2 * cluster1->getClusterFullEnergy() * cluster2->getClusterFullEnergy() * (1 - z12));
			hTCInvariantMass->Fill(M12);

		}

		Eseed[0] = cluster0->getHit(0)->getHitEnergy();
		Eclus[0] = cluster0->getClusterFullEnergy();
		Tseed[0] = cluster0->getHit(0)->getHitTime();
		Tclus[0] = cluster0->getClusterTime();
		Xseed[0] = cluster0->getHit(0)->getHitIX();
		Yseed[0] = cluster0->getHit(0)->getHitIY();
		Xclus[0] = cluster0->getX();
		Yclus[0] = cluster0->getY();

		Eseed[1] = cluster1->getHit(0)->getHitEnergy();
		Eclus[1] = cluster1->getClusterFullEnergy();
		Tseed[1] = cluster1->getHit(0)->getHitTime();
		Tclus[1] = cluster1->getClusterTime();
		Xseed[1] = cluster1->getHit(0)->getHitIX();
		Yseed[1] = cluster1->getHit(0)->getHitIY();
		Xclus[1] = cluster1->getX();
		Yclus[1] = cluster1->getY();

		Eseed[2] = cluster2->getHit(0)->getHitEnergy();
		Eclus[2] = cluster2->getClusterFullEnergy();
		Tseed[2] = cluster2->getHit(0)->getHitTime();
		Tclus[2] = cluster2->getClusterTime();
		Xseed[2] = cluster2->getHit(0)->getHitIX();
		Yseed[2] = cluster2->getHit(0)->getHitIY();
		Xclus[2] = cluster2->getX();
		Yclus[2] = cluster2->getY();

	}

	/*	if (hits.size() != 0 || hits_EneCorr.size() != 0 || hits_TimeCorr.size() != 0 || clusters.size() != 0 || clusters_EneCorr.size() != 0 || clusters_TimeCorr.size() != 0)
	 hTest->Fill(1);

	 //	Energy leaking correction
	 if (clusters.size() == 1) {
	 hClusEneVsClusEneLeakCorr->Fill(clusters[0]->getClusterEnergy(), clusters[0]->getClusterFullEnergy());
	 }
	 if (clusters_TimeCorr.size() == 1) {
	 hClusEneVsClusEneLeakCorr_corrTime->Fill(clusters_TimeCorr[0]->getClusterEnergy(), clusters_TimeCorr[0]->getClusterFullEnergy());
	 }
	 if (clusters_EneCorr.size() == 1) {
	 hClusEneVsClusEneLeakCorr_corrAll->Fill(clusters_EneCorr[0]->getClusterEnergy(), clusters_EneCorr[0]->getClusterFullEnergy());
	 }

	 //	Right analog radius
	 /*	if (clusters_TimeCorr.size() == 1) {
	 hAnalogRadius->Fill(clusters_TimeCorr[0]->getRadius());
	 hAnalogRadiusVsClusEne->Fill(clusters_TimeCorr[0]->getClusterEnergy(), clusters_TimeCorr[0]->getRadius());
	 }
	 if (clusters_EneCorr.size() == 1) {
	 hAnalogRadius_corr->Fill(clusters_EneCorr[0]->getRadius());
	 hAnalogRadiusVsClusEne_corr->Fill(clusters_EneCorr[0]->getClusterEnergy(), clusters_EneCorr[0]->getRadius());
	 }*/

//	Stampa mappa degli eventi con raggio del cluster nullo.
	/*	if (clusters_EneCorr.size() == 1) {
	 if (clusters_EneCorr[0]->getRadius() < 0.5) {
	 TH2D *hRadius0Event = new TH2D(Form("hRadius0Event%d", eventNumber), Form("hRadius0Event%d", eventNumber), 25, -0.5, 24.5, 25, -0.5, 24.5);
	 for (int i = 0; i < clusters_EneCorr[0]->getClusterSize(); i++) {
	 auto hit = clusters_EneCorr[0]->getHit(i);
	 hRadius0Event->Fill(hit->getHitIX(), hit->getHitIY(), hit->getHitEnergy());
	 }
	 Radius0Events.push_back(hRadius0Event);
	 }
	 }*/

//	Riempe distanza tra due cluster senza correzioni
	/*	if (clusters.size() == 2) {
	 auto cluster1 = clusters[0];
	 auto cluster2 = clusters[1];
	 auto dist = (clusters[0]->getCentroid() - clusters[1]->getCentroid()).Mag();
	 hDist2Clus->Fill(dist);
	 if (fabs(cluster1->getClusterTime() - cluster2->getClusterTime()) < 3) {
	 hDist2Clus_coinc->Fill(dist);
	 }
	 }*/

//	Stampa mappa degli eventi distanti 15 mm senza correzioni (picco che sparisce con correzioni).
	/*if (clusters.size() == 2) {
	 auto cluster1 = clusters[0];
	 auto cluster2 = clusters[1];
	 auto dist = (clusters[0]->getCentroid() - clusters[1]->getCentroid()).Mag();
	 hDist2Clus->Fill(dist);
	 if (fabs(cluster1->getClusterTime() - cluster2->getClusterTime()) < 6) {
	 hDist2Clus_coinc->Fill(dist);
	 }
	 if (dist > 12 && dist < 18 && fabs(cluster1->getClusterTime() - cluster2->getClusterTime()) < 6) {
	 //			cin.get();
	 TH2D *hDist15Event1Energy = new TH2D(Form("hDist15Event1Energy%d", eventNumber), Form("hDist15Event1Energy%d", eventNumber), 25, -0.5, 24.5, 25, -0.5, 24.5);
	 TH2D *hDist15Event2Energy = new TH2D(Form("hDist15Event2Energy%d", eventNumber), Form("hDist15Event2Energy%d", eventNumber), 25, -0.5, 24.5, 25, -0.5, 24.5);
	 TH2D *hDist15Event1Time = new TH2D(Form("hDist15Event1Time%d", eventNumber), Form("hDist15Event1Time%d", eventNumber), 25, -0.5, 24.5, 25, -0.5, 24.5);
	 TH2D *hDist15Event2Time = new TH2D(Form("hDist15Event2Time%d", eventNumber), Form("hDist15Event2Time%d", eventNumber), 25, -0.5, 24.5, 25, -0.5, 24.5);
	 //			cout << "Cluster1 size " << cluster1->getClusterSize() << endl;
	 for (int i = 0; i < cluster1->getClusterSize(); i++) {
	 auto hit = cluster1->getHit(i);
	 hDist15Event1Energy->Fill(hit->getHitIX(), hit->getHitIY(), hit->getHitEnergy());
	 hDist15Event1Time->Fill(hit->getHitIX(), hit->getHitIY(), hit->getHitTime() + 1000);
	 //				cout << "Hit " << i << " Energy" << hit->getHitEnergy() << " X " << hit->getHitIX() << " Y " << hit->getHitIY() << endl;
	 }
	 //			cout << "Cluster 1 end; Cluster 2 size " << cluster2->getClusterSize() << endl;
	 for (int i = 0; i < cluster2->getClusterSize(); i++) {
	 auto hit = cluster2->getHit(i);
	 hDist15Event2Energy->Fill(hit->getHitIX(), hit->getHitIY(), hit->getHitEnergy());
	 hDist15Event2Time->Fill(hit->getHitIX(), hit->getHitIY(), hit->getHitTime() + 1000);
	 //				cout << "Hit " << i << " Energy " << hit->getHitEnergy() << " X " << hit->getHitIX() << " Y " << hit->getHitIY() << endl;
	 }

	 Dist15Events1Energy.push_back(hDist15Event1Energy);
	 Dist15Events1Time.push_back(hDist15Event1Time);
	 Dist15Events2Energy.push_back(hDist15Event2Energy);
	 Dist15Events2Time.push_back(hDist15Event2Time);
	 //			cout << endl;
	 //			cin.get();

	 }

	 }*/

//	Istogramma degli angoli relativi tra i due cluster e bidimensionae degli angoli polari.
	/*	if (clusters_EneCorr.size() == 2) {
	 auto cluster1 = clusters_EneCorr[0];
	 auto cluster2 = clusters_EneCorr[1];
	 auto dist = (clusters_EneCorr[0]->getCentroid() - clusters_EneCorr[1]->getCentroid()).Mag();
	 auto angleRel = (cluster1->getCentroid().Angle(cluster2->getCentroid())) * 180 / M_PI;
	 auto theta1 = cluster1->getCentroid().Theta() * 180 / M_PI;
	 auto theta2 = cluster2->getCentroid().Theta() * 180 / M_PI;
	 hOpeningAngle->Fill(angleRel);
	 hRelativeAngle->Fill(theta1, theta2);
	 if (dist > 30 && dist < 100) {
	 hOpeningAngle_1bump->Fill(angleRel);
	 hRelativeAngle_1bump->Fill(theta1, theta2);
	 } else if (dist > 170 && dist < 280) {
	 hOpeningAngle_2bump->Fill(angleRel);
	 hRelativeAngle_2bump->Fill(theta1, theta2);
	 } else {
	 hOpeningAngle_off->Fill(angleRel);
	 hRelativeAngle_off->Fill(theta1, theta2);
	 }
	 }*/

//	Posizione dei cluster (con/senza coincidenza).
	/*	if (clusters_EneCorr.size() == 2) {
	 auto cluster0 = clusters_EneCorr[0];
	 auto cluster1 = clusters_EneCorr[1];
	 auto dist = (cluster0->getCentroid() - cluster1->getCentroid()).Mag();
	 if (abs(cluster0->getClusterTime() - cluster1->getClusterTime()) > 15) {
	 hClus1EneVsClus2Ene->Fill(cluster0->getClusterFullEnergy(), cluster1->getClusterFullEnergy());
	 h2ClusPosition->Fill(cluster0->getCentroid().X(), cluster0->getCentroid().Y());
	 h2ClusPosition->Fill(cluster1->getCentroid().X(), cluster1->getCentroid().Y());
	 if (dist > 30 && dist < 100) {
	 hClus1EneVsClus2Ene_1bump->Fill(cluster0->getClusterFullEnergy(), cluster1->getClusterFullEnergy());
	 h2ClusPosition_1bump->Fill(cluster0->getCentroid().X(), cluster0->getCentroid().Y());
	 h2ClusPosition_1bump->Fill(cluster1->getCentroid().X(), cluster1->getCentroid().Y());
	 } else if (dist > 170 && dist < 280) {
	 hClus1EneVsClus2Ene_2bump->Fill(cluster0->getClusterFullEnergy(), cluster1->getClusterFullEnergy());
	 h2ClusPosition_2bump->Fill(cluster0->getCentroid().X(), cluster0->getCentroid().Y());
	 h2ClusPosition_2bump->Fill(cluster1->getCentroid().X(), cluster1->getCentroid().Y());
	 }
	 }
	 if (abs(cluster0->getClusterTime() - cluster1->getClusterTime()) < 6) {
	 hClus1EneVsClus2Ene_coinc->Fill(cluster0->getClusterFullEnergy(), cluster1->getClusterFullEnergy());
	 h2ClusPosition_coinc->Fill(cluster0->getCentroid().X(), cluster0->getCentroid().Y());
	 h2ClusPosition_coinc->Fill(cluster1->getCentroid().X(), cluster1->getCentroid().Y());
	 if (dist > 30 && dist < 100) {
	 hClus1EneVsClus2Ene_1bump_coinc->Fill(cluster0->getClusterFullEnergy(), cluster1->getClusterFullEnergy());
	 h2ClusPosition_1bump_coinc->Fill(cluster0->getCentroid().X(), cluster0->getCentroid().Y());
	 h2ClusPosition_1bump_coinc->Fill(cluster1->getCentroid().X(), cluster1->getCentroid().Y());
	 } else if (dist > 170 && dist < 280) {
	 hClus1EneVsClus2Ene_2bump_coinc->Fill(cluster0->getClusterFullEnergy(), cluster1->getClusterFullEnergy());
	 h2ClusPosition_2bump_coinc->Fill(cluster0->getCentroid().X(), cluster0->getCentroid().Y());
	 h2ClusPosition_2bump_coinc->Fill(cluster1->getCentroid().X(), cluster1->getCentroid().Y());
	 }

	 }
	 }*/

//	if (clusters_TimeCorr.size() == 1 && clusters_EneCorr.size() == 1) {
//		if (clusters_TimeCorr[0]->getClusterEnergy() < 2000) {
//			cout << endl << "Id EneCorr " << clusters_EneCorr[0]->getClusterId() * 1. << " TimeCorr " << clusters_TimeCorr[0]->getClusterId() * 1. << endl;
//			cout << "Size EneCorr " << clusters_EneCorr[0]->getClusterSize() * 1. << " TimeCorr " << clusters_TimeCorr[0]->getClusterSize() * 1. << endl;
//			cout << "Energy EneCorr " << clusters_EneCorr[0]->getClusterEnergy() << " TimeCorr " << clusters_TimeCorr[0]->getClusterEnergy() << endl;
//			cout << "Time EneCorr " << clusters_EneCorr[0]->getClusterTime() << " TimeCorr " << clusters_TimeCorr[0]->getClusterTime() << endl;
//			cout << "X EneCorr " << clusters_EneCorr[0]->getCentroid().X() << " TimeCorr " << clusters_TimeCorr[0]->getCentroid().X() << endl;
//			cout << "Y EneCorr " << clusters_EneCorr[0]->getCentroid().Y() << " TimeCorr " << clusters_TimeCorr[0]->getCentroid().Y() << endl;
//			cout << "Z EneCorr " << clusters_EneCorr[0]->getCentroid().Z() << " TimeCorr " << clusters_TimeCorr[0]->getCentroid().Z() << endl;
//			cout << " Cluster radius Enecorr " << clusters_EneCorr[0]->getRadius() << " TimeCorr " << clusters_TimeCorr[0]->getRadius() << endl << endl;
//			for (int i = 0; i < clusters_EneCorr[0]->getClusterSize(); i++) {
//				auto hit_TimeCorr = clusters_TimeCorr[0]->getHit(i);
//				auto hit_EneCorr = clusters_EneCorr[0]->getHit(i);
//				cout << "Hit " << i * 1. << " EneCorr:  X = " << hit_EneCorr->getHitIX() * 1. << " ; Y = " << hit_EneCorr->getHitIY() * 1. << " ; Energy = " << hit_EneCorr->getHitEnergy()
//						<< " ; Time = " << hit_EneCorr->getHitTime() << endl;
//				cout << "Hit " << i * 1. << " TimeCorr: X = " << hit_TimeCorr->getHitIX() * 1. << " ; Y = " << hit_TimeCorr->getHitIY() * 1. << " ; Energy = " << hit_TimeCorr->getHitEnergy()
//						<< " ; Time = " << hit_TimeCorr->getHitTime() << endl;
//
//			}
//			cout << endl << "Hits size " << hits.size() + 0. << endl;
//			cout << "Cluster, seed position, X " << clusters_TimeCorr[0]->getHit(0)->getHitIX() + 0. << "; Y " << clusters_TimeCorr[0]->getHit(0)->getHitIY() + 0. << "; time "
//					<< clusters_TimeCorr[0]->getHit(0)->getHitTime() << "; energy" << clusters_TimeCorr[0]->getClusterEnergy() << "; size " << clusters_TimeCorr[0]->getClusterSize() + 0. << endl;
//			for (auto hit : hits_TimeCorr) {
//				cout << "Hit:TimeCorr Energy " << hit->getHitEnergy() << "; X " << hit->getHitIX() + 0. << "; Y " << hit->getHitIY() + 0. << "; time " << hit->getHitTime() << endl;
//			}
//			cout << endl;
//			for (auto hit : hits_EneCorr) {
//				cout << "Hit:EneCorr Energy " << hit->getHitEnergy() << "; X " << hit->getHitIX() + 0. << "; Y " << hit->getHitIY() + 0. << "; time " << hit->getHitTime() << endl;
//
//			}
//			cout << endl;
//		}
//	}
//Valuto energia dei cluster corretta vs energia cluster non corretta.
	/*	if (clusters_TimeCorr.size() == 1 && clusters_EneCorr.size() == 1) {
	 hClusEneCorrVsClusEne->Fill(clusters_TimeCorr[0]->getClusterEnergy(), clusters_EneCorr[0]->getClusterEnergy());
	 hSeedEneCorrVsSeedEne->Fill(clusters_TimeCorr[0]->getHit(0)->getHitEnergy(), clusters_EneCorr[0]->getHit(0)->getHitEnergy());
	 }*/

//	ASSUMO CHE LA CORREZIONE TEMPORALE SIA CORRETTA; COMPLETO LE ANALISI SULLA CORREZIONE ENERGETICA.
//	Studio la distanza tra i due cluster, con o senza la correzione energetica (tempi sempre corretti)
	/*	if (clusters_TimeCorr.size() == 2) {
	 if (fabs(clusters_TimeCorr[0]->getClusterTime() - clusters_TimeCorr[1]->getClusterTime()) > 6) {
	 auto dist = (clusters_TimeCorr[0]->getCentroid() - clusters_TimeCorr[1]->getCentroid()).Mag();
	 //			hDist2Clus->Fill(dist);
	 //			if (dist < 80) {
	 //				hClusEne_0_80mm->Fill(clusters_TimeCorr[0]->getClusterEnergy(), clusters_TimeCorr[1]->getClusterEnergy());
	 //			} else if (dist > 160) {
	 //				hClusEne_over_160mm->Fill(clusters_TimeCorr[0]->getClusterEnergy(), clusters_TimeCorr[1]->getClusterEnergy());
	 //			} else {
	 //				hClusEne_80_160mm->Fill(clusters_TimeCorr[0]->getClusterEnergy(), clusters_TimeCorr[1]->getClusterEnergy());
	 //			}
	 }
	 }
	 if (clusters_EneCorr.size() == 2) {
	 if (fabs(clusters_EneCorr[0]->getClusterTime() - clusters_EneCorr[1]->getClusterTime()) > 6) {
	 auto dist = (clusters_EneCorr[0]->getCentroid() - clusters_EneCorr[1]->getCentroid()).Mag();
	 hDist2Clus_corr->Fill(dist);
	 //			if (dist < 80) {
	 //				hClusEne_0_80mm_corr->Fill(clusters_EneCorr[0]->getClusterEnergy(), clusters_EneCorr[1]->getClusterEnergy());
	 //			} else if (dist > 160) {
	 //				hClusEne_over_160mm_corr->Fill(clusters_EneCorr[0]->getClusterEnergy(), clusters_EneCorr[1]->getClusterEnergy());
	 //			} else {
	 //				hClusEne_80_160mm_corr->Fill(clusters_EneCorr[0]->getClusterEnergy(), clusters_EneCorr[1]->getClusterEnergy());
	 //			}
	 }
	 }*/

	/*	if (clusters_EneCorr.size() == 1 && clusters_TimeCorr.size() == 1) {
	 if (clusters_EneCorr[0]->getClusterSize() == clusters_TimeCorr[0]->getClusterSize() && (clusters_EneCorr[0]->getClusterEnergy() > 10000 && clusters_TimeCorr[0]->getClusterEnergy() > 10000)) { //
	 cout << endl << "Id EneCorr " << clusters_EneCorr[0]->getClusterId() * 1. << " TimeCorr " << clusters_TimeCorr[0]->getClusterId() * 1. << endl;
	 cout << "Size EneCorr " << clusters_EneCorr[0]->getClusterSize() * 1. << " TimeCorr " << clusters_TimeCorr[0]->getClusterSize() * 1. << endl;
	 cout << "Energy EneCorr " << clusters_EneCorr[0]->getClusterEnergy() << " TimeCorr " << clusters_TimeCorr[0]->getClusterEnergy() << endl;
	 cout << "Time EneCorr " << clusters_EneCorr[0]->getClusterTime() << " TimeCorr " << clusters_TimeCorr[0]->getClusterTime() << endl;
	 cout << "X EneCorr " << clusters_EneCorr[0]->getCentroid().X() << " TimeCorr " << clusters_TimeCorr[0]->getCentroid().X() << endl;
	 cout << "Y EneCorr " << clusters_EneCorr[0]->getCentroid().Y() << " TimeCorr " << clusters_TimeCorr[0]->getCentroid().Y() << endl;
	 cout << "Z EneCorr " << clusters_EneCorr[0]->getCentroid().Z() << " TimeCorr " << clusters_TimeCorr[0]->getCentroid().Z() << endl;
	 cout << " Cluster radius Enecorr " << clusters_EneCorr[0]->getRadius() << " TimeCorr " << clusters_TimeCorr[0]->getRadius() << endl << endl;

	 for (int i = 0; i < clusters_EneCorr[0]->getClusterSize(); i++) {
	 auto hit_TimeCorr = clusters_TimeCorr[0]->getHit(i);
	 auto hit_EneCorr = clusters_EneCorr[0]->getHit(i);
	 cout << "Hit " << i * 1. << " EneCorr:  X = " << hit_EneCorr->getHitIX() * 1. << " ; Y = " << hit_EneCorr->getHitIY() * 1. << " ; Energy = " << hit_EneCorr->getHitEnergy()
	 << " ; Time = " << hit_EneCorr->getHitTime() << endl;
	 cout << "Hit " << i * 1. << " TimeCorr: X = " << hit_TimeCorr->getHitIX() * 1. << " ; Y = " << hit_TimeCorr->getHitIY() * 1. << " ; Energy = " << hit_TimeCorr->getHitEnergy()
	 << " ; Time = " << hit_TimeCorr->getHitTime() << endl;

	 }
	 cout << endl;
	 }
	 }*/

//Riempe distanza tra i due cluster, per eventi a 2 cluster
	/*		if (clusters.size() == 2) {
	 auto dist = (clusters[0]->getCentroid() - clusters[1]->getCentroid()).Mag();
	 hDist2Clus->Fill(dist);
	 if (fabs(clusters[0]->getClusterTime() - clusters[1]->getClusterTime()) < 6) {
	 hDist2Clus_coinc->Fill(dist);
	 }
	 }
	 if (clusters_TimeCorr.size() == 2) {
	 auto dist_corr = (clusters_TimeCorr[0]->getCentroid() - clusters_TimeCorr[1]->getCentroid()).Mag();
	 hDist2Clus_corr->Fill(dist_corr);
	 if (fabs(clusters_TimeCorr[0]->getClusterTime() - clusters_TimeCorr[1]->getClusterTime()) < 6) {
	 hDist2Clus_coinc_corr->Fill(dist_corr);
	 }
	 }*/

//Riempe raggio digitale e distanza analogica tra gli hit e la posizione del cluster.
	/* if (clusters.size() == 1) {
	 auto seed = clusters[0]->getHit(0);
	 for (int i = 0; i < clusters[0]->getClusterSize(); i++) {
	 auto hit = clusters[0]->getHit(i);
	 int dist = max(abs(hit->getHitIX() - seed->getHitIX()), abs(hit->getHitIY() - seed->getHitIY()));
	 hDigitalRadius->Fill(dist);
	 hDigitalRadiusVsClusEne->Fill(clusters[0]->getClusterEnergy(), dist);
	 TVector3 hitPosition(hit->getHitX(), hit->getHitY(), hit->getHitZ());
	 double analogDist = (clusters[0]->getCentroid() - hitPosition).Mag();
	 hAnalogRadius->Fill(analogDist, hit->getHitEnergy() / clusters[0]->getClusterEnergy());
	 hAnalogRadiusVsClusEne->Fill(clusters[0]->getClusterEnergy(), analogDist, hit->getHitEnergy() / clusters[0]->getClusterEnergy());
	 }
	 }

	 if (clusters_TimeCorr.size() == 1) {
	 auto seed = clusters_TimeCorr[0]->getHit(0);
	 for (int i = 0; i < clusters_TimeCorr[0]->getClusterSize(); i++) {
	 auto hit = clusters_TimeCorr[0]->getHit(i);
	 int dist = max(abs(hit->getHitIX() - seed->getHitIX()), abs(hit->getHitIY() - seed->getHitIY()));
	 hDigitalRadius_corr->Fill(dist);
	 hDigitalRadiusVsClusEne_corr->Fill(clusters_TimeCorr[0]->getClusterEnergy(), dist);
	 TVector3 hitPosition_corr(hit->getHitX(), hit->getHitY(), hit->getHitZ());
	 double analogDist_corr = (clusters_TimeCorr[0]->getCentroid() - hitPosition_corr).Mag();
	 hAnalogRadius_corr->Fill(analogDist_corr, hit->getHitEnergy() / clusters_TimeCorr[0]->getClusterEnergy());
	 hAnalogRadiusVsClusEne_corr->Fill(clusters_TimeCorr[0]->getClusterEnergy(), analogDist_corr, hit->getHitEnergy() / clusters_TimeCorr[0]->getClusterEnergy());
	 }
	 }

	 //RIEMPE istogrammi per i Crystalli della colonna x=12. Histo ritardo hit vs energy. Due histo per seed nella metà di destra o nella metà di sinistra del calorimetro
	 /*	if (clusters.size() == 1 && eventNumber > 1000000) { 	//
	 bool flag = false;
	 for (int i = 0; i < clusters[0]->getClusterSize(); i++) {
	 auto hit = clusters[0]->getHit(i);
	 if (hit->getHitIX() == 12) {
	 flag = true;
	 break;
	 }
	 }
	 if (flag == true) {
	 auto seed = clusters[0]->getHit(0);
	 if (seed->getHitIX() < 12) {
	 for (int i = 1; i < clusters[0]->getClusterSize(); i++) {
	 auto hit = clusters[0]->getHit(i);
	 if (hit->getHitIX() == 12) {
	 //						hSeedSx->Fill(hit->getHitEnergy(), hit->getHitTime() - seed->getHitTime());
	 TwentyNsSx[hit->m_channel.component]->Fill(hit->getHitEnergy(), hit->getHitTime() - seed->getHitTime());
	 }

	 }
	 } else {
	 for (int i = 1; i < clusters[0]->getClusterSize(); i++) {
	 auto hit = clusters[0]->getHit(i);
	 if (hit->getHitIX() == 12) {
	 //						hSeedDx->Fill(hit->getHitEnergy(), hit->getHitTime() - seed->getHitTime());
	 TwentyNsDx[hit->m_channel.component]->Fill(hit->getHitEnergy(), hit->getHitTime() - seed->getHitTime());
	 }
	 }
	 }
	 }
	 }*/

//Riempe CorrectionCurve, TH2D ritardo hit (rispetto al seed) vs energy hit, uno diverso per ogni component, da cui ricavare la curva di correzione
/*
	if (clusters.size() == 1) {
	 auto seed = clusters[0]->getHit(0);
	 for (int i = 1; i < clusters[0]->getClusterSize(); i++) {
	 auto hit = clusters[0]->getHit(i);
	 CorrectionCurve[hit->m_channel.component]->Fill(hit->getHitEnergy(), hit->getHitTime() - seed->getHitTime());
	 }
	 }
*/
//Riempe CorrectionCurve, per cluster non corretti, TH2D ritardo hit (rispetto al seed) vs energy hit, uno diverso per ogni component, da cui ricavare la curva di correzione
	/*	if (eventNumber > 1000000) {
	 if (clusters.size() == 1) {
	 auto seed = clusters[0]->getHit(0);
	 for (int i = 1; i < clusters[0]->getClusterSize(); i++) {
	 auto hit = clusters[0]->getHit(i);
	 CorrectionCurve[hit->m_channel.component]->Fill(hit->getHitEnergy(), hit->getHitTime() - seed->getHitTime());
	 }
	 }
	 }*/

//	Riempre Correction curve differenti, nel caso di seed a tra 2 e 4 GeV, tra 4 e 6 GeV, oltre 6 GeV.
	/*	if (eventNumber > 1000000) {
	 if (clusters.size() == 1) {
	 auto seed = clusters[0]->getHit(0);
	 for (int i = 1; i < clusters[0]->getClusterSize(); i++) {
	 auto hit = clusters[0]->getHit(i);
	 if (seed->getHitEnergy() < 4000) {
	 CorrectionCurve2GeV[hit->m_channel.component]->Fill(hit->getHitEnergy(), hit->getHitTime() - seed->getHitTime());
	 }
	 if (seed->getHitEnergy() >= 4000 && seed->getHitEnergy() < 6000) {
	 CorrectionCurve4GeV[hit->m_channel.component]->Fill(hit->getHitEnergy(), hit->getHitTime() - seed->getHitTime());
	 }
	 if (seed->getHitEnergy() > 6000) {
	 CorrectionCurve6GeV[hit->m_channel.component]->Fill(hit->getHitEnergy(), hit->getHitTime() - seed->getHitTime());
	 }
	 }
	 }
	 }*/

//Riempe istogramma 1D della distribuzione del tempo degli hit relativo al seed, per ogni Crystallo.
	/*	if (eventNumber > 1000000) {
	 if (clusters.size() == 1 && clusters_TimeCorr.size() == 1) {
	 auto seed = clusters[0]->getHit(0);
	 for (int i = 0; i < clusters[0]->getClusterSize(); i++) {
	 auto hit = clusters[0]->getHit(i);
	 CrystalTimeDistribution[hit->m_channel.component]->Fill(hit->getHitTime() - seed->getHitTime());
	 }
	 auto seed_corr = clusters_TimeCorr[0]->getHit(0);
	 for (int i = 0; i < clusters_TimeCorr[0]->getClusterSize(); i++) {
	 auto hit = clusters_TimeCorr[0]->getHit(i);
	 CrystalTimeDistribution_TimeCorr[hit->m_channel.component]->Fill(hit->getHitTime() - seed_corr->getHitTime());
	 }
	 }
	 }*/

//	TH2D Energia corretta vs Energia per ogni Crystallo
	/*	if (clusters.size() == 1 && clusters_EneCorr.size() == 1) {
	 if (clusters[0]->getClusterSize() == clusters_EneCorr[0]->getClusterSize()) {
	 for (int i = 0; i < clusters[0]->getClusterSize(); i++) {
	 auto hit = clusters[0]->getHit(i);
	 auto hit_EC = clusters_EneCorr[0]->getHit(i);
	 if (hit->m_channel.component == hit_EC->m_channel.component) {
	 EnergyVsCorrEnergy[hit->m_channel.component]->Fill(hit_EC->getHitEnergy(), hit->getHitEnergy());
	 }
	 }
	 }
	 }*/

	/*	Produce TH2D della posizione degli hit di eventi con hit nella colonna 12, con hit pesati per energia e tempo.
	 if (clusters.size() == 1) {
	 bool flag = false;
	 for (int i = 0; i < clusters[0]->getClusterSize(); i++) {
	 auto hit = clusters[0]->getHit(i);
	 if (hit->getHitIX() == 12) {
	 flag = true;
	 break;
	 }
	 }
	 if (flag == true) {
	 TH2D *hEvent = new TH2D(Form("hEvent%d", eventNumber), Form("hEvent%d", eventNumber), 25, -0.5, 24.5, 25, -0.5, 24.5);
	 auto seed = clusters[0]->getHit(0);
	 for (int i = 0; i < clusters[0]->getClusterSize(); i++) {
	 auto hit = clusters[0]->getHit(i);
	 if (hit->getHitTime() - seed->getHitTime() != 0) {
	 hEvent->Fill(hit->getHitIX(), hit->getHitIY(), hit->getHitTime() - seed->getHitTime());
	 } else {
	 hEvent->Fill(hit->getHitIX(), hit->getHitIY(), 1);
	 }
	 }
	 IntEvent.push_back(hEvent);
	 }
	 }*/

//Produce TH2D degli hit di eventi applicando o meno la correzione temporale, con hit pesati su tempo o energia . Produce anche istogrammi dei cluster.
	/*if (eventNumber >= firstEvent && eventNumber <= lastEvent && firstEvent != lastEvent) {
	 if (eventCounter < 50) {
	 eventCounter++;
	 TH2D *hHitsEnergy = new TH2D(Form("hHitsEnergy%d", eventNumber), Form("hHitsEnergy%d", eventNumber), 25, -0.5, 24.5, 25, -0.5, 24.5);
	 TH2D *hHitsTime = new TH2D(Form("hHitsTime%d", eventNumber), Form("hHitsTime%d", eventNumber), 25, -0.5, 24.5, 25, -0.5, 24.5);
	 TH2D *hClusterHitsEnergy = new TH2D(Form("hClusterHitsEnergy%d", eventNumber), Form("hClusterHitsEnergy%d", eventNumber), 25, -0.5, 24.5, 25, -0.5, 24.5);
	 TH2D *hClusterHitsTime = new TH2D(Form("hClusterHitsTime%d", eventNumber), Form("hClusterHitsTime%d", eventNumber), 25, -0.5, 24.5, 25, -0.5, 24.5);

	 TH2D *hClusterHitsEnergy_TimeCorr = new TH2D(Form("hClusterHitsEnergy_TimeCorr%d", eventNumber), Form("hClusterHitsEnergy_TimeCorr%d", eventNumber), 25, -0.5, 24.5, 25, -0.5, 24.5);
	 TH2D *hClusterHitsTime_TimeCorr = new TH2D(Form("hClusterHitsTime_TimeCorr%d", eventNumber), Form("hClusterHitsTime_TimeCorr%d", eventNumber), 25, -0.5, 24.5, 25, -0.5, 24.5);

	 TH2D *hTimeSpread = new TH2D(Form("hTimeSpread%d", eventNumber), Form("hTimeSpread%d", eventNumber), 25, -0.5, 24.5, 25, -0.5, 24.5);
	 for (auto hit : hits) {
	 hHitsEnergy->Fill(hit->getHitIX(), hit->getHitIY(), hit->getHitEnergy());
	 if (hit->getHitTime() != 0) {
	 hHitsTime->Fill(hit->getHitIX(), hit->getHitIY(), hit->getHitTime());
	 } else {
	 hHitsTime->Fill(hit->getHitIX(), hit->getHitIY(), 1);
	 }
	 }

	 for (auto cluster : clusters) {
	 for (int i = 0; i < cluster->getClusterSize(); i++) {
	 auto hit = cluster->getHit(i);
	 hClusterHitsEnergy->Fill(hit->getHitIX(), hit->getHitIY(), hit->getHitEnergy());
	 if (hit->getHitTime() != 0) {
	 hClusterHitsTime->Fill(hit->getHitIX(), hit->getHitIY(), hit->getHitTime());
	 } else {
	 hClusterHitsTime->Fill(hit->getHitIX(), hit->getHitIY(), 1);
	 }
	 }
	 }

	 for (auto cluster : clusters_TimeCorr) {
	 for (int i = 0; i < cluster->getClusterSize(); i++) {
	 auto hit = cluster->getHit(i);
	 hClusterHitsEnergy_TimeCorr->Fill(hit->getHitIX(), hit->getHitIY(), hit->getHitEnergy());
	 if (hit->getHitTime() != 0) {
	 hClusterHitsTime_TimeCorr->Fill(hit->getHitIX(), hit->getHitIY(), hit->getHitTime());
	 } else {
	 hClusterHitsTime_TimeCorr->Fill(hit->getHitIX(), hit->getHitIY(), 1);
	 }
	 }
	 }


	 auto seed = clusters[0]->getHit(0);
	 for (int i = 0; i < clusters[0]->getClusterSize(); i++) {
	 auto hit = clusters[0]->getHit(i);
	 if (hit->getHitTime() - seed->getHitTime() != 0) {
	 hTimeSpread->Fill(hit->getHitIX(), hit->getHitIY(), hit->getHitTime() - seed->getHitTime());
	 } else {
	 hTimeSpread->Fill(hit->getHitIX(), hit->getHitIY(), 1);
	 }

	 HitsEnergy.push_back(hHitsEnergy);
	 HitsTime.push_back(hHitsTime);
	 ClusterHitsEnergy.push_back(hClusterHitsEnergy);
	 ClusterHitsTime.push_back(hClusterHitsTime);

	 ClusterHitsEnergy_TimeCorr.push_back(hClusterHitsEnergy_TimeCorr);
	 ClusterHitsTime_TimeCorr.push_back(hClusterHitsTime_TimeCorr);

	 TimeWalkViewer.push_back(hTimeSpread);
	 }*/

//Single event time distribution, time corrected and not corrected.
	/*	if (eventNumber < 200) {
	 if (clusters_EneCorr.size() == 1 && clusters_TimeCorr.size() == 1) {
	 TH1D *hTimeDistribution = new TH1D(Form("hTimeDistribution%d", eventNumber), Form("hTimeDistribution%d", eventNumber), 45, -10.5, 34.5);
	 TH1D *hTimeDistribution_TimeCorr = new TH1D(Form("hTimeDistribution_TimeCorr%d", eventNumber), Form("hTimeDistribution_TimeCorr%d", eventNumber), 45, -10.5, 34.5);

	 auto seed_EneCorr = clusters_EneCorr[0]->getHit(0);
	 for (int i = 0; i < clusters_EneCorr[0]->getClusterSize(); i++) {
	 auto hit = clusters_EneCorr[0]->getHit(i);
	 hTimeDistribution->Fill(hit->getHitTime() - seed_EneCorr->getHitTime());
	 }

	 auto seed_TimeCorr = clusters_TimeCorr[0]->getHit(0);
	 for (int i = 0; i < clusters_TimeCorr[0]->getClusterSize(); i++) {
	 auto hit = clusters_TimeCorr[0]->getHit(i);
	 hTimeDistribution_TimeCorr->Fill(hit->getHitTime() - seed_TimeCorr->getHitTime());
	 }
	 TimeDistribution.push_back(hTimeDistribution);
	 TimeDistribution_TimeCorr.push_back(hTimeDistribution_TimeCorr);
	 }
	 }*/

//	Distribuzione per ogni Crystallo delle energie misurate, non corrette.
	/*	if (clusters.size() == 1) {
	 for (int i = 0; i < clusters[0]->getClusterSize(); i++) {
	 auto hit = clusters[0]->getHit(i);
	 CrystalEnergy[hit->m_channel.component]->Fill(hit->getHitEnergy());
	 }
	 }
	 if (clusters_EneCorr.size() == 1) {
	 for (int i = 0; i < clusters_EneCorr[0]->getClusterSize(); i++) {
	 auto hit = clusters_EneCorr[0]->getHit(i);
	 CrystalEnergy_corr[hit->m_channel.component]->Fill(hit->getHitEnergy());
	 }
	 }*/

//	Distribuzione aggregata dei ritardi degli hit dei cluster. Per eventi con 1 cluster e 1 cluster con tempi corretti, produce la distribuzione temporale degli hit del cluster per entrambi i casi.
	/*	if (clusters.size() == 1) {
	 auto seed = clusters[0]->getHit(0);
	 for (int i = 0; i < clusters[0]->getClusterSize(); i++) {
	 auto hit = clusters[0]->getHit(i);
	 hdTime->Fill(hit->getHitTime() - seed->getHitTime());
	 }
	 }
	 if (clusters_TimeCorr.size() == 1) {
	 auto seed_TimeCorr = clusters_TimeCorr[0]->getHit(0);
	 for (int i = 1; i < clusters_TimeCorr[0]->getClusterSize(); i++) {
	 auto hit = clusters_TimeCorr[0]->getHit(i);
	 hdTime_corr->Fill(hit->getHitTime() - seed_TimeCorr->getHitTime());
	 }
	 }

	 //	Distribuzione della molteplicità degli hit, per eventi ad 1 cluster.
	 if (clusters.size() == 1) {
	 hMoltHit->Fill(clusters[0]->getClusterSize());
	 }
	 if (clusters_TimeCorr.size() == 1) {
	 hMoltHit_corr->Fill(clusters_TimeCorr[0]->getClusterSize());
	 }

	 //	Distribuzione energia dei cluster, eventi ad 1 cluster.
	 if (clusters.size() == 1) {
	 hEneClus->Fill(clusters[0]->getClusterEnergy());
	 }
	 if (clusters_TimeCorr.size() == 1) {
	 hEneClus_corr->Fill(clusters_TimeCorr[0]->getClusterEnergy());
	 }

	 //	Distribuzione energia dei cluster, eventi a 2 cluster.
	 if (clusters.size() == 2) {
	 hEneClus_2ClusEvents->Fill(clusters[0]->getClusterEnergy());
	 hEneClus_2ClusEvents->Fill(clusters[1]->getClusterEnergy());
	 if (fabs(clusters[0]->getClusterTime() - clusters[1]->getClusterTime()) < 6) {
	 hEneClus_2ClusEvents_coinc->Fill(clusters[0]->getClusterEnergy());
	 hEneClus_2ClusEvents_coinc->Fill(clusters[1]->getClusterEnergy());
	 }
	 }
	 if (clusters_TimeCorr.size() == 2) {
	 hEneClus_2ClusEvents_corr->Fill(clusters_TimeCorr[0]->getClusterEnergy());
	 hEneClus_2ClusEvents_corr->Fill(clusters_TimeCorr[1]->getClusterEnergy());
	 if (fabs(clusters_TimeCorr[0]->getClusterTime() - clusters_TimeCorr[1]->getClusterTime()) < 6) {
	 hEneClus_2ClusEvents_corr_coinc->Fill(clusters_TimeCorr[0]->getClusterEnergy());
	 hEneClus_2ClusEvents_corr_coinc->Fill(clusters_TimeCorr[1]->getClusterEnergy());
	 }
	 }
	 //	Distribuzione del tempo del cluster rispetto al seed, eventi ad 1 cluster
	 if (clusters.size() == 1) {
	 hTimeClus->Fill(clusters[0]->getClusterTime() - clusters[0]->getHit(0)->getHitTime());
	 }
	 if (clusters_TimeCorr.size() == 1) {
	 hTimeClus_corr->Fill(clusters_TimeCorr[0]->getClusterTime() - clusters_TimeCorr[0]->getHit(0)->getHitTime());
	 }

	 //	Distributzione energia dei seed, eventi ad 1 cluster.
	 if (clusters.size() == 1) {
	 hEneSeed->Fill(clusters[0]->getClusterSeedEnergy());
	 }
	 if (clusters_TimeCorr.size() == 1) {
	 hEneSeed_corr->Fill(clusters_TimeCorr[0]->getClusterSeedEnergy());
	 }

	 hMoltClus->Fill(clusters.size());
	 hMoltClus_corr->Fill(clusters_TimeCorr.size());

	 //	Molteplicità degli hit vs energia del cluster
	 if (clusters.size() == 1) {
	 hMoltHitVsEnergyClus->Fill(clusters[0]->getClusterEnergy(), clusters[0]->getClusterSize());
	 }
	 if (clusters_TimeCorr.size() == 1) {
	 hMoltHitVsEnergyClus_corr->Fill(clusters_TimeCorr[0]->getClusterEnergy(), clusters_TimeCorr[0]->getClusterSize());
	 }

	 //	Molteplicità degli hit vs Component del Seed
	 /*	 if (clusters.size() == 1) {
	 hMoltHitVsComponentSeed->Fill(clusters[0]->getHit(0)->m_channel.component, clusters[0]->getClusterSize());
	 }
	 if (clusters_TimeCorr.size() == 1) {
	 hMoltHitVsComponentSeed_corr->Fill(clusters_TimeCorr[0]->getHit(0)->m_channel.component, clusters_TimeCorr[0]->getClusterSize());
	 hMolHitVsXVsY->Fill(clusters_TimeCorr[0]->getCentroid().X(), clusters_TimeCorr[0]->getCentroid().Y(), clusters_TimeCorr[0]->getClusterSize());
	 }*/

// Molteplicità hit nell'evento vs molteplicità hit nel cluster
	/*	if (clusters.size() == 1) {
	 hMoltEventVsMoltHit->Fill(hits.size(), clusters[0]->getClusterSize());
	 }*/

//	ClustersPosition
	/*	if (clusters.size() == 1) {
	 hSeedPosition->Fill(clusters[0]->getHit(0)->getHitIX(), clusters[0]->getHit(0)->getHitIY());
	 hClusterPosition->Fill(clusters[0]->getX(), clusters[0]->getY());
	 hEnergyPosition->Fill(clusters[0]->getX(), clusters[0]->getY(), clusters[0]->getClusterEnergy());
	 }
	 if (clusters_TimeCorr.size() == 1) {
	 hSeedPosition_corr->Fill(clusters_TimeCorr[0]->getHit(0)->getHitIX(), clusters_TimeCorr[0]->getHit(0)->getHitIY());
	 hClusterPosition_corr->Fill(clusters_TimeCorr[0]->getX(), clusters_TimeCorr[0]->getY());
	 hEnergyPosition_corr->Fill(clusters_TimeCorr[0]->getX(), clusters_TimeCorr[0]->getY(), clusters_TimeCorr[0]->getClusterEnergy());
	 }

	 //	Energia del cluster vs energia del seed
	 if (clusters.size() == 1) {
	 hEneClusVsEneSeed->Fill(clusters[0]->getHit(0)->getHitEnergy() + clusters[0]->getHit(1)->getHitEnergy(), clusters[0]->getClusterEnergy());
	 //		if (clusters[0]->getHit(0)->getHitEnergy() > 9000) {
	 //			cout << "Cluster size " << clusters[0]->getClusterSize() * 1. << endl;
	 //			for (int i = 0; i < clusters[0]->getClusterSize(); i++) {
	 //				auto hit = clusters[0]->getHit(i);
	 //				cout << "Hit " << i * 1. << " X " << hit->getHitIX() * 1. << " Y " << hit->getHitIY() * 1. << " Energy " << hit->getHitEnergy() << endl;
	 //			}
	 //			cout << endl;
	 //		}
	 }
	 if (clusters_TimeCorr.size() == 1) {
	 hEneClusVsEneSeed_corr->Fill(clusters_TimeCorr[0]->getHit(0)->getHitEnergy() + clusters_TimeCorr[0]->getHit(1)->getHitEnergy(), clusters_TimeCorr[0]->getClusterEnergy());
	 //		if (clusters_TimeCorr[0]->getHit(0)->getHitEnergy() > 10000) {
	 //			hTest2->Fill(clusters_TimeCorr[0]->getHit(0)->getHitIX(), clusters_TimeCorr[0]->getHit(0)->getHitIY());
	 //			cout << "Cluster_TimeCorr size " << clusters_TimeCorr[0]->getClusterSize() * 1. << endl;
	 //			for (int i = 0; i < clusters_TimeCorr[0]->getClusterSize(); i++) {
	 //				auto hit = clusters_TimeCorr[0]->getHit(i);
	 //				cout << "Hit " << i * 1. << " X " << hit->getHitIX() * 1. << " Y " << hit->getHitIY() * 1. << " Energy " << hit->getHitEnergy() << endl;
	 //			}
	 //			cout << endl;
	 //		}
	 }

	 //	Rapporto tra energia del seed ed energia del cluster
	 if (clusters.size() == 1) {
	 hRatioESeedEClus->Fill(clusters[0]->getHit(0)->getHitEnergy() / clusters[0]->getClusterEnergy());
	 hRatioFirstTwoHit->Fill((clusters[0]->getHit(0)->getHitEnergy() + clusters[0]->getHit(1)->getHitEnergy()) / (clusters[0]->getClusterEnergy()));
	 hRatioESeedEClusVsClusEne->Fill(clusters[0]->getClusterEnergy(), clusters[0]->getHit(0)->getHitEnergy() / clusters[0]->getClusterEnergy());
	 hRatioFirstTwoHitVsClusEne->Fill(clusters[0]->getClusterEnergy(), (clusters[0]->getHit(0)->getHitEnergy() + clusters[0]->getHit(1)->getHitEnergy()) / (clusters[0]->getClusterEnergy()));

	 }
	 if (clusters_TimeCorr.size() == 1) {
	 hRatioESeedEClus_corr->Fill(clusters_TimeCorr[0]->getHit(0)->getHitEnergy() / clusters_TimeCorr[0]->getClusterEnergy());
	 hRatioFirstTwoHit_corr->Fill((clusters_TimeCorr[0]->getHit(0)->getHitEnergy() + clusters_TimeCorr[0]->getHit(1)->getHitEnergy()) / clusters_TimeCorr[0]->getClusterEnergy());
	 hRatioESeedEClusVsClusEne_corr->Fill(clusters_TimeCorr[0]->getClusterEnergy(), clusters_TimeCorr[0]->getHit(0)->getHitEnergy() / clusters_TimeCorr[0]->getClusterEnergy());
	 hRatioFirstTwoHitVsClusEne_corr->Fill(clusters_TimeCorr[0]->getClusterEnergy(),
	 (clusters_TimeCorr[0]->getHit(0)->getHitEnergy() + clusters_TimeCorr[0]->getHit(1)->getHitEnergy()) / clusters_TimeCorr[0]->getClusterEnergy());
	 }

	 //	Energia del seed vs angolo polare
	 if (clusters.size() == 1) {
	 hSeedEnergyVsTheta->Fill(clusters[0]->getCentroid().Theta() * 180 / M_PI, clusters[0]->getHit(0)->getHitEnergy());
	 }
	 if (clusters_TimeCorr.size() == 1) {
	 hSeedEnergyVsTheta_corr->Fill(clusters_TimeCorr[0]->getCentroid().Theta() * 180 / M_PI, clusters_TimeCorr[0]->getHit(0)->getHitEnergy());
	 }

	 /*	if (clusters_TimeCorr.size() == 1) {
	 for (int i = 0; i < clusters_TimeCorr[0]->getClusterSize(); i++) {
	 auto hit = clusters_TimeCorr[0]->getHit(i);
	 dTimeVsEne[hit->m_channel.component]->Fill(hit->getTimeWalkCorrection(), hit->getHitEnergy());
	 }
	 }*/

//	Produce la distribuzione energetica dei cluster in funzione del coseno dell'angolo polare, per eventi con tempo corretto.
	/*	if (clusters.size() == 1 && clusters_TimeCorr.size() == 1) {
	 if (clusters[0]->getCentroid().Theta() * 180 / M_PI >= 2.7 && clusters[0]->getCentroid().Theta() * 180 / M_PI <= 3.8) {
	 hClusterEnergyVsTheta->Fill(clusters[0]->getCentroid().Theta() * 180 / M_PI, clusters[0]->getClusterEnergy());
	 }
	 if (clusters_TimeCorr[0]->getCentroid().Theta() * 180 / M_PI >= 2.7 && clusters_TimeCorr[0]->getCentroid().Theta() * 180 / M_PI <= 3.8) {
	 hClusterEnergyVsTheta_TimeCorr->Fill(clusters_TimeCorr[0]->getCentroid().Theta() * 180 / M_PI, clusters_TimeCorr[0]->getClusterEnergy());
	 }
	 }

	 //	Eventi a due cluster, distribuzione dei tempi
	 if (clusters.size() == 2) {
	 h2ClusTimeDist->Fill(clusters[0]->getClusterTime() - clusters[1]->getClusterTime());
	 }
	 if (clusters_TimeCorr.size() == 2) {
	 h2ClusTimeDist_corr->Fill(clusters_TimeCorr[0]->getClusterTime() - clusters_TimeCorr[1]->getClusterTime());
	 }
	 */

//	Molteplicità dei cluster per eventi a 2 cluster
	/*if (clusters_EneCorr.size() == 2) {
	 auto cluster1 = clusters_EneCorr[0];
	 auto cluster2 = clusters_EneCorr[1];
	 if (abs(cluster1->getClusterTime() - cluster2->getClusterTime()) < 3) {
	 hMoltClus1->Fill(cluster1->getClusterSize());
	 hMoltClus2->Fill(cluster2->getClusterSize());
	 hMoltClus1VsEneClus1->Fill(cluster1->getClusterFullEnergy(), cluster1->getClusterSize());
	 hMoltClus2VsEneClus2->Fill(cluster2->getClusterFullEnergy(), cluster2->getClusterSize());
	 hMoltClus1VsMoltClus2->Fill(cluster1->getClusterSize(), cluster2->getClusterSize());
	 hEneClus1->Fill(cluster1->getClusterFullEnergy());
	 hEneClus2->Fill(cluster2->getClusterFullEnergy());
	 hEneClus1VsEneClus2->Fill(cluster1->getClusterFullEnergy(), cluster2->getClusterFullEnergy());
	 }
	 }

	 //	Istogramma della molteplicità degli hit vs energia del cluster; versione senza correzione e con correzione.
	 //	Pi0 mass find
	 if (clusters_EneCorr.size() == 2) {
	 auto cluster1 = clusters_EneCorr[0];
	 auto cluster2 = clusters_EneCorr[1];
	 auto z = cos(cluster1->getCentroid().Angle(cluster2->getCentroid()));
	 auto M = sqrt(2 * cluster1->getClusterFullEnergy() * cluster2->getClusterFullEnergy() * (1 - z));
	 if ((cluster1->getClusterFullEnergy() + cluster2->getClusterFullEnergy()) < 11000) { //&& (cluster1->getClusterFullEnergy() + cluster2->getClusterFullEnergy()) > 6000
	 if (abs(cluster1->getClusterTime() - cluster2->getClusterTime()) < 3) { //&& (cluster1->getClusterFullEnergy() + cluster2->getClusterFullEnergy()) > 6000
	 hInvMass->Fill(M);
	 hZDistribution->Fill(1 - z);
	 h2E1E2Distribution->Fill(sqrt(2 * cluster1->getClusterFullEnergy() * cluster2->getClusterFullEnergy()));
	 h2E1E2SeedDistribution->Fill(sqrt(2 * cluster1->getClusterSeedEnergy() * cluster2->getClusterSeedEnergy()));
	 if ((cluster1->getClusterFullEnergy() + cluster2->getClusterFullEnergy()) > 4000) {
	 hInvMass_Emin4->Fill(M);
	 }
	 if ((cluster1->getClusterFullEnergy() + cluster2->getClusterFullEnergy()) > 4500) {
	 hInvMass_Emin4_5->Fill(M);
	 }
	 if ((cluster1->getClusterFullEnergy() + cluster2->getClusterFullEnergy()) > 5000) {
	 hInvMass_Emin5->Fill(M);
	 }
	 if ((cluster1->getClusterFullEnergy() + cluster2->getClusterFullEnergy()) > 5500) {
	 hInvMass_Emin5_5->Fill(M);
	 }
	 if ((cluster1->getClusterFullEnergy() + cluster2->getClusterFullEnergy()) > 6000) {
	 hInvMass_Emin6->Fill(M);
	 }
	 if ((cluster1->getClusterFullEnergy() + cluster2->getClusterFullEnergy()) > 6500) {
	 hInvMass_Emin6_5->Fill(M);
	 }
	 if ((cluster1->getClusterFullEnergy() + cluster2->getClusterFullEnergy()) > 7000) {
	 hInvMass_Emin7->Fill(M);
	 }
	 if (M > 50 && M < 150) {
	 hZDistribution_peak->Fill(1 - z);
	 hInvMassVsClus1Ene->Fill(cluster1->getClusterFullEnergy(), M);
	 hInvMassVsClus2Ene->Fill(cluster2->getClusterFullEnergy(), M);
	 hInvMassVsSeed1Ene->Fill(cluster1->getClusterSeedEnergy(), M);
	 hInvMassVsSeed2Ene->Fill(cluster2->getClusterSeedEnergy(), M);
	 hOpeningAngle->Fill((cluster1->getCentroid().Angle(cluster2->getCentroid())) * 180 / M_PI);
	 hRelativeAngle->Fill(cluster1->getCentroid().Theta() * 180 / M_PI, cluster2->getCentroid().Theta() * 180 / M_PI);
	 hInvMassVsdTime->Fill(cluster1->getClusterTime() - cluster2->getClusterTime(), M);
	 }
	 if (M > 96 && M < 105) {
	 hPeak1Energies->Fill(cluster1->getClusterFullEnergy(), cluster2->getClusterFullEnergy());
	 hPeak1OpeningAngle->Fill((cluster1->getCentroid().Angle(cluster2->getCentroid())) * 180 / M_PI);
	 hPeak1Position->Fill(cluster1->getX(), cluster1->getY());
	 hPeak1Position->Fill(cluster2->getX(), cluster2->getY());
	 } else if (M > 114 && M < 122) {
	 hPeak2Energies->Fill(cluster1->getClusterFullEnergy(), cluster2->getClusterFullEnergy());
	 hPeak2OpeningAngle->Fill((cluster1->getCentroid().Angle(cluster2->getCentroid())) * 180 / M_PI);

	 hPeak2Position->Fill(cluster1->getX(), cluster1->getY());
	 hPeak2Position->Fill(cluster2->getX(), cluster2->getY());
	 } else {
	 hOffPeakEnergies->Fill(cluster1->getClusterFullEnergy(), cluster2->getClusterFullEnergy());
	 hOffPeakOpeningAngle->Fill((cluster1->getCentroid().Angle(cluster2->getCentroid())) * 180 / M_PI);
	 }

	 if (M > 95 && M < 125) {
	 hInvMassPion->Fill(M);
	 }
	 if (M > 80 && M < 95) {
	 hInvMassSideband->Fill(M + 15);
	 }
	 if (M > 125 && M < 140) {
	 hInvMassSideband->Fill(M - 15);
	 }
	 auto dist = (clusters_EneCorr[0]->getCentroid() - clusters_EneCorr[1]->getCentroid()).Mag();
	 if (dist > 30 && dist < 100) {
	 hInvMass_1bump->Fill(M);
	 } else if (dist > 170 && dist < 280) {
	 hInvMass_2bump->Fill(M);
	 } else {
	 hInvMass_off->Fill(M);
	 }

	 }
	 if (cluster1->getClusterTime() - cluster2->getClusterTime() < 150 && cluster1->getClusterTime() - cluster2->getClusterTime() > 144) {
	 hInvMass_sideband150P->Fill(M);
	 }
	 if (cluster1->getClusterTime() - cluster2->getClusterTime() > -150 && cluster1->getClusterTime() - cluster2->getClusterTime() < -144) {
	 hInvMass_sideband150N->Fill(M);
	 }
	 if (cluster1->getClusterTime() - cluster2->getClusterTime() < 120 && cluster1->getClusterTime() - cluster2->getClusterTime() > 114) {
	 hInvMass_sideband120P->Fill(M);
	 }
	 if (cluster1->getClusterTime() - cluster2->getClusterTime() > -120 && cluster1->getClusterTime() - cluster2->getClusterTime() < -114) {
	 hInvMass_sideband120N->Fill(M);
	 }
	 if (cluster1->getClusterTime() - cluster2->getClusterTime() < 80 && cluster1->getClusterTime() - cluster2->getClusterTime() > 74) {
	 hInvMass_sideband080P->Fill(M);
	 }
	 if (cluster1->getClusterTime() - cluster2->getClusterTime() > -80 && cluster1->getClusterTime() - cluster2->getClusterTime() < -74) {
	 hInvMass_sideband080N->Fill(M);
	 }
	 if (cluster1->getClusterTime() - cluster2->getClusterTime() < 40 && cluster1->getClusterTime() - cluster2->getClusterTime() > 34) {
	 hInvMass_sideband040P->Fill(M);
	 }
	 if (cluster1->getClusterTime() - cluster2->getClusterTime() > -40 && cluster1->getClusterTime() - cluster2->getClusterTime() < -34) {
	 hInvMass_sideband040N->Fill(M);
	 }
	 }
	 }

	 /*	Stampa su terminale un po' di numeri comodi per capire se la factory standar e la factory time_corr funzionano bene.
	 if (clusters.size() == 1 && clusters_TimeCorr.size() == 1) {
	 cout << "Id " << clusters[0]->getClusterId() << " " << clusters_TimeCorr[0]->getClusterId() << endl;
	 cout << "Size " << clusters[0]->getClusterSize() << " " << clusters_TimeCorr[0]->getClusterSize() << endl;
	 cout << "Energy " << clusters[0]->getClusterEnergy() << " " << clusters_TimeCorr[0]->getClusterEnergy() << endl;
	 cout << "Time " << clusters[0]->getClusterTime() << " " << clusters_TimeCorr[0]->getClusterTime() << endl;
	 cout << "X " << clusters[0]->getCentroid().X() << " " << clusters_TimeCorr[0]->getCentroid().X() << endl;
	 cout << "Y " << clusters[0]->getCentroid().Y() << " " << clusters_TimeCorr[0]->getCentroid().Y() << endl;
	 cout << "Y " << clusters[0]->getCentroid().Z() << " " << clusters_TimeCorr[0]->getCentroid().Z() << endl << endl;
	 }*/

//	Correzioni applicate su ogni Crystallo
	/*	if (clusters_TimeCorr.size() == 1) {
	 for (int i = 0; i < clusters_TimeCorr[0]->getClusterSize(); i++) {
	 auto hit = clusters_TimeCorr[0]->getHit(i);
	 CrystalTimeCorrection[hit->m_channel.component]->Fill(hit->getTimeWalkCorrection());
	 }
	 }*/

//					TH2D *hPeak1Event = new TH2D(Form("hPeak1Event%d", eventNumber), Form("hPeak1Event%d", eventNumber), 25, -0.5, 24.5, 25, -0.5, 24.5);
//					for (int i = 0; i < cluster1->getClusterSize(); i++) {
//						auto hit = cluster1->getHit(i);
//						hPeak1Event->Fill(hit->getHitIX(), hit->getHitIY(), hit->getHitEnergy());
//					}
//					for (int i = 0; i < cluster2->getClusterSize(); i++) {
//						auto hit = cluster2->getHit(i);
//						hPeak1Event->Fill(hit->getHitIX(), hit->getHitIY(), hit->getHitEnergy());
//					}
//					PeakEvents.push_back(hPeak1Event);
//					TH2D *hPeak2Event = new TH2D(Form("hPeak2Event%d", eventNumber), Form("hPeak2Event%d", eventNumber), 25, -0.5, 24.5, 25, -0.5, 24.5);
//					for (int i = 0; i < cluster1->getClusterSize(); i++) {
//						auto hit = cluster1->getHit(i);
//						hPeak2Event->Fill(hit->getHitIX(), hit->getHitIY(), hit->getHitEnergy());
//					}
//					for (int i = 0; i < cluster2->getClusterSize(); i++) {
//						auto hit = cluster2->getHit(i);
//						hPeak2Event->Fill(hit->getHitIX(), hit->getHitIY(), hit->getHitEnergy());
//					}
//					PeakEvents.push_back(hPeak2Event);
	tout->Fill();
	m_root_lock->release_lock();
//unlock

}

//------------------
// Finish
//------------------
void JEventProcessor_HallBFT_Mariangela::Finish(void) {
// This is called when at the end of event processing

//	hEnergyPosition->Divide(hClusterPosition);
//	hEnergyPosition_corr->Divide(hClusterPosition_corr);

	hHitsEnergyPosition->Divide(hHitsPosition);
	hSCEnergyPosition->Divide(hSCClusterPosition);
	hDCEnergyPosition->Divide(hDCClusterPosition);

//	hInvMassPion->Add(hInvMassSideband, -1);

	auto app = japp;
	std::string outFileName;
	TFile *fout;
	if (app->GetJParameterManager()->Exists("hallBFT_Mariangela:output_file") == true) {
		gROOT->cd();
		TDirectory *main = gDirectory;

		app->GetJParameterManager()->GetParameter("hallBFT_Mariangela:output_file", outFileName);
		std::cout << "JEventProcessor_HallBFT_Mariangela::Finish " << this << " " << outFileName << std::endl;
		fout = new TFile(outFileName.c_str(), "recreate");

		main->cd("HallBFT_Mariangela");
		TIter next(gDirectory->GetList());
		TObject* object = 0;
		fout->cd();

		while (object = next()) {
			if (object->InheritsFrom(TH1::Class())) {
				fout->cd();
				object->Write();
				std::cout << "JEventProcessor_HallBFT_Mariangela::wrote " << object->GetName() << std::endl;
			}
			if (object->InheritsFrom(TTree::Class())){
				fout->cd();
				object->Write();
				std::cout << "JEventProcessor_HallBFT_Mariangela::wrote " << object->GetName() << std::endl;
			}
		}

		fout->Write();
		fout->Close();
	}
}
