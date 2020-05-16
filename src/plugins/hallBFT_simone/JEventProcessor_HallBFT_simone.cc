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

using namespace std;

/*Here goes the histograms*/
static TH1D *hTest = 0; //Cancello tutto, posso sempre recuperarli da hallBFT_monitoring. Lascio solo htest
static TH1D *hdTimeHit = 0;
static TH1D *hdTimeHitSel1GeV = 0;
static TH1D *hdTimeCluster = 0;
static TH1D *hdTimeClusterSelSeed60 = 0;
static TH1D *hdTimeClusterSelSeed70 = 0;
static TH1D *hdTimeClusterSelSeed75 = 0;
static TH1D *hdTimeClusterSelSeed80 = 0;
static TH1D *hdTimeClusterSelSeed85 = 0;
static TH1D *hdTimeClusterSelSeed90 = 0;
static TH1D *hdTimeClusterSelSeed95 = 0;
static TH1D *hdTimeClusterSelSeed99 = 0;

static TH1D *hdTimeClusterSel1GeV = 0;
static TH1D *hdTimeClusterSel1GeVSelSeed = 0;
static TH1D *hdTimeClusterSel2GeV = 0;
static TH1D *hdTimeClusterSel3GeV = 0;
static TH1D *hdTimeClusterSel5GeV = 0;
static TH1D *hdTimeClusterSel6GeV = 0;

static TH2D *hClusterPosition = 0;
static TH2D *hClusterPositionDTimeSimm = 0;
static TH2D *hClusterPositionDTimeCas = 0;

static TH1D *hMinvAllPairAll = 0;
static TH1D *hMinvAllPair1GeV = 0;
static TH1D *hMinvAllPair2GeV = 0;
static TH1D *hMinvAllPair3GeV = 0;

static TH1D *hMinvAllPair = 0;
static TH1D *hMinvAllPair2C2G = 0;
static TH1D *hMinvAllPair3C2G = 0;
static TH1D *hMinvAllPair2C3G = 0;
static TH1D *hMinvAllPair3C3G = 0;

static TH1D *hMinvClosePair = 0;
static TH1D *hMinvClosePair2C2G = 0;
static TH1D *hMinvClosePair3C2G = 0;
static TH1D *hMinvClosePair2C3G = 0;
static TH1D *hMinvClosePair3C3G = 0;

static TH1D *hMinvClosePairSelTime = 0;
static TH1D *hMinvClosePairSelTime2C2G = 0;
static TH1D *hMinvClosePairSelTime3C2G = 0;
static TH1D *hMinvClosePairSelTime2C3G = 0;
static TH1D *hMinvClosePairSelTime3C3G = 0;

static TH1D *hMinvPiccoAll = 0;
static TH1D *hMinvPiccoClose = 0;
static TH1D *hMinvPicco2C3G = 0;
static TH1D *hMinvPicco2C4G = 0;
static TH1D *hDTimeThirdClusterPicco = 0;

static TH1D* hECluster2Cluster1GeV = 0;
static TH1D* hEHit2Cluster1GeV = 0;
static TH1D* hMinv2C2GeV30ns = 0;
static TH1D* hMinvSideband = 0;
static TH1D* hMinvRapportoSideband = 0;
static TH1D* hHitEnergy = 0;
static TH1D* hAllHitEnergy = 0;
//static TH3D* hdTimeVsPosition=0;

//static TH2D *hClustersVsEventNumber = 0;
//static TH2D *hDeltaTimeClusterVeEventNumber = 0;


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

	hdTimeHit = new TH1D("hdTimeHit", "hdTimeHit", 260, -10.5, 259.5);
	hdTimeHitSel1GeV = new TH1D("hdTimeHitSel1GeV", "hdTimeHitSel1GeV", 1001, -500, 500);
	hdTimeCluster = new TH1D("hdTimeCluster", "hdTimeCluster", 260, -10.5, 259.5);
	hdTimeClusterSel1GeV = new TH1D("hdTimeClusterSel1GeV", "hdTimeClusterSel1GeV", 1001, -500, 500);
	hdTimeClusterSel2GeV = new TH1D("hdTimeClusterSel2GeV", "hdTimeClusterSel2GeV", 1001, -500, 500);
	hdTimeClusterSel3GeV = new TH1D("hdTimeClusterSel3GeV", "hdTimeClusterSel3GeV", 1001, -500, 500);
	hdTimeClusterSel5GeV = new TH1D("hdTimeClusterSel5GeV", "hdTimeClusterSel5GeV", 1001, -500, 500);
	hdTimeClusterSel6GeV = new TH1D("hdTimeClusterSel6GeV", "hdTimeClusterSel6GeV", 1001, -500, 500);

	hdTimeClusterSelSeed60 = new TH1D("hdTimeClusterSelSeed60", "hdTimeClusterSelSeed60", 1001, -500, 500);
	hdTimeClusterSelSeed70 = new TH1D("hdTimeClusterSelSeed70", "hdTimeClusterSelSeed70", 1001, -500, 500);
	hdTimeClusterSelSeed75 = new TH1D("hdTimeClusterSelSeed75", "hdTimeClusterSelSeed75", 1001, -500, 500);
	hdTimeClusterSelSeed80 = new TH1D("hdTimeClusterSelSeed80", "hdTimeClusterSelSeed80", 1001, -500, 500);
	hdTimeClusterSelSeed85 = new TH1D("hdTimeClusterSelSeed85", "hdTimeClusterSelSeed85", 1001, -500, 500);
	hdTimeClusterSelSeed90 = new TH1D("hdTimeClusterSelSeed90", "hdTimeClusterSelSeed90", 1001, -500, 500);
	hdTimeClusterSelSeed95 = new TH1D("hdTimeClusterSelSeed95", "hdTimeClusterSelSeed95", 1001, -500, 500);
	hdTimeClusterSelSeed99 = new TH1D("hdTimeClusterSelSeed99", "hdTimeClusterSelSeed99", 1001, -500, 500);
	hdTimeClusterSel1GeVSelSeed = new TH1D("hdTimeClusterSel1GeVSelSeed", "hdTimeClusterSel1GeVSelSeed", 1001, -500, 500);

	hClusterPosition = new TH2D("hClusterPosition", "hClusterPosition", 40, -200, 200, 40, -200, 200);
	hClusterPositionDTimeSimm = new TH2D("hClusterPositionDTimeSimm", "hClusterPositionDTimeSimm", 40, -200, 200, 40, -200, 200);
	hClusterPositionDTimeCas = new TH2D("hClusterPositionDTimeCas", "hClusterPositionDTimeCas", 40, -200, 200, 40, -200, 200);

	hMinvAllPairAll = new TH1D("hMinvAllPairAll", "hMinvAllPairAll", 200, 0, 1000);
	hMinvAllPair1GeV = new TH1D("hMinvAllPair1GeV", "hMinvAllPair1GeV", 200, 0, 1000);
	hMinvAllPair2GeV = new TH1D("hMinvAllPair2GeV", "hMinvAllPair2GeV", 200, 0, 1000);
	hMinvAllPair3GeV = new TH1D("hMinvAllPair3GeV", "hMinvAllPair3GeV", 200, 0, 1000);

	hMinvAllPair = new TH1D("hMinvAllPair", "hMinvAllPair", 200, 0, 1000);
	hMinvAllPair2C2G = new TH1D("hMinvAllPair2C2G", "hMinvAllPair2C2G", 200, 0, 1000);
	hMinvAllPair3C2G = new TH1D("hMinvAllPair3C2G", "hMinvAllPair3C2G", 200, 0, 1000);
	hMinvAllPair2C3G = new TH1D("hMinvAllPair2C3G", "hMinvAllPair2C3G", 200, 0, 1000);
	hMinvAllPair3C3G = new TH1D("hMinvAllPair3C3G", "hMinvAllPair3C3G", 200, 0, 1000);

	hMinvClosePair = new TH1D("hMinvClosePair", "hMinvClosePair", 200, 0, 1000);
	hMinvClosePair2C2G = new TH1D("hMinvClosePair2C2G", "hMinvClosePair2C2G", 200, 0, 1000);
	hMinvClosePair3C2G = new TH1D("hMinvClosePair3C2G", "hMinvClosePair3C2G", 200, 0, 1000);
	hMinvClosePair2C3G = new TH1D("hMinvClosePair2C3G", "hMinvClosePair2C3G", 200, 0, 1000);
	hMinvClosePair3C3G = new TH1D("hMinvClosePair3C3G", "hMinvClosePair3C3G", 200, 0, 1000);

	hMinvClosePairSelTime = new TH1D("hMinvClosePairSelTime", "hMinvClosePairSelTime", 200, 0, 1000);
	hMinvClosePairSelTime2C2G = new TH1D("hMinvClosePairSelTime2C2G", "hMinvClosePairSelTime2C2G", 200, 0, 1000);
	hMinvClosePairSelTime3C2G = new TH1D("hMinvClosePairSelTime3C2G", "hMinvClosePairSelTime3C2G", 200, 0, 1000);
	hMinvClosePairSelTime2C3G = new TH1D("hMinvClosePairSelTime2C3G", "hMinvClosePairSelTime2C3G", 200, 0, 1000);
	hMinvClosePairSelTime3C3G = new TH1D("hMinvClosePairSelTime3C3G", "hMinvClosePairSelTime3C3G", 200, 0, 1000);

	hMinvPiccoAll = new TH1D("hMinvPiccoAll", "hMinvPiccoAll", 200, 0, 1000);
	hMinvPiccoClose = new TH1D("hMinvPiccoClose", "hMinvPiccoClose", 200, 0, 1000);
	hMinvPicco2C3G = new TH1D("hMinvPicco2C3G", "hMinvPicco2C3G", 200, 0, 1000);
	hMinvPicco2C4G = new TH1D("hMinvPicco2C4G", "hMinvPicco2C4G", 200, 0, 1000);
	hDTimeThirdClusterPicco = new TH1D("hDTimeThirdClusterPicco", "hDTimeThirdClusterPicco", 1001, -500, 500);

	hECluster2Cluster1GeV = new TH1D("hECluster2Cluster1GeV", "hECluster2Cluster1GeV", 2000, 0, 10000);
	hEHit2Cluster1GeV = new TH1D("hEHit2Cluster1GeV", "hEHit2Cluster1GeV", 2000, 0, 10000);
	hMinv2C2GeV30ns = new TH1D("hMinv2C2GeV30ns", "hMinv2C2GeV30ns", 200, 0, 1000);
	hMinvSideband = new TH1D("hMinvSideband", "hMinvSideband", 200, 0, 1000);
	hMinvRapportoSideband = new TH1D("hMinvRapportoSideband", "hMinvRapportoSideband", 200, 0, 1000);
	hHitEnergy = new TH1D("hHitEnergy", "hHitEnergy", 2000, 0, 10000);
	hAllHitEnergy = new TH1D("hAllHitEnergy", "hAllHitEnergy", 2000, 0, 10000);

//	hdTimeVsPosition= new TH3D("hdTimeVsPosition","hdTimeVsPosition",40,-200,200,40,-200,200,500,0,500);

//	hClustersVsEventNumber = new TH2D("hClustersVsEventNumber", "hClustersVsEventNumber", 2000, 0, 2000, 20, -1.5, 18.5);
//	hDeltaTimeClusterVeEventNumber = new TH2D("hDeltaTimeClusterVeEventNumber", "hDeltaTimeClusterVeEventNumber", 2000000, 0, 20000000, 1001, -501, 501);


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
	auto hits = aEvent->Get<FTCalHit>(); //vector degli hits dell'evento
//	auto clusters = aEvent->Get < FTCalCluster > ("EneCorr"); //vector dei clusters dell'evento con correzione sull'energia degli hit
	auto clusters = aEvent->Get<FTCalCluster>();
	//	auto eventNumber = aEvent->GetEventNumber();

	//Variables
	int nCluster4GeV = 0;
	int nCluster3GeV = 0;
	int nCluster2GeV = 0;

	//Pion and electron identification variables declarations
	const FTCalCluster *gamma1;
	const FTCalCluster *gamma2;
	const FTCalCluster *electron;

	double dist_min = 1000000;
	double dTime_max = -1000;


	//lock
	m_root_lock->acquire_write_lock();


	if (hits.size() > 1) {
		for (int i = 0; i < hits.size(); i++) {
			auto hit1 = hits[i];
			for (int j = i+1; j < hits.size(); j++) {
				if (i != j) {
					auto hit2 = hits[j];
					hdTimeHit->Fill(abs(hit2->getHitTime() - hit1->getHitTime()));
					if (hit1->getHitEnergy() > 3000 && hit2->getHitEnergy() > 3000)
						hdTimeHitSel1GeV->Fill(hit2->getHitTime() - hit1->getHitTime());
				}
			}
		}
	}

	if (clusters.size() > 1) {
		for (int ii = 0; ii < clusters.size(); ii++) {
			auto cluster1 = clusters[ii];
			for (int jj = ii+1; jj < clusters.size(); jj++) {
				if (ii != jj) {
					auto cluster2 = clusters[jj];
					auto dtime = cluster2->getClusterTime() - cluster1->getClusterTime();
					hdTimeCluster->Fill(abs(dtime));
					if (cluster1->getClusterSeedEnergy() / cluster1->getClusterEnergy() > 0.6 && cluster2->getClusterSeedEnergy() / cluster2->getClusterEnergy() > 0.6) {
						hdTimeClusterSelSeed60->Fill(dtime);
					}
					if (cluster1->getClusterSeedEnergy() / cluster1->getClusterEnergy() > 0.7 && cluster2->getClusterSeedEnergy() / cluster2->getClusterEnergy() > 0.7) {
						hdTimeClusterSelSeed70->Fill(dtime);
					}
					if (cluster1->getClusterSeedEnergy() / cluster1->getClusterEnergy() > 0.75 && cluster2->getClusterSeedEnergy() / cluster2->getClusterEnergy() > 0.75) {
						hdTimeClusterSelSeed75->Fill(dtime);
					}
					if (cluster1->getClusterSeedEnergy() / cluster1->getClusterEnergy() > 0.8 && cluster2->getClusterSeedEnergy() / cluster2->getClusterEnergy() > 0.8) {
						hdTimeClusterSelSeed80->Fill(dtime);
					}
					if (cluster1->getClusterSeedEnergy() / cluster1->getClusterEnergy() > 0.85 && cluster2->getClusterSeedEnergy() / cluster2->getClusterEnergy() > 0.85) {
						hdTimeClusterSelSeed85->Fill(dtime);
					}
					if (cluster1->getClusterSeedEnergy() / cluster1->getClusterEnergy() > 0.90 && cluster2->getClusterSeedEnergy() / cluster2->getClusterEnergy() > 0.90) {
						hdTimeClusterSelSeed90->Fill(dtime);
					}
					if (cluster1->getClusterSeedEnergy() / cluster1->getClusterEnergy() > 0.95 && cluster2->getClusterSeedEnergy() / cluster2->getClusterEnergy() > 0.95) {
						hdTimeClusterSelSeed95->Fill(dtime);
					}
					if (cluster1->getClusterSeedEnergy() / cluster1->getClusterEnergy() > 0.99 && cluster2->getClusterSeedEnergy() / cluster2->getClusterEnergy() > 0.99) {
						hdTimeClusterSelSeed99->Fill(dtime);
					}
					if (cluster1->getClusterEnergy() > 1000 && cluster2->getClusterEnergy() > 1000) {
						hdTimeClusterSel1GeV->Fill(dtime);
						if (cluster1->getClusterSeedEnergy() / cluster1->getClusterEnergy() > 0.7 && cluster2->getClusterSeedEnergy() / cluster2->getClusterEnergy() > 0.7) {
							hdTimeClusterSel1GeVSelSeed->Fill(dtime);
						}
					}
					if (cluster1->getClusterEnergy() > 2000 && cluster2->getClusterEnergy() > 2000) {
						hdTimeClusterSel2GeV->Fill(dtime);
					}
					if (cluster1->getClusterEnergy() > 3000 && cluster2->getClusterEnergy() > 3000) {
						hdTimeClusterSel3GeV->Fill(dtime);
					}
					if (cluster1->getClusterEnergy() > 5000 && cluster2->getClusterEnergy() > 5000) {
						hdTimeClusterSel5GeV->Fill(dtime);
					}
					if (cluster1->getClusterEnergy() > 6000 && cluster2->getClusterEnergy() > 6000) {
						hdTimeClusterSel6GeV->Fill(dtime);
					}
					hClusterPosition->Fill(cluster1->getX(), cluster1->getY());
					if (abs(dtime) > 15 && abs(dtime) < 25) {
						hClusterPositionDTimeSimm->Fill(cluster1->getX(), cluster1->getY());
					}
					if (abs(dtime) > 80 && abs(dtime) < 90) {
						hClusterPositionDTimeCas->Fill(cluster1->getX(), cluster1->getY());
					}

//					hdTimeVsPosition->Fill(cluster1->getX(),cluster1->getY(),abs(dtime));
//					hdTimeVsPosition->Fill(cluster2->getX(),cluster2->getY(),abs(dtime));

//					hClustersVsEventNumber->Fill(eventNumber * 0.0001, clusters.size());
//					hDeltaTimeClusterVeEventNumber->Fill(eventNumber * 0.0001, dtime);
					if (abs(dtime) > dTime_max) {
						dTime_max = abs(dtime);
					}
				}
			}
			if (cluster1->getClusterEnergy() > 2000) {
				nCluster2GeV++;
			}
			if (cluster1->getClusterEnergy() > 3000) {
				nCluster3GeV++;
			}
			if (cluster1->getClusterEnergy() > 4000) {
				nCluster4GeV++;
			}
		}
	}

//	ANALISI Minv ristretta a picco 20 ns

	if (clusters.size() == 3) {
		double distMaxPicco = 100000000;
		auto dt1 = abs(clusters[0]->getClusterTime() - clusters[1]->getClusterTime());
		auto dt2 = abs(clusters[0]->getClusterTime() - clusters[2]->getClusterTime());
		bool flag1 = false;
		bool flag2 = false;
		bool dist_flag = false;
		int pho1, pho2, pi;
		double Minv;
		if (dt1 < 2 || (dt1 > 18 && dt1 < 22))
			flag1 = true;
		if (dt2 < 2 || (dt2 > 18 && dt2 < 22))
			flag2 = true;

		if (flag1 == true)
			hDTimeThirdClusterPicco->Fill(dt2);
		if (flag2 == true)
			hDTimeThirdClusterPicco->Fill(dt1);

		for (int i = 0; i < clusters.size(); i++) {
			auto cluster1 = clusters[i];
			for (int j = i + 1; j < clusters.size(); j++) {
				auto cluster2 = clusters[j];
				auto z = cos(cluster1->getCentroid().Angle(cluster2->getCentroid()));
				auto M = sqrt(2 * cluster1->getClusterEnergy() * cluster2->getClusterEnergy() * (1 - z));
				hMinvPiccoAll->Fill(M);
				auto dist = (cluster2->getCentroid() - cluster1->getCentroid()).Mag();
				if (dist < distMaxPicco) {
					dist_flag = true;
					dist_min = dist;
					pho1 = i;
					pho2 = j;
					Minv = M;
					for (int z = 0; z < 3; z++)
						if (z != i && z != j)
							pi = 0;
				}
			}
			if (dist_flag == true && flag1 == true && flag2 == true)
				hMinvPiccoClose->Fill(Minv);
			if (dist_flag == true && flag1 == true && flag2 == true && nCluster3GeV == 2)
				hMinvPicco2C3G->Fill(Minv);
			if (dist_flag == true && flag1 == true && flag2 == true && nCluster4GeV == 2)
				hMinvPicco2C4G->Fill(Minv);

		}
	}

//	Analisi ristretta ad eventi con esattamente 3 cluster!

	if (clusters.size() == 3) {
		bool flag = false;
		hTest->Fill(0);
		for (int i = 0; i < clusters.size(); i++) {
			auto cluster1 = clusters[i];
			for (int j = i + 1; j < clusters.size(); j++) {
				auto cluster2 = clusters[j];
				auto z = cos(cluster1->getCentroid().Angle(cluster2->getCentroid()));
				auto M = sqrt(2 * cluster1->getClusterEnergy() * cluster2->getClusterEnergy() * (1 - z));
				hMinvAllPair->Fill(M);
				if (nCluster2GeV >= 2) {
					hMinvAllPair2C2G->Fill(M);
				}
				if (nCluster2GeV >= 3) {
					hMinvAllPair3C2G->Fill(M);
				}
				if (nCluster3GeV >= 2) {
					hMinvAllPair2C3G->Fill(M);
				}
				if (nCluster3GeV >= 3) {
					hMinvAllPair3C3G->Fill(M);
				}
				auto dist = (cluster2->getCentroid() - cluster1->getCentroid()).Mag();
				if (dist < dist_min) {
					flag = true;
					dist_min = dist;
					for (int z = 0; z < clusters.size(); z++) {
						if (z == i) {
							gamma1 = clusters[z];
						} else if (z == j) {
							gamma2 = clusters[z];
						} else {
							electron = clusters[z];
						}
					}

				}
			}
		}

		if (flag == true) {
			auto z_close = cos(gamma1->getCentroid().Angle(gamma2->getCentroid()));
			auto M_close = sqrt(2 * gamma1->getClusterEnergy() * gamma2->getClusterEnergy() * (1 - z_close));
			hMinvClosePair->Fill(M_close);
			if (nCluster2GeV >= 2) {
				hMinvClosePair2C2G->Fill(M_close);
			}
			if (nCluster2GeV >= 3) {
				hMinvClosePair3C2G->Fill(M_close);
			}
			if (nCluster3GeV >= 2) {
				hMinvClosePair2C3G->Fill(M_close);
			}
			if (nCluster3GeV >= 3) {
				hMinvClosePair3C3G->Fill(M_close);
			}

		}
		if (flag == true && dTime_max < 50) {
			auto z_close = cos(gamma1->getCentroid().Angle(gamma2->getCentroid()));
			auto M_close = sqrt(2 * gamma1->getClusterEnergy() * gamma2->getClusterEnergy() * (1 - z_close));
			hMinvClosePairSelTime->Fill(M_close);
			if (nCluster2GeV >= 2) {
				hMinvClosePairSelTime2C2G->Fill(M_close);
			}
			if (nCluster2GeV >= 3) {
				hMinvClosePairSelTime3C2G->Fill(M_close);
			}
			if (nCluster3GeV >= 2) {
				hMinvClosePairSelTime2C3G->Fill(M_close);
			}
			if (nCluster3GeV >= 3) {
				hMinvClosePairSelTime3C3G->Fill(M_close);
			}
		}
	}

	//ANALISI DI TUTTI GLI EVENTI CON ALMENO 2 CLUSTER
	if (clusters.size() > 1) {
		hTest->Fill(1);
		for (int i = 0; i < clusters.size(); i++) {
			auto cluster1 = clusters[i];
			for (int j = i + 1; j < clusters.size(); j++) {
				auto cluster2 = clusters[j];
				auto z = cos(cluster1->getCentroid().Angle(cluster2->getCentroid()));
				auto M = sqrt(2 * cluster1->getClusterEnergy() * cluster2->getClusterEnergy() * (1 - z));

				hMinvAllPairAll->Fill(M);
				if (cluster1->getClusterEnergy() > 1000 && cluster2->getClusterEnergy() > 1000) {
					hMinvAllPair1GeV->Fill(M);
				}
				if (cluster1->getClusterEnergy() > 2000 && cluster2->getClusterEnergy() > 2000) {
					hMinvAllPair2GeV->Fill(M);
				}
				if (cluster1->getClusterEnergy() > 3000 && cluster2->getClusterEnergy() > 3000) {
					hMinvAllPair3GeV->Fill(M);
				}
			}
		}
	}

	/*	hECluster2Cluster1GeV=0;
	 hEHit2Cluster1GeV=0;
	 hMinv2C2GeV30ns=0;
	 hMinvSideband=0;
	 */

	if (clusters.size() == 2) {
		auto cluster1 = clusters[0];
		auto cluster2 = clusters[1];
		if (cluster1->getClusterEnergy() > 1000 && cluster2->getClusterEnergy() > 1000) {
			hECluster2Cluster1GeV->Fill(cluster1->getClusterEnergy());
			hECluster2Cluster1GeV->Fill(cluster2->getClusterEnergy());
			for (auto hit : hits) {
				if (cluster1->containsHit(hit) == true || cluster2->containsHit(hit) == true) {
					hEHit2Cluster1GeV->Fill(hit->getHitEnergy());
				}
			}
			auto dtime = abs(cluster1->getClusterTime() - cluster2->getClusterTime());
			if (cluster1->getClusterEnergy() > 2000 && cluster2->getClusterEnergy() > 2000 && dtime < 30) {
				auto z = cos(cluster1->getCentroid().Angle(cluster2->getCentroid()));
				auto M = sqrt(2 * cluster1->getClusterEnergy() * cluster2->getClusterEnergy() * (1 - z));
				hMinv2C2GeV30ns->Fill(M);
			}
			if (cluster1->getClusterEnergy() > 2000 && cluster2->getClusterEnergy() > 2000 && dtime < 90 && dtime >= 60) {
				auto z = cos(cluster1->getCentroid().Angle(cluster2->getCentroid()));
				auto M = sqrt(2 * cluster1->getClusterEnergy() * cluster2->getClusterEnergy() * (1 - z));
				hMinvSideband->Fill(M);
			}

		}
	}

	if (clusters.size() > 1) {
		for (auto hit : hits) {
			hHitEnergy->Fill(hit->getHitEnergy());
		}
	}
	for (auto hit : hits) {
		hAllHitEnergy->Fill(hit->getHitEnergy());
	}

	m_root_lock->release_lock();
//unlock


}

//------------------
// Finish
//------------------
void JEventProcessor_HallBFT_simone::Finish(void) {
// This is called when at the end of event processing


	hMinvRapportoSideband->Divide(hMinv2C2GeV30ns, hMinvSideband, 1, 1);


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
