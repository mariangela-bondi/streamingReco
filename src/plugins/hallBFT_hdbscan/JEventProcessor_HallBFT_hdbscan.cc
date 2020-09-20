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

#include "JEventProcessor_HallBFT_hdbscan.h"

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
#include "TLorentzVector.h"

using namespace std;

/*Here goes the histograms*/
static TH1D *hTest = 0;
//static TH2D *hTest2 = 0;
static vector<TH2D *> HitsEnergy;
static vector<TH2D *> HitsTime;
static vector<TH2D *> ClusterHitsEnergy;
static vector<TH2D *> ClusterHitsTime;
static vector<TH2D *> HitsEnergy_TimeCorr;
static vector<TH2D *> HitsTime_TimeCorr;
static vector<TH2D *> ClusterHitsEnergy_TimeCorr;
static vector<TH2D *> ClusterHitsTime_TimeCorr;
static vector<TH2D *> TimeWalkViewer;
static vector<TH1D *> TimeDistribution;
static vector<TH1D *> TimeDistribution_TimeCorr;
static vector<TH2D *> CorrectionCurve;
static vector<TH2D *> EnergyVsCorrEnergy;
static vector<TH2D *> TwentyNsSx;
static vector<TH2D *> TwentyNsDx;
static vector<TH1D *> CrystalTimeDistribution;
static vector<TH1D *> CrystalTimeDistribution_TimeCorr;
static vector<TH2D *> CorrectionCurve2GeV;
static vector<TH2D *> CorrectionCurve4GeV;
static vector<TH2D *> CorrectionCurve6GeV;
static vector<TH1D *> CrystalEnergy;
static vector<TH1D *> CrystalEnergy_corr;
static vector<TH1D *> CrystalTimeCorrection;
static vector<TH2D *> Radius0Events;
static vector<TH2D *> Dist15Events1Energy;
static vector<TH2D *> Dist15Events1Time;
static vector<TH2D *> Dist15Events2Energy;
static vector<TH2D *> Dist15Events2Time;

static TH2D *hSeedDx = 0;
static TH2D *hSeedSx = 0;

static vector<TH2D *> IntEvent;
static vector<TH2D *> dTimeVsEne;

static TH1D *hNhits = 0; //per event

static TH1D *hNhitsClu = 0; //per event
static TH1D *hNClu = 0; //per event
static TH1D *hNhitsClu_tcorr = 0; //per event
static TH1D *hNClu_tcorr = 0; //per event
static TH1D *hNhitsClu_tecorr = 0; //per event
static TH1D *hNClu_tecorr = 0; //per event
static TH1D *hNhitsClu_hdbscan = 0; //per event
static TH1D *hNClu_hdbscan = 0; //per event
static TH1D *hNhitsClu_tecorr_hdbscan = 0; //per event
static TH1D *hNClu_tecorr_hdbscan = 0; //per event
static TH1D *hNhitsClu_km = 0; //per event
static TH1D *hNClu_km = 0; //per event

static TH1D *hdTime = 0;
static TH1D *hdTime_corr = 0;
static TH1D *hMoltHit = 0;
static TH1D *hMoltHit_corr = 0;
static TH1D *hMoltClus = 0;
static TH1D *hMoltClus_corr = 0;
static TH1D *hEneClus = 0;
static TH1D *hEneClus_corr = 0;
static TH1D *hTimeClus = 0;
static TH1D *hTimeClus_corr = 0;
static TH1D *hEneSeed = 0;
static TH1D *hEneSeed_corr = 0;
static TH1D *h2ClusTimeDist = 0;
static TH1D *h2ClusTimeDist_corr = 0;
static TH2D *hClusterEnergyVsTheta = 0;
static TH2D *hClusterEnergyVsTheta_TimeCorr = 0;
static TH2D *hSeedEnergyVsTheta = 0;
static TH2D *hSeedEnergyVsTheta_corr = 0;

static TH1D *hEneClus_2ClusEvents = 0;
static TH1D *hEneClus_2ClusEvents_corr = 0;
static TH1D *hEneClus_2ClusEvents_coinc = 0;
static TH1D *hEneClus_2ClusEvents_corr_coinc = 0;

static TH2D *hSeedPosition = 0;
static TH2D *hSeedPosition_corr = 0;
static TH2D *hClusterPosition = 0;
static TH2D *hClusterPosition_corr = 0;
static TH2D *hEnergyPosition = 0;
static TH2D *hEnergyPosition_corr = 0;

static TH1D *hDigitalRadius = 0;
static TH1D *hDigitalRadius_corr = 0;
static TH2D *hDigitalRadiusVsClusEne = 0;
static TH2D *hDigitalRadiusVsClusEne_corr = 0;
static TH1D *hAnalogRadius = 0;
static TH1D *hAnalogRadius_corr = 0;
static TH2D *hAnalogRadiusVsClusEne = 0;
static TH2D *hAnalogRadiusVsClusEne_corr = 0;
static TH1D *hDist2Clus = 0;
static TH1D *hDist2Clus_corr = 0;
static TH1D *hDist2Clus_coinc = 0;
static TH1D *hDist2Clus_coinc_corr = 0;

static TH2D *hClus1EneVsClus2Ene = 0;
static TH2D *hClus1EneVsClus2Ene_coinc = 0;
static TH2D *hClus1EneVsClus2Ene_1bump = 0;
static TH2D *hClus1EneVsClus2Ene_1bump_coinc = 0;
static TH2D *hClus1EneVsClus2Ene_2bump = 0;
static TH2D *hClus1EneVsClus2Ene_2bump_coinc = 0;

static TH2D *h2ClusPosition = 0;
static TH2D *h2ClusPosition_coinc = 0;
static TH2D *h2ClusPosition_1bump = 0;
static TH2D *h2ClusPosition_1bump_coinc = 0;
static TH2D *h2ClusPosition_2bump = 0;
static TH2D *h2ClusPosition_2bump_coinc = 0;

static TH2D *hClusEneCorrVsClusEne = 0;
static TH2D *hSeedEneCorrVsSeedEne = 0;

static TH1D *hOpeningAngle = 0;
static TH1D *hOpeningAngle_1bump = 0;
static TH1D *hOpeningAngle_2bump = 0;
static TH1D *hOpeningAngle_off = 0;
static TH2D *hRelativeAngle = 0;
static TH2D *hRelativeAngle_1bump = 0;
static TH2D *hRelativeAngle_2bump = 0;
static TH2D *hRelativeAngle_off = 0;

//no corrections
static TH1D *hInvMass = 0;
static TH1D *hInvMass_1bump = 0;
static TH1D *hInvMass_2bump = 0;
static TH1D *hInvMass_off = 0;
//time corrections
static TH1D *hInvMass_tcorr = 0;
static TH1D *hInvMass_1bump_tcorr = 0;
static TH1D *hInvMass_2bump_tcorr = 0;
static TH1D *hInvMass_off_tcorr = 0;
//time+ene corrections
static TH1D *hInvMass_tecorr = 0;
static TH1D *hInvMass_1bump_tecorr  = 0;
static TH1D *hInvMass_2bump_tecorr  = 0;
static TH1D *hInvMass_off_tecorr  = 0;
//no corrections + hdbscan
static TH1D *hInvMass_hdbscan = 0;
static TH1D *hInvMass_1bump_hdbscan = 0;
static TH1D *hInvMass_2bump_hdbscan = 0;
static TH1D *hInvMass_off_hdbscan = 0;
//time+ene corrections + hdbscan
static TH1D *hInvMass_tecorr_hdbscan = 0;
static TH1D *hInvMass_1bump_tecorr_hdbscan = 0;
static TH1D *hInvMass_2bump_tecorr_hdbscan = 0;
static TH1D *hInvMass_off_tecorr_hdbscan = 0;
//no corrections + kmeans
static TH1D *hInvMass_km = 0;
static TH1D *hInvMass_1bump_km = 0;
static TH1D *hInvMass_2bump_km = 0;
static TH1D *hInvMass_off_km = 0;


//------ my analysis -----//

static TH1D * h_minv_combo_tecorr= 0;
static TH1D * h_minv_nocuts_combo_tecorr= 0;
static TH1D * h_minv_Ecuts_combo_tecorr= 0;
static TH1D * h_minv_Etotcuts_combo_tecorr= 0;
static TH1D * h_minv_ele_combo_tecorr= 0;
static TH1D * h_tcoinc_combo_tecorr= 0;

static TH1D * h_minv_combo_tecorr_hdbscan= 0;
static TH1D * h_minv_nocuts_combo_tecorr_hdbscan= 0;
static TH1D * h_minv_Ecuts_combo_tecorr_hdbscan= 0;
static TH1D * h_minv_Etotcuts_combo_tecorr_hdbscan= 0;
static TH1D * h_minv_ele_combo_tecorr_hdbscan= 0;
static TH1D * h_tcoinc_combo_tecorr_hdbscan= 0;


static TH1D * h_tcoinc= 0;


//static TH1D * h_tcoinc_combo= 0;

//Selezione eventi "basica"
const int firstEvent = 0;
const int lastEvent = 50;
static int eventCounter = 0;

//---------------------------------
// JEventProcessor_HallBFT_hdbscan    (Constructor)
//---------------------------------
JEventProcessor_HallBFT_hdbscan::JEventProcessor_HallBFT_hdbscan() {

}

//---------------------------------
// ~JEventProcessor_HallBFT_hdbscan    (Destructor)
//---------------------------------
JEventProcessor_HallBFT_hdbscan::~JEventProcessor_HallBFT_hdbscan() {

}


bool JEventProcessor_HallBFT_hdbscan::compareClusters(const FTCalCluster* a, const FTCalCluster* b) {
	//cout<<"Ea: "<< a->getClusterEnergy() << ", Eb: "<< b->getClusterEnergy() <<endl;
	return (a->getClusterEnergy() > b->getClusterEnergy());
}

//------------------
// Init
//------------------
void JEventProcessor_HallBFT_hdbscan::Init(void) {
	// This is called once at program startup.
	m_root_lock = japp->GetService<JGlobalRootLock>();

	m_root_lock->acquire_write_lock();
	if (hTest != NULL) {
		m_root_lock->release_lock();
		return;
	}

	gROOT->cd();
	TDirectory *main = gDirectory;
	gDirectory->mkdir("HallBFT_hdbscan")->cd();

	hNhits = new TH1D("hNhits", "hNhits", 30, -.5, 29.5);
	//no corr
	hNhitsClu = new TH1D("hNhitsClu", "hNhitsClu", 20, -.5, 19.5);
  hNClu = new TH1D("hNClu", "hNClu", 10, -.5, 9.5);
	//t corr
	hNhitsClu_tcorr = new TH1D("hNhitsClu_tcorr", "hNhitsClu", 20, -.5, 19.5);
  hNClu_tcorr = new TH1D("hNClu_tcorr", "hNClu", 10, -.5, 9.5);
	//t+e corr
	hNhitsClu_tecorr = new TH1D("hNhitsClu_tecorr", "hNhitsClu", 20, -.5, 19.5);
	hNClu_tecorr = new TH1D("hNClu_tecorr", "hNClu", 10, -.5, 9.5);
	//no corr + hdbscan
	hNhitsClu_hdbscan = new TH1D("hNhitsClu_hdbscan", "hNhitsClu", 20, -.5, 19.5);
	hNClu_hdbscan = new TH1D("hNClu_hdbscan", "hNClu", 10, -.5, 9.5);
	//t+e corr + hdbscan
	hNhitsClu_tecorr_hdbscan = new TH1D("hNhitsClu_tecorr_hdbscan", "hNhitsClu", 20, -.5, 19.5);
	hNClu_tecorr_hdbscan = new TH1D("hNClu_tecorr_hdbscan", "hNClu", 10, -.5, 9.5);
	//no corr + kmeans
	hNhitsClu_km = new TH1D("hNhitsClu_km", "hNhitsClu", 20, -.5, 19.5);
	hNClu_km = new TH1D("hNClu_km", "hNClu", 10, -.5, 9.5);

	hTest = new TH1D("hTest", "hTest", 25, -.5, 24.5);

	hDist2Clus = new TH1D("hDist2Clus", "hDist2Clus", 500, 0, 500);
	hDist2Clus_coinc = new TH1D("hDist2Clus_coinc", "hDist2Clus_coinc", 500, 0, 500);
	hDist2Clus_corr = new TH1D("hDist2Clus_corr", "hDist2Clus_corr", 500, 0, 500);

	hClusEneCorrVsClusEne = new TH2D("hClusEneCorrVsClusEne", "hClusEneCorrVsClusEne", 1500, 0, 15000, 1500, 0, 15000);
	hSeedEneCorrVsSeedEne = new TH2D("hSeedEneCorrVsClusEne", "hSeedEneCorrVsClusEne", 1500, 0, 15000, 1500, 0, 15000);

	hClus1EneVsClus2Ene = new TH2D("hClus1EneVsClus2Ene", "hClus1EneVsClus2Ene", 1500, 0, 15000, 1500, 0, 15000);
	hClus1EneVsClus2Ene_coinc = new TH2D("hClus1EneVsClus2Ene_coinc", "hClus1EneVsClus2Ene_coinc", 1500, 0, 15000, 1500, 0, 15000);
	hClus1EneVsClus2Ene_1bump = new TH2D("hClus1EneVsClus2Ene_1bump", "hClus1EneVsClus2Ene_1bump", 1500, 0, 15000, 1500, 0, 15000);
	hClus1EneVsClus2Ene_1bump_coinc = new TH2D("hClus1EneVsClus2Ene_1bump_coinc", "hClus1EneVsClus2Ene_1bump_coinc", 1500, 0, 15000, 1500, 0, 15000);
	hClus1EneVsClus2Ene_2bump = new TH2D("hClus1EneVsClus2Ene_2bump", "hClus1EneVsClus2Ene_2bump", 1500, 0, 15000, 1500, 0, 15000);
	hClus1EneVsClus2Ene_2bump_coinc = new TH2D("hClus1EneVsClus2Ene_2bump_coinc", "hClus1EneVsClus2Ene_2bump_coinc", 1500, 0, 15000, 1500, 0, 15000);

	h2ClusPosition = new TH2D("h2ClusPosition", "h2ClusPosition", 40, -200, 200, 40, -200, 200);
	h2ClusPosition_coinc = new TH2D("h2ClusPosition_coinc", "h2ClusPosition_coinc", 40, -200, 200, 40, -200, 200);
	h2ClusPosition_1bump = new TH2D("h2ClusPosition_1bump", "h2ClusPosition_1bump", 40, -200, 200, 40, -200, 200);
	h2ClusPosition_1bump_coinc = new TH2D("h2ClusPosition_1bump_coinc", "h2ClusPosition_1bump_coinc", 40, -200, 200, 40, -200, 200);
	h2ClusPosition_2bump = new TH2D("h2ClusPosition_2bump", "h2ClusPosition_2bump", 40, -200, 200, 40, -200, 200);
	h2ClusPosition_2bump_coinc = new TH2D("h2ClusPosition_2bump_coinc", "h2ClusPosition_2bump_coinc", 40, -200, 200, 40, -200, 200);

	//no corr
	hInvMass = new TH1D("hInvMass", "hInvMass", 500, 0, 500);
	hInvMass_1bump = new TH1D("hInvMass_1bump", "hInvMass_1bump", 500, 0, 500);
	hInvMass_2bump = new TH1D("hInvMass_2bump", "hInvMass_2bump", 500, 0, 500);
	hInvMass_off = new TH1D("hInvMass_off", "hInvMass_off", 500, 0, 500);
  //tcorr
	hInvMass_tcorr = new TH1D("hInvMass_tcorr", "hInvMass_tcorr", 500, 0, 500);
	hInvMass_1bump_tcorr = new TH1D("hInvMass_1bump_tcorr", "hInvMass_1bump_tcorr", 500, 0, 500);
	hInvMass_2bump_tcorr = new TH1D("hInvMass_2bump_tcorr", "hInvMass_2bump_tcorr", 500, 0, 500);
	hInvMass_off_tcorr = new TH1D("hInvMass_off_tcorr", "hInvMass_off_tcorr", 500, 0, 500);
	//t+e corr
	hInvMass_tecorr = new TH1D("hInvMass_tecorr", "hInvMass_tecorr", 500, 0, 500);
	hInvMass_1bump_tecorr = new TH1D("hInvMass_1bump_tecorr", "hInvMass_1bump_tecorr", 500, 0, 500);
	hInvMass_2bump_tecorr = new TH1D("hInvMass_2bump_tecorr", "hInvMass_2bump_tecorr", 500, 0, 500);
	hInvMass_off_tecorr = new TH1D("hInvMass_off_tecorr", "hInvMass_off_tecorr", 500, 0, 500);
  //no corr + hdbscan
	hInvMass_hdbscan = new TH1D("hInvMass_hdbscan", "hInvMass", 500, 0, 500);
	hInvMass_1bump_hdbscan = new TH1D("hInvMass_1bump_hdbscan", "hInvMass_1bump", 500, 0, 500);
	hInvMass_2bump_hdbscan = new TH1D("hInvMass_2bump_hdbscan", "hInvMass_2bump", 500, 0, 500);
	hInvMass_off_hdbscan = new TH1D("hInvMass_off_hdbscan", "hInvMass_off", 500, 0, 500);
	//no corr + kmeans
	hInvMass_km = new TH1D("hInvMass_km", "hInvMass", 500, 0, 500);
	hInvMass_1bump_km = new TH1D("hInvMass_1bump_km", "hInvMass_1bump", 500, 0, 500);
	hInvMass_2bump_km = new TH1D("hInvMass_2bump_km", "hInvMass_2bump", 500, 0, 500);
	hInvMass_off_km = new TH1D("hInvMass_off_km", "hInvMass_off", 500, 0, 500);
	//t+e corr + hdbscan
	hInvMass_tecorr_hdbscan = new TH1D("hInvMass_tecorr_hdbscan", "hInvMass_tecorr_hdbscan", 500, 0, 500);
	hInvMass_1bump_tecorr_hdbscan = new TH1D("hInvMass_1bump_tecorr_hdbscan", "hInvMass_1bump_tecorr_hdbscan", 500, 0, 500);
	hInvMass_2bump_tecorr_hdbscan = new TH1D("hInvMass_2bump_tecorr_hdbscan", "hInvMass_2bump_tecorr_hdbscan", 500, 0, 500);
	hInvMass_off_tecorr_hdbscan = new TH1D("hInvMass_off_tecorr_hdbscan", "hInvMass_off_tecorr_hdbscan", 500, 0, 500);

	hOpeningAngle = new TH1D("hOpeningAngle", "hOpeningAngle", 200, 0, 10);
	hOpeningAngle_1bump = new TH1D("hOpeningAngle_1bump", "hOpeningAngle_1bump", 200, 0, 10);
	hOpeningAngle_2bump = new TH1D("hOpeningAngle_2bump", "hOpeningAngle_2bump", 200, 0, 10);
	hOpeningAngle_off = new TH1D("hOpeningAngle_off", "hOpeningAngle_off", 200, 0, 10);

	hRelativeAngle = new TH2D("hRelativeAngle", "hRelativeAngle", 30, 2, 5, 30, 2, 5);
	hRelativeAngle_1bump = new TH2D("hRelativeAngle_1bump", "hRelativeAngle_1bump", 30, 2, 5, 30, 2, 5);
	hRelativeAngle_2bump = new TH2D("hRelativeAngle_2bump", "hRelativeAngle_2bump", 30, 2, 5, 30, 2, 5);
	hRelativeAngle_off = new TH2D("hRelativeAngle_off", "hRelativeAngle_off", 30, 2, 5, 30, 2, 5);

	hAnalogRadius = new TH1D("hAnalogRadius", "hAnalogRadius", 200, 0, 100);
	hAnalogRadius_corr = new TH1D("hAnalogRadius_corr", "hAnalogRadius_corr", 200, 0, 100);
	hAnalogRadiusVsClusEne = new TH2D("hAnalogRadiusVsClusEne", "hAnalogRadiusVsClusEne", 1500, 0, 15000, 200, 0, 100);
	hAnalogRadiusVsClusEne_corr = new TH2D("hAnalogRadiusVsClusEne_corr", "hAnalogRadiusVsClusEne_corr", 1500, 0, 15000, 200, 0, 100);


	h_minv_combo_tecorr = new TH1D("h_minv_combo_tecorr", "h_minv", 1000, 0, 1000);
	h_minv_nocuts_combo_tecorr = new TH1D("h_minv_nocuts_combo_tecorr", "h_minv_nocuts", 1000, 0, 1000);
	h_minv_Ecuts_combo_tecorr = new TH1D("h_minv_Ecuts_combo_tecorr", "h_minv_Ecuts", 1000, 0, 1000);
	h_minv_Etotcuts_combo_tecorr = new TH1D("h_minv_Etotcuts_combo_tecorr", "h_minv_Etotcuts", 1000, 0, 1000);
	h_minv_ele_combo_tecorr = new TH1D("h_minv_ele_combo_tecorr", "h_minv_ele", 1000, 0, 1000);
	h_tcoinc_combo_tecorr = new TH1D("h_tcoinc_combo_tecorr", "h_tcoinc_combo", 200, -100, 100);


	h_minv_combo_tecorr_hdbscan = new TH1D("h_minv_combo_tecorr_hdbscan", "h_minv", 1000, 0, 1000);
	h_minv_nocuts_combo_tecorr_hdbscan = new TH1D("h_minv_nocuts_combo_tecorr_hdbscan", "h_minv_nocuts", 1000, 0, 1000);
	h_minv_Ecuts_combo_tecorr_hdbscan = new TH1D("h_minv_Ecuts_combo_tecorr_hdbscan", "h_minv_Ecuts", 1000, 0, 1000);
	h_minv_Etotcuts_combo_tecorr_hdbscan = new TH1D("h_minv_Etotcuts_combo_tecorr_hdbscan", "h_minv_Etotcuts", 1000, 0, 1000);
	h_minv_ele_combo_tecorr_hdbscan = new TH1D("h_minv_ele_combo_tecorr_hdbscan", "h_minv_ele", 1000, 0, 1000);
	h_tcoinc_combo_tecorr_hdbscan = new TH1D("h_tcoinc_combo_tecorr_hdbscan", "h_tcoinc_combo", 200, -100, 100);


	h_tcoinc = new TH1D("h_tcoinc", "h_tcoinc", 200, -100, 100);



	gDirectory->cd();
	m_root_lock->release_lock();

}

//------------------
// Process
//------------------
void JEventProcessor_HallBFT_hdbscan::Process(const std::shared_ptr<const JEvent>& aEvent) {


	auto evnum = aEvent->GetEventNumber();

	if(evnum%10000==0){
		cout<<""<<endl;
		cout<<"EVENT #: "<< evnum <<endl;
	}

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
	auto hits = aEvent->Get<FTCalHit>(); //vector degli hits dell'evento
	auto hits_EneCorr = aEvent->Get<FTCalHitEneCorr>();
	auto hits_TimeCorr = aEvent->Get<FTCalHitTimeCorr>();

	/*
	for(int i=0; i < hits_EneCorr.size(); i++){

		cout<< hits_EneCorr[i]->getHitX() << ", "<< hits_EneCorr[i]->getHitY() <<  ", "\
		<< hits_EneCorr[i]->getHitTime() <<",  "<< hits_EneCorr[i]->getHitEnergy() << endl;

	}
	*/

	//cout<<"hits.size(): "<< hits.size() <<", hits_TimeCorr.size(): "<< hits_TimeCorr.size() <<\
	 ", hits_EneCorr.size(): "<< hits_EneCorr.size()<<endl;



  //cout<<"DEBUG1"<<endl;
 //Clusters dell'evento
	auto clusters = aEvent->Get<FTCalCluster>();
	//
	auto clusters_Hdbscan = aEvent->Get<FTCalCluster>("Hdbscan");
	//
	auto clusters_Kmeans = aEvent->Get<FTCalCluster>("Kmeans");
  //
	auto clusters_TimeCorr = aEvent->Get < FTCalCluster > ("TimeCorr");
	//
	auto clusters_EneCorr = aEvent->Get < FTCalCluster > ("EneCorr"); //vector dei clusters dell'evento con correzione sull'energia degli hit
	//
	auto clusters_EneCorrHdbscan = aEvent->Get < FTCalCluster > ("EneCorrHdbscan");


	//cout<<"clusters.size(): "<< clusters.size() <<", clusters_TimeCorr.size(): "<< clusters_TimeCorr.size() << ", clusters_EneCorr.size(): "<< clusters_EneCorr.size() <<endl;
	//cout<<""<<endl;

	//----------------------------------------------//
	//  sorting the clusters from hdbscan in energy //
	//----------------------------------------------//
	std::sort(clusters.begin(), clusters.end(), compareClusters);
	std::sort(clusters_Hdbscan.begin(), clusters_Hdbscan.end(), compareClusters);
	std::sort(clusters_Kmeans.begin(), clusters_Kmeans.end(), compareClusters);
	std::sort(clusters_TimeCorr.begin(), clusters_TimeCorr.end(), compareClusters);
	std::sort(clusters_EneCorr.begin(), clusters_EneCorr.end(), compareClusters);
	std::sort(clusters_EneCorrHdbscan.begin(), clusters_EneCorrHdbscan.end(), compareClusters);


	//-----------------------------------------------//

	double dist_min = 1000000; //mm
	double dist_fid = 2.*15.*sqrt(2.); //fiducial cut //mm
	double dist_thr = 100;
	double dTime_max = -1000;
	double twindow = 12;

	//-----------------------------------------------//

	//lock
	m_root_lock->acquire_write_lock();

	if (hits.size() != 0)
		hTest->Fill(1);

	//------------ hits/clusters survey -----------//
	hNhits->Fill(hits_EneCorr.size());

	//no corr
	hNClu->Fill(clusters.size());
	for (int ii = 0; ii < clusters.size(); ii++) {
		auto cluster1 = clusters[ii];
		hNhitsClu->Fill(cluster1->getClusterSize());
	}
	//t corr
	hNClu_tcorr->Fill(clusters_TimeCorr.size());
	for (int ii = 0; ii < clusters_TimeCorr.size(); ii++) {
		auto cluster1 = clusters_TimeCorr[ii];
		hNhitsClu_tcorr->Fill(cluster1->getClusterSize());
	}
	//t+e corr
	hNClu_tecorr->Fill(clusters_EneCorr.size());
	for (int ii = 0; ii < clusters_EneCorr.size(); ii++) {
		auto cluster1 = clusters_EneCorr[ii];
		hNhitsClu_tecorr->Fill(cluster1->getClusterSize());
	}
	//no corr + hdbscan
	hNClu_hdbscan->Fill(clusters_Hdbscan.size());
	for (int ii = 0; ii < clusters_Hdbscan.size(); ii++) {
		auto cluster1 = clusters_Hdbscan[ii];
		hNhitsClu_hdbscan->Fill(cluster1->getClusterSize());
	}
	//no corr + kmeans
	hNClu_km->Fill(clusters_Kmeans.size());
	for (int ii = 0; ii < clusters_Kmeans.size(); ii++) {
		auto cluster1 = clusters_Kmeans[ii];
		hNhitsClu_km->Fill(cluster1->getClusterSize());
	}
	//t+e corr + hdbscan
	hNClu_tecorr_hdbscan->Fill(clusters_EneCorrHdbscan.size());
	for (int ii = 0; ii < clusters_EneCorrHdbscan.size(); ii++) {
		auto cluster1 = clusters_EneCorrHdbscan[ii];
		hNhitsClu_tecorr_hdbscan->Fill(cluster1->getClusterSize());
	}

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//
	//-------------------------------------------------------------------------//
	//------------ Simone's Analysis (left for benchmark) ---------------------// //S.V.
  //-------------------------------------------------------------------------//
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

	if(evnum > 0){//1000000

		//cout<<"............event number: "<< evnum <<endl;


		if (clusters_TimeCorr.size() == 1) {
			hAnalogRadius->Fill(clusters_TimeCorr[0]->getRadius());
			hAnalogRadiusVsClusEne->Fill(clusters_TimeCorr[0]->getClusterEnergy(), clusters_TimeCorr[0]->getRadius());
		}


		if (clusters_EneCorrHdbscan.size() == 1) {
			hAnalogRadius_corr->Fill(clusters_EneCorrHdbscan[0]->getRadius());
			hAnalogRadiusVsClusEne_corr->Fill(clusters_EneCorrHdbscan[0]->getClusterEnergy(), clusters_EneCorrHdbscan[0]->getRadius());
		}



		//	Riempe distanza tra due cluster senza correzioni
		if (clusters.size() >= 2) { //N.b. changed to >=2, clusters are ordered in energy, they can be more than 2
			auto cluster1 = clusters[0];
			auto cluster2 = clusters[1];
			auto dist = (clusters[0]->getCentroid() - clusters[1]->getCentroid()).Mag();
			hDist2Clus->Fill(dist);
			if (fabs(cluster1->getClusterTime() - cluster2->getClusterTime()) < 3) {
				hDist2Clus_coinc->Fill(dist);
			}
		}


		//	Istogramma degli angoli relativi tra i due cluster e bidimensionae degli angoli polari.
		if (clusters_EneCorrHdbscan.size() >= 2) {
			auto cluster1 = clusters_EneCorrHdbscan[0];
			auto cluster2 = clusters_EneCorrHdbscan[1];
			auto dist = (clusters_EneCorrHdbscan[0]->getCentroid() - clusters_EneCorrHdbscan[1]->getCentroid()).Mag();
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
		}



		if (clusters_EneCorrHdbscan.size() >= 2) {
			auto cluster0 = clusters_EneCorrHdbscan[0];
			auto cluster1 = clusters_EneCorrHdbscan[1];
			auto dist = (cluster0->getCentroid() - cluster1->getCentroid()).Mag();
			if (abs(cluster0->getClusterTime() - cluster1->getClusterTime()) > 15) {
				hClus1EneVsClus2Ene->Fill(cluster0->getClusterEnergy(), cluster1->getClusterEnergy());
				h2ClusPosition->Fill(cluster0->getCentroid().X(), cluster0->getCentroid().Y());
				h2ClusPosition->Fill(cluster1->getCentroid().X(), cluster1->getCentroid().Y());
				if (dist > 30 && dist < 100) {
					hClus1EneVsClus2Ene_1bump->Fill(cluster0->getClusterEnergy(), cluster1->getClusterEnergy());
					h2ClusPosition_1bump->Fill(cluster0->getCentroid().X(), cluster0->getCentroid().Y());
					h2ClusPosition_1bump->Fill(cluster1->getCentroid().X(), cluster1->getCentroid().Y());
				} else if (dist > 170 && dist < 280) {
					hClus1EneVsClus2Ene_2bump->Fill(cluster0->getClusterEnergy(), cluster1->getClusterEnergy());
					h2ClusPosition_2bump->Fill(cluster0->getCentroid().X(), cluster0->getCentroid().Y());
					h2ClusPosition_2bump->Fill(cluster1->getCentroid().X(), cluster1->getCentroid().Y());
				}
			}
			if (abs(cluster0->getClusterTime() - cluster1->getClusterTime()) < 6) {
				hClus1EneVsClus2Ene_coinc->Fill(cluster0->getClusterEnergy(), cluster1->getClusterEnergy());
				h2ClusPosition_coinc->Fill(cluster0->getCentroid().X(), cluster0->getCentroid().Y());
				h2ClusPosition_coinc->Fill(cluster1->getCentroid().X(), cluster1->getCentroid().Y());
				if (dist > 30 && dist < 100) {
					hClus1EneVsClus2Ene_1bump_coinc->Fill(cluster0->getClusterEnergy(), cluster1->getClusterEnergy());
					h2ClusPosition_1bump_coinc->Fill(cluster0->getCentroid().X(), cluster0->getCentroid().Y());
					h2ClusPosition_1bump_coinc->Fill(cluster1->getCentroid().X(), cluster1->getCentroid().Y());
				} else if (dist > 170 && dist < 280) {
					hClus1EneVsClus2Ene_2bump_coinc->Fill(cluster0->getClusterEnergy(), cluster1->getClusterEnergy());
					h2ClusPosition_2bump_coinc->Fill(cluster0->getCentroid().X(), cluster0->getCentroid().Y());
					h2ClusPosition_2bump_coinc->Fill(cluster1->getCentroid().X(), cluster1->getCentroid().Y());
				}

			}

			h_tcoinc->Fill(cluster0->getClusterTime() - cluster1->getClusterTime());
		}


		//Valuto energia dei cluster corretta vs energia cluster non corretta.
		if (clusters_TimeCorr.size() == 1 && clusters_EneCorrHdbscan.size() == 1) {
			double cluE_tcorr = clusters_TimeCorr[0]->getClusterEnergy();
			double cluE_ecorr = clusters_EneCorrHdbscan[0]->getClusterEnergy();
			double seed_tcorr = clusters_TimeCorr[0]->getHit(0)->getHitEnergy();
			double seed_ecorr = clusters_EneCorrHdbscan[0]->getClusterSeedEnergy();

			//cout<<"cluE_tcorr, cluE_ecorr, seed_tcorr, seed_ecorr: "<< \
			//cluE_tcorr << ", " <<  cluE_ecorr << ", " <<  seed_tcorr << ", " <<  seed_ecorr << endl;

			hClusEneCorrVsClusEne->Fill(cluE_tcorr, cluE_ecorr);
			hSeedEneCorrVsSeedEne->Fill(seed_tcorr, seed_ecorr);
		}


		//	ASSUMO CHE LA CORREZIONE TEMPORALE SIA CORRETTA; COMPLETO LE ANALISI SULLA CORREZIONE ENERGETICA.
		//	Studio la distanza tra i due cluster, con o senza la correzione energetica (tempi sempre corretti)
		if (clusters_TimeCorr.size() >= 2) {
			if (fabs(clusters_TimeCorr[0]->getClusterTime() - clusters_TimeCorr[1]->getClusterTime()) > 6) {
				auto dist = (clusters_TimeCorr[0]->getCentroid() - clusters_TimeCorr[1]->getCentroid()).Mag();
				//			hDist2Clus->Fill(dist);
			}
		}
		if (clusters_EneCorrHdbscan.size() >= 2) {
			if (fabs(clusters_EneCorrHdbscan[0]->getClusterTime() - clusters_EneCorrHdbscan[1]->getClusterTime()) > 6) {
				auto dist = (clusters_EneCorrHdbscan[0]->getCentroid() - clusters_EneCorrHdbscan[1]->getCentroid()).Mag();
				hDist2Clus_corr->Fill(dist);

			}
		}


		//	Istogramma della molteplicità degli hit vs energia del cluster; versione senza correzione e con correzione.
		//	Pi0 mass find

		//C.F. adding comparison with all cases


		//No Corr
		if (clusters.size() >= 2) {
			auto cluster1 = clusters[0];
			auto cluster2 = clusters[1];
			auto z = cos(cluster1->getCentroid().Angle(cluster2->getCentroid()));
			auto M = sqrt(2 * cluster1->getClusterEnergy() * cluster2->getClusterEnergy() * (1 - z));
			if (abs(cluster1->getClusterTime() - cluster2->getClusterTime()) < 3) {
				hInvMass->Fill(M);
				auto dist = (clusters[0]->getCentroid() - clusters[1]->getCentroid()).Mag();
				if (dist > 30 && dist < 100) {
					hInvMass_1bump->Fill(M);
				} else if (dist > 170 && dist < 280) {
					hInvMass_2bump->Fill(M);
				} else {
					hInvMass_off->Fill(M);
				}
			}
		}


		//TimeCorr
		if (clusters_TimeCorr.size() >= 2) {
			auto cluster1 = clusters_TimeCorr[0];
			auto cluster2 = clusters_TimeCorr[1];
			auto z = cos(cluster1->getCentroid().Angle(cluster2->getCentroid()));
			auto M = sqrt(2 * cluster1->getClusterEnergy() * cluster2->getClusterEnergy() * (1 - z));
			if (abs(cluster1->getClusterTime() - cluster2->getClusterTime()) < 3) {
				hInvMass_tcorr->Fill(M);
				auto dist = (clusters_TimeCorr[0]->getCentroid() - clusters_TimeCorr[1]->getCentroid()).Mag();
				if (dist > 30 && dist < 100) {
					hInvMass_1bump_tcorr->Fill(M);
				} else if (dist > 170 && dist < 280) {
					hInvMass_2bump_tcorr->Fill(M);
				} else {
					hInvMass_off_tcorr->Fill(M);
				}
			}
		}

		//TimeEneCorr
		if (clusters_EneCorr.size() >= 2) {
			auto cluster1 = clusters_EneCorr[0];
			auto cluster2 = clusters_EneCorr[1];
			auto z = cos(cluster1->getCentroid().Angle(cluster2->getCentroid()));
			auto M = sqrt(2 * cluster1->getClusterEnergy() * cluster2->getClusterEnergy() * (1 - z));
			if (abs(cluster1->getClusterTime() - cluster2->getClusterTime()) < 3) {
				hInvMass_tecorr->Fill(M);
				auto dist = (clusters_EneCorr[0]->getCentroid() - clusters_EneCorr[1]->getCentroid()).Mag();
				if (dist > 30 && dist < 100) {
					hInvMass_1bump_tecorr->Fill(M);
				} else if (dist > 170 && dist < 280) {
					hInvMass_2bump_tecorr->Fill(M);
				} else {
					hInvMass_off_tecorr->Fill(M);
				}
			}
		}

		//Hdbscan
		if (clusters_Hdbscan.size() >= 2) {
			auto cluster1 = clusters_Hdbscan[0];
			auto cluster2 = clusters_Hdbscan[1];
			auto z = cos(cluster1->getCentroid().Angle(cluster2->getCentroid()));
			auto M = sqrt(2 * cluster1->getClusterEnergy() * cluster2->getClusterEnergy() * (1 - z));
			if (abs(cluster1->getClusterTime() - cluster2->getClusterTime()) < 3) {
				hInvMass_hdbscan->Fill(M);
				auto dist = (clusters_Hdbscan[0]->getCentroid() - clusters_Hdbscan[1]->getCentroid()).Mag();
				if (dist > 30 && dist < 100) {
					hInvMass_1bump_hdbscan->Fill(M);
				} else if (dist > 170 && dist < 280) {
					hInvMass_2bump_hdbscan->Fill(M);
				} else {
					hInvMass_off_hdbscan->Fill(M);
				}
			}
		}

		//Kmeans
		if (clusters_Kmeans.size() >= 2) {
			auto cluster1 = clusters_Kmeans[0];
			auto cluster2 = clusters_Kmeans[1];
			auto z = cos(cluster1->getCentroid().Angle(cluster2->getCentroid()));
			auto M = sqrt(2 * cluster1->getClusterEnergy() * cluster2->getClusterEnergy() * (1 - z));
			if (abs(cluster1->getClusterTime() - cluster2->getClusterTime()) < 3) {
				hInvMass_km->Fill(M);
				auto dist = (clusters_Kmeans[0]->getCentroid() - clusters_Kmeans[1]->getCentroid()).Mag();
				if (dist > 30 && dist < 100) {
					hInvMass_1bump_km->Fill(M);
				} else if (dist > 170 && dist < 280) {
					hInvMass_2bump_km->Fill(M);
				} else {
					hInvMass_off_km->Fill(M);
				}
			}
		}

		//EneCorrHdbscan
		if (clusters_EneCorrHdbscan.size() >= 2) {
			auto cluster1 = clusters_EneCorrHdbscan[0];
			auto cluster2 = clusters_EneCorrHdbscan[1];
			auto z = cos(cluster1->getCentroid().Angle(cluster2->getCentroid()));
			auto M = sqrt(2 * cluster1->getClusterEnergy() * cluster2->getClusterEnergy() * (1 - z));
			if (abs(cluster1->getClusterTime() - cluster2->getClusterTime()) < 3) {
				hInvMass_tecorr_hdbscan->Fill(M);
				auto dist = (clusters_EneCorrHdbscan[0]->getCentroid() - clusters_EneCorrHdbscan[1]->getCentroid()).Mag();
				if (dist > 30 && dist < 100) {
					hInvMass_1bump_tecorr_hdbscan->Fill(M);
				} else if (dist > 170 && dist < 280) {
					hInvMass_2bump_tecorr_hdbscan->Fill(M);
				} else {
					hInvMass_off_tecorr_hdbscan->Fill(M);
				}
			}
		}


	}// if num events

  //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//
	//-------------------------------------------------------------------------//
	//------------ analysis taking into account combos of clusters ------------// //C.F.
  //-------------------------------------------------------------------------//
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//

	TLorentzVector P4_gamma1, P4_gamma2, P4_ele, P4_cand, P4_pi0;
	TLorentzVector X4_gamma1, X4_gamma2, X4_ele, X4_cand;
	double t_ene, t_phi, t_theta, t_X, t_Y, t_Z, t_time, max_extra_ene(-9.);
	double deltat, tmp_dist, deltaphi;
	bool good_event = false;
	bool flag_ele = false; //true if an "electron candidate" is found
	int tmp_idx1, tmp_idx2;

	//Time+Ene Corr
	for (int i = 0; i < clusters_EneCorr.size(); i++) {
		auto cluster1 = clusters_EneCorr[i];

		t_ene = cluster1->getClusterEnergy();
		t_phi = cluster1->getPhi()*M_PI/180.;
		t_theta = cluster1->getTheta()*M_PI/180.;
		t_time = cluster1->getClusterTime();
		t_X = cluster1->getX();
		t_Y = cluster1->getY();
		t_Z = cluster1->getZ();
		P4_gamma1.SetPxPyPzE(t_ene*sin(t_theta)*cos(t_phi),t_ene*sin(t_theta)*sin(t_phi), t_ene*cos(t_theta), t_ene);
		X4_gamma1.SetXYZT(t_X,t_Y,t_Z,t_time);

		for (int j = i + 1; j < clusters_EneCorr.size(); j++) {
			auto cluster2 = clusters_EneCorr[j];

			t_ene = cluster2->getClusterEnergy();
			t_phi = cluster2->getPhi()*M_PI/180.;
			t_theta = cluster2->getTheta()*M_PI/180.;
			t_time = cluster2->getClusterTime();
			t_X = cluster2->getX();
			t_Y = cluster2->getY();
			t_Z = cluster2->getZ();
			P4_gamma2.SetPxPyPzE(t_ene*sin(t_theta)*cos(t_phi),t_ene*sin(t_theta)*sin(t_phi), t_ene*cos(t_theta), t_ene);
			X4_gamma2.SetXYZT(t_X,t_Y,t_Z,t_time);

			P4_pi0 = P4_gamma1 + P4_gamma2;

			deltat = abs(X4_gamma1.T() - X4_gamma2.T());
			tmp_dist = (cluster2->getCentroid() - cluster1->getCentroid()).Mag();//TVector3

			if(tmp_dist>dist_fid && deltat < twindow) good_event = true;


			h_minv_nocuts_combo_tecorr->Fill(P4_pi0.M());
			if(good_event) h_minv_combo_tecorr->Fill(P4_pi0.M());
			if(good_event && P4_gamma1.E()>3. && P4_gamma2.E()>3.) h_minv_Ecuts_combo_tecorr->Fill(P4_pi0.M());
			if(good_event && (P4_gamma1.E()+P4_gamma2.E())>7.) h_minv_Etotcuts_combo_tecorr->Fill(P4_pi0.M());


			tmp_idx1 = i;
			tmp_idx2 = j;

			for (int k = 0; k < clusters_EneCorr.size(); k++) {
				auto clustere = clusters_EneCorr[k];
				if(k!=tmp_idx1 && k!=tmp_idx2){

					t_ene = clustere->getClusterEnergy();
					t_phi = clustere->getPhi()*M_PI/180.;
					t_theta = clustere->getTheta()*M_PI/180.;
					t_time = clustere->getClusterTime();
					t_X = clustere->getX();
					t_Y = clustere->getY();
					t_Z = clustere->getZ();
					P4_cand.SetPxPyPzE(t_ene*sin(t_theta)*cos(t_phi),t_ene*sin(t_theta)*sin(t_phi), t_ene*cos(t_theta), t_ene);
					X4_cand.SetXYZT(t_X,t_Y,t_Z,t_time);

					deltaphi = abs(P4_cand.DeltaPhi(P4_pi0)); //returns phi angle in the interval [-Pi,Pi)
					//Error in <TROOT::TVector2::Phi_mpi_pi>: function called with NaN ???

					//take the most energetic electron
					if(t_ene>max_extra_ene && deltaphi>120.*M_PI/180.){
						max_extra_ene = t_ene;
						P4_ele = P4_cand;
						X4_ele = X4_cand;
						flag_ele = true; // have an electron candidate
					}

				}

			}//--------electron

			if(flag_ele && good_event && P4_gamma1.E()>2. && P4_gamma2.E()>2.) h_minv_ele_combo_tecorr->Fill(P4_pi0.M());

			h_tcoinc_combo_tecorr->Fill(X4_gamma1.T() - X4_gamma2.T());

		}//-------photon2

	}//------photon1

	//Time+Ene Corr+hdbscan

	for (int i = 0; i < clusters_EneCorrHdbscan.size(); i++) {
		auto cluster1 = clusters_EneCorrHdbscan[i];

		t_ene = cluster1->getClusterEnergy();
		t_phi = cluster1->getPhi()*M_PI/180.;
		t_theta = cluster1->getTheta()*M_PI/180.;
		t_time = cluster1->getClusterTime();
		t_X = cluster1->getX();
		t_Y = cluster1->getY();
		t_Z = cluster1->getZ();
		P4_gamma1.SetPxPyPzE(t_ene*sin(t_theta)*cos(t_phi),t_ene*sin(t_theta)*sin(t_phi), t_ene*cos(t_theta), t_ene);
		X4_gamma1.SetXYZT(t_X,t_Y,t_Z,t_time);

		for (int j = i + 1; j < clusters_EneCorrHdbscan.size(); j++) {
			auto cluster2 = clusters_EneCorrHdbscan[j];

			t_ene = cluster2->getClusterEnergy();
			t_phi = cluster2->getPhi()*M_PI/180.;
			t_theta = cluster2->getTheta()*M_PI/180.;
			t_time = cluster2->getClusterTime();
			t_X = cluster2->getX();
			t_Y = cluster2->getY();
			t_Z = cluster2->getZ();
			P4_gamma2.SetPxPyPzE(t_ene*sin(t_theta)*cos(t_phi),t_ene*sin(t_theta)*sin(t_phi), t_ene*cos(t_theta), t_ene);
			X4_gamma2.SetXYZT(t_X,t_Y,t_Z,t_time);

			P4_pi0 = P4_gamma1 + P4_gamma2;

			deltat = abs(X4_gamma1.T() - X4_gamma2.T());
			tmp_dist = (cluster2->getCentroid() - cluster1->getCentroid()).Mag();//TVector3

			if(tmp_dist>dist_fid && deltat < twindow) good_event = true;


			h_minv_nocuts_combo_tecorr_hdbscan->Fill(P4_pi0.M());
			if(good_event) h_minv_combo_tecorr_hdbscan->Fill(P4_pi0.M());
			if(good_event && P4_gamma1.E()>3. && P4_gamma2.E()>3.) h_minv_Ecuts_combo_tecorr_hdbscan->Fill(P4_pi0.M());
			if(good_event && (P4_gamma1.E()+P4_gamma2.E())>7.) h_minv_Etotcuts_combo_tecorr_hdbscan->Fill(P4_pi0.M());


			tmp_idx1 = i;
			tmp_idx2 = j;

			for (int k = 0; k < clusters_EneCorrHdbscan.size(); k++) {
				auto clustere = clusters_EneCorrHdbscan[k];
				if(k!=tmp_idx1 && k!=tmp_idx2){

					t_ene = clustere->getClusterEnergy();
					t_phi = clustere->getPhi()*M_PI/180.;
					t_theta = clustere->getTheta()*M_PI/180.;
					t_time = clustere->getClusterTime();
					t_X = clustere->getX();
					t_Y = clustere->getY();
					t_Z = clustere->getZ();
					P4_cand.SetPxPyPzE(t_ene*sin(t_theta)*cos(t_phi),t_ene*sin(t_theta)*sin(t_phi), t_ene*cos(t_theta), t_ene);
					X4_cand.SetXYZT(t_X,t_Y,t_Z,t_time);

					deltaphi = abs(P4_cand.DeltaPhi(P4_pi0)); //returns phi angle in the interval [-Pi,Pi)
					//Error in <TROOT::TVector2::Phi_mpi_pi>: function called with NaN ???

					//take the most energetic electron
					if(t_ene>max_extra_ene && deltaphi>120.*M_PI/180.){
						max_extra_ene = t_ene;
						P4_ele = P4_cand;
						X4_ele = X4_cand;
						flag_ele = true; // have an electron candidate
					}

				}

			}//--------electron

			if(flag_ele && good_event && P4_gamma1.E()>2. && P4_gamma2.E()>2.) h_minv_ele_combo_tecorr_hdbscan->Fill(P4_pi0.M());

			h_tcoinc_combo_tecorr_hdbscan->Fill(X4_gamma1.T() - X4_gamma2.T());

		}//-------photon2

	}//------photon1



	m_root_lock->release_lock();
//unlock

}

//------------------
// Finish
//------------------
void JEventProcessor_HallBFT_hdbscan::Finish(void) {
// This is called when at the end of event processing

//	hEnergyPosition->Divide(hClusterPosition);
//	hEnergyPosition_corr->Divide(hClusterPosition_corr);

	auto app = japp;
	std::string outFileName;
	TFile *fout;
	if (app->GetJParameterManager()->Exists("hallBFT_hdbscan:output_file") == true) {
		gROOT->cd();
		TDirectory *main = gDirectory;

		app->GetJParameterManager()->GetParameter("hallBFT_hdbscan:output_file", outFileName);
		std::cout << "JEventProcessor_HallBFT_hdbscan::Finish " << this << " " << outFileName << std::endl;
		fout = new TFile(outFileName.c_str(), "recreate");

		main->cd("HallBFT_hdbscan");
		TIter next(gDirectory->GetList());
		TObject* object = 0;
		fout->cd();

		while (object = next()) {
			if (object->InheritsFrom(TH1::Class())) {
				fout->cd();
				object->Write();
				std::cout << "JEventProcessor_HallBFT_hdbscan::wrote " << object->GetName() << std::endl;
			}
		}

		fout->Write();
		fout->Close();
	}
}
