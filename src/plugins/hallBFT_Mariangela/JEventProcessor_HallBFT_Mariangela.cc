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
#include "FT/FTHodoCluster.h"
#include "FT/FTParticle.h"

#include "JANA/Services/JGlobalRootLock.h"
#include "JANA/JApplication.h"

#include "DAQ/TridasEvent.h"

#include <TDirectory.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TTree.h>
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

bool compareHits(const FTHodoHit* a, const FTHodoHit* b) {
	return (a->getHitEnergy() > b->getHitEnergy());
}

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
static TH2D *hClustersMolt_Corr_noCorr = 0;
static TH1D *hClustersMolt_TrigCLus = 0;
static TH1D *hClustersMolt_noCorr =0;

static vector<TH1D *> EneCrystal;

//Analisi eventi a singolo cluster
static TH1D *hSCDelayFromSeed = 0;
static TH1D *hSCHitsMolt = 0;
static TH1D *hSCHitsEnergy = 0;
static TH1D *hSCClusterEnergy = 0;
static TH2D *hSCSeedPosition = 0;
static TH2D *hSCClusterPosition = 0;
static TH2D *hSCEnergyPosition = 0;
static TH2D *hSCClusterEnergyVsSeedEnergy = 0;
static TH1D *hSCtheta =0;

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
static TH1D *hDCdistance_seed = 0;
static TH2D *hDCSeedEnergy1VsSeedEnergy2 = 0;

static TH2D *hDCSeedEnergy1VsSeedEnergy2_0_40 = 0;
static TH2D *hDCSeedEnergy1VsSeedEnergy2_40 = 0;
static TH1D *hDCtheta =0;


static TH1D *hDCInvariantMass_angle = 0;
static TH1D *hDCInvariantMass_Raffa = 0;
static TH1D *hDCInvariantMass_Raffa_triggerClus = 0;

//Analisi eventi a tre cluster
static TH2D *hTCClustersDeltaTime = 0;
static TH1D *hTCInvariantMass = 0;
static TH1D *hTCSelectedInvariantMass = 0;

//AnalisiCristiano
static TH1D *h_tcoinc_combo = 0;
static TH1D *h_minv = 0;
static TH1D *h_minv_nocuts = 0;


// Check DC events with time cluster difference < -5 ns and >-15 ns

static TH2D *hDCEneClus0vsEneClus1_DT=0;
static TH2D *hDCEneClus0vsEneClus1=0;

static TH2D *hDCEClus1vsEseedClus1_DT=0;
static TH2D *hDCEClus1vsEseedClus1=0;

static TH1D *hDT_Hit_seed_fake2Cluster=0;
static TH2D *hDT_Hit_seed_Vs_component_fake2Cluster=0;

static TH2D *hInVMass_angle=0;
static TH2D *hInVMass_distance=0;
static TH2D *hangle_distance=0;
//static vector<TH2D*> XYDCPosClus1_DT;
//static vector<TH2D*> XYDCPosClus0_DT;
int j=0;
//TimeWalk correction
//static vector<TH2D *> CorrectionCurve;
//static vector<TH1D *> DT_Hit_seed;
//static vector<TH2D *> DT_Hit_seed_ene;


// HODO HIT histo
static TH2D *hHitsHODOPosition = 0;
static vector<TH1D *> EneHitHODO_layer1_sector1;
static vector<TH1D *> EneHitHODO_layer1_sector2;
static vector<TH1D *> EneHitHODO_layer1_sector3;
static vector<TH1D *> EneHitHODO_layer1_sector4;
static vector<TH1D *> EneHitHODO_layer1_sector5;
static vector<TH1D *> EneHitHODO_layer1_sector6;
static vector<TH1D *> EneHitHODO_layer1_sector7;
static vector<TH1D *> EneHitHODO_layer1_sector8;

static vector<TH1D *> EneHitHODO_layer2_sector1;
static vector<TH1D *> EneHitHODO_layer2_sector2;
static vector<TH1D *> EneHitHODO_layer2_sector3;
static vector<TH1D *> EneHitHODO_layer2_sector4;
static vector<TH1D *> EneHitHODO_layer2_sector5;
static vector<TH1D *> EneHitHODO_layer2_sector6;
static vector<TH1D *> EneHitHODO_layer2_sector7;
static vector<TH1D *> EneHitHODO_layer2_sector8;

static TH1D *hHitsHODOTime = 0;

static TH1D *hClustHODOmult =0;
static TH1D *hClustHODOTimeSeed_hit=0;
static TH2D *hClustHODOTimeSeedEne_hit =0;
static TH1D *hClustHODOHitmult =0;
static TH1D *hClustHODOEne =0;
static TH1D *hClustHODOEneHit_layer1 =0;
static TH1D *hClustHODOEneHit_layer2 =0;
static TH1D *hClustHODOEne_layer1 =0;
static TH1D *hClustHODOEne_layer2 =0;
static TH2D *hClustHODOPosition =0;
static TH2D *hClustHODOSeed1vsSeed2=0;
static TH2D *hClustHODO_DTSeedvsSeed2=0;
static TH2D *hClustHODO_DTSeedvsSeed2_seed1th=0;

// study matching HODO CAL

static TH1D *hmatch_diffX=0;
static TH1D *hmatch_diffY=0;
static TH1D *hmatch_diffT=0;
static TH2D *hmatch_diffX_diffY=0;
static TH1D *hmatch_diffT_cut=0;
static TH1D *hTimeSeedcal_hodohit=0;
static TH2D *hNclustervsNgamma=0;
static TH1D *hpi0=0;
static TH1D *hpi0_raffa=0;
static TH1D *hpi0_angle=0;
int pp=0;
int qq=0;

static TH1D *htrigger=0;
static TH1D *htrigger_2clusterJANA_ene =0;
static TH1D *htrigger_2cluster_ene =0;


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
	hClustersMolt_TrigCLus = new TH1D("hClustersMolt_TrigCLus", "hClustersMolt_TrigCLus", 11, -.5, 10.5);
	hClustersMolt_noCorr = new TH1D("hClustersMolt_noCorr", "hClustersMolt_noCorr", 11, -.5, 10.5);
	hClustersMolt_Corr_noCorr = new TH2D("hClustersMolt_Corr_noCorr", "hClustersMolt_Corr_noCorr", 11, -.5, 10.5, 11, -.5, 10.5);
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
    hSCtheta = new TH1D("hSCtheta", "hSCtheta", 20, 0, 10.);


	//Double clusters events
	hDCtheta = new TH1D("hDCtheta", "hDCtheta", 20, 0, 10.);
	hDCInvariantMass_angle = new TH1D("hDCInvariantMass_angle", "hDCInvariantMass_angle", 500, 0, 500);
	hDCInvariantMass_Raffa = new TH1D("hDCInvariantMass_Raffa", "hDCInvariantMass_Raffa", 500, 0, 500);
	hDCInvariantMass_Raffa_triggerClus = new TH1D("hDCInvariantMass_Raffa_triggerClus", "hDCInvariantMass_Raffa_triggerClus", 500, 0, 500);
	hDCSeedEnergy1VsSeedEnergy2 =  new TH2D("hDCSeedEnergy1VsSeedEnergy2", "hDCSeedEnergy1VsSeedEnergy2", 1500, 0, 15000, 1500, 0, 15000);


    hDCSeedEnergy1VsSeedEnergy2_0_40 = new TH2D("hDCSeedEnergy1VsSeedEnergy2_0_40", "hDCSeedEnergy1VsSeedEnergy2_0_40", 1500, 0, 15000, 1500, 0, 15000);
	hDCSeedEnergy1VsSeedEnergy2_40 = new TH2D("hDCSeedEnergy1VsSeedEnergy2_40", "hDCSeedEnergy1VsSeedEnergy2_40", 1500, 0, 15000, 1500, 0, 15000);

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
	hInVMass_angle = new TH2D("hInVMass_angle", "hInVMass_angle", 500, 0, 500, 200, 0., 20.);
	hInVMass_distance = new TH2D("hInVMass_distance", "hInVMass_distance", 500, 0, 500, 400, 0., 400.);
	hangle_distance = new TH2D("hangle_distance", "hangle_distance", 150, 0, 15., 400, 0., 400.);

	hDCdistance_seed = new TH1D("hDCdistance_seed", "hDCdistance_seed", 500, 0, 500);
	//	hDCSelectedInvariantMass = new TH1D("hDCSelectedInvariantMass", "hDCSelectedInvariantMass", 500, 0, 500);




	//Triple clusters events
	hTCClustersDeltaTime = new TH2D("hTCClustersDeltaTime", "hTCClustersDeltaTime", 201, -0.5, 200.5, 201, -0.5, 200.5);
	hTCInvariantMass = new TH1D("hTCInvariantMass", "hTCInvariantMass", 500, 0, 500);
	hTCSelectedInvariantMass = new TH1D("hTCSelectedInvariantMass", "hTCSelectedInvariantMass", 500, 0, 500);

	for (int j = 0; j < 500; j++) {
		TH1D *hCrystalEnergy = new TH1D(Form("hCrystalEnergy%d", j), Form("hCrystalEnergy%d", j), 100, 0., 200.);
		EneCrystal.push_back(hCrystalEnergy);
	}
	/*
	for (int j = 0; j < 500; j++) {
	 TH2D *hCorrectionCurve = new TH2D(Form("hCorrectionCurve%d", j), Form("hCorrectionCurve%d", j), 1000, 0, 10000, 60, -5.5, 54.5);
		CorrectionCurve.push_back(hCorrectionCurve);

		TH1D *hDT_Hit_seed = new TH1D(Form("hDT_Hit_seed%d", j), Form("hDT_Hit_seed%d", j), 200, -30, 30);
		DT_Hit_seed.push_back(hDT_Hit_seed);

		TH2D *hDT_Hit_seed_ene = new TH2D(Form("hDT_Hit_seed_ene%d", j), Form("hDT_Hit_seed_ene%d", j), 1000, 0, 10000, 200, -30, 30);
		DT_Hit_seed_ene.push_back(hDT_Hit_seed_ene);
                 }

*/
	hDT_Hit_seed_fake2Cluster = new TH1D("hDT_Hit_seed_fake2Cluster", "hDT_Hit_seed_fake2Cluster", 200, -30, 30);
	hDT_Hit_seed_Vs_component_fake2Cluster = new TH2D("hDT_Hit_seed_Vs_component_fake2Cluster", "hDT_Hit_seed_Vs_component_fake2Cluster", 200, -50., 50., 500, 0., 500);

	hDCEneClus0vsEneClus1_DT = new TH2D("hDCEneClus0vsEneClus1_DT", "hDCEneClus0vsEneClus1_DT", 1500, 0, 15000, 1500, 0, 15000);
	hDCEneClus0vsEneClus1 = new TH2D("hDCEneClus0vsEneClus1", "hDCEneClus0vsEneClus1", 1500, 0, 15000, 1500, 0, 15000);

	hDCEClus1vsEseedClus1_DT = new TH2D("hDCEClus1vsEseedClus1_DT", "hDCEClus1vsEseedClus1_DT", 3000, 0, 15000, 3000, 0, 15000);
	hDCEClus1vsEseedClus1 = new TH2D("hDCEClus1vsEseedClus1", "hDCEClus1vsEseedClus1", 3000, 0, 15000, 3000, 0, 15000);
	for (int j = 0; j < 100; j++) {

	//	TH2D *hXYDCClus1 = new TH2D(Form("hXYDCClus1%d", j), Form("hXYDCClus1%d", j), 25, -.5, 24.5, 25, -0.5, 24.5);
	//	XYDCPosClus1_DT.push_back(hXYDCClus1);

	//	TH2D *hXYDCClus0 = new TH2D(Form("hXYDCClus0%d", j), Form("hXYDCClus0%d", j), 25, -.5, 24.5, 25, -0.5, 24.5);
	//	XYDCPosClus0_DT.push_back(hXYDCClus0);


	}

	hHitsHODOPosition = new TH2D("hHitsHODOPosition", "hHitsHODOPosition", 200, -200, 200, 200, -200, 200);

         for(int w=0; w<20; w++){
           TH1D *hEneHitHODO_layer1_sector1 = new TH1D(Form("hEneHitHODO_layer1_sector1_%d",w), Form("hEneHitHODO_layer1_sector1_%d",w), 200, 0, 10);
           EneHitHODO_layer1_sector1.push_back(hEneHitHODO_layer1_sector1);

           TH1D *hEneHitHODO_layer1_sector2 = new TH1D(Form("hEneHitHODO_layer1_sector2_%d",w), Form("hEneHitHODO_layer1_sector2_%d",w), 200, 0, 10);
           EneHitHODO_layer1_sector2.push_back(hEneHitHODO_layer1_sector2);

           TH1D *hEneHitHODO_layer1_sector3 = new TH1D(Form("hEneHitHODO_layer1_sector3_%d",w), Form("hEneHitHODO_layer1_sector3_%d",w), 200, 0, 10);
           EneHitHODO_layer1_sector3.push_back(hEneHitHODO_layer1_sector3);

           TH1D *hEneHitHODO_layer1_sector4 = new TH1D(Form("hEneHitHODO_layer1_sector4_%d",w), Form("hEneHitHODO_layer1_sector4_%d",w), 200, 0, 10);
           EneHitHODO_layer1_sector4.push_back(hEneHitHODO_layer1_sector4);

           TH1D *hEneHitHODO_layer1_sector5 = new TH1D(Form("hEneHitHODO_layer1_sector5_%d",w), Form("hEneHitHODO_layer1_sector5_%d",w),  200, 0, 10);
           EneHitHODO_layer1_sector5.push_back(hEneHitHODO_layer1_sector5);

           TH1D *hEneHitHODO_layer1_sector6 = new TH1D(Form("hEneHitHODO_layer1_sector6_%d",w), Form("hEneHitHODO_layer1_sector6_%d",w), 200, 0, 10);
           EneHitHODO_layer1_sector6.push_back(hEneHitHODO_layer1_sector6);

           TH1D *hEneHitHODO_layer1_sector7 = new TH1D(Form("hEneHitHODO_layer1_sector7_%d",w), Form("hEneHitHODO_layer1_sector7_%d",w), 200, 0, 10);
           EneHitHODO_layer1_sector7.push_back(hEneHitHODO_layer1_sector7);

           TH1D *hEneHitHODO_layer1_sector8 = new TH1D(Form("hEneHitHODO_layer1_sector8_%d",w), Form("hEneHitHODO_layer1_sector8_%d",w), 200, 0, 10);
           EneHitHODO_layer1_sector8.push_back(hEneHitHODO_layer1_sector8);



           TH1D *hEneHitHODO_layer2_sector1 = new TH1D(Form("hEneHitHODO_layer2_sector1_%d",w), Form("hEneHitHODO_layer2_sector1_%d",w), 200, 0, 10);
           EneHitHODO_layer2_sector1.push_back(hEneHitHODO_layer2_sector1);

           TH1D *hEneHitHODO_layer2_sector2 = new TH1D(Form("hEneHitHODO_layer2_sector2_%d",w), Form("hEneHitHODO_layer2_sector2_%d",w), 200, 0, 10);
           EneHitHODO_layer2_sector2.push_back(hEneHitHODO_layer2_sector2);

           TH1D *hEneHitHODO_layer2_sector3 = new TH1D(Form("hEneHitHODO_layer2_sector3_%d",w), Form("hEneHitHODO_layer2_sector3_%d",w), 200, 0, 10);
           EneHitHODO_layer2_sector3.push_back(hEneHitHODO_layer2_sector3);

           TH1D *hEneHitHODO_layer2_sector4 = new TH1D(Form("hEneHitHODO_layer2_sector4_%d",w), Form("hEneHitHODO_layer2_sector4_%d",w), 200, 0, 10);
           EneHitHODO_layer2_sector4.push_back(hEneHitHODO_layer2_sector4);

           TH1D *hEneHitHODO_layer2_sector5 = new TH1D(Form("hEneHitHODO_layer2_sector5_%d",w), Form("hEneHitHODO_layer2_sector5_%d",w), 200, 0, 10);
           EneHitHODO_layer2_sector5.push_back(hEneHitHODO_layer2_sector5);

           TH1D *hEneHitHODO_layer2_sector6 = new TH1D(Form("hEneHitHODO_layer2_sector6_%d",w), Form("hEneHitHODO_layer2_sector6_%d",w), 200, 0, 10);
           EneHitHODO_layer2_sector6.push_back(hEneHitHODO_layer2_sector6);

           TH1D *hEneHitHODO_layer2_sector7 = new TH1D(Form("hEneHitHODO_layer2_sector7_%d",w), Form("hEneHitHODO_layer2_sector7_%d",w), 200, 0, 10);
           EneHitHODO_layer2_sector7.push_back(hEneHitHODO_layer2_sector7);

           TH1D *hEneHitHODO_layer2_sector8 = new TH1D(Form("hEneHitHODO_layer2_sector8_%d",w), Form("hEneHitHODO_layer2_sector8_%d",w), 200, 0, 10);
           EneHitHODO_layer2_sector8.push_back(hEneHitHODO_layer2_sector8);

			}
         hHitsHODOTime = new TH1D("hHitsHODOTime", "hHitsHODOTime", 300, -50, 50);

         hClustHODOmult =new TH1D("hClustHODOmult", "hClustHODOmult", 20, -0.5, 19.5);
         hClustHODOTimeSeed_hit=new TH1D("hHitsHODOTime", "hHitsHODOTime", 300, -50, 50);
         hClustHODOTimeSeedEne_hit = new TH2D("hClustHODOTimeSeedEne_hit", "hClustHODOTimeSeedEne_hit",400, 0, 10., 300, -50, 50);
         hClustHODOHitmult = new TH1D("hClustHODOHitmult", "hClustHODOHitmult", 20, -0.5, 19.5);
         hClustHODOEne =new TH1D("hClustHODOEne", "hClustHODOEne", 400, -0.5, 20.5);
         hClustHODOPosition = new TH2D("hClustHODOPosition", "hClustHODOPosition", 200, -200, 200, 200, -200, 200);
         hClustHODOEneHit_layer1 = new TH1D("hClustHODOEneHit_layer1", "hClustHODOEneHit_layer1", 300, 0., 10);
         hClustHODOEneHit_layer2 = new TH1D("hClustHODOEneHit_layer2", "hClustHODOEneHit_layer2", 300, 0., 10);
         hClustHODOSeed1vsSeed2 = new TH2D("hClustHODOSeed1vsSeed2", "hClustHODOSeed1vsSeed2", 300, 0., 10, 300, 0., 10);
         hClustHODO_DTSeedvsSeed2= new TH2D("hClustHODO_DTSeedvsSeed2", "hClustHODO_DTSeedvsSeed2", 300, -30., 30, 300, 0., 10);
         hClustHODO_DTSeedvsSeed2_seed1th=new TH2D("hClustHODO_DTSeedvsSeed2_seed1th", "hClustHODO_DTSeedvsSeed2_seed1th", 300, -30., 30, 300, 0., 10);


         hmatch_diffX= new TH1D("hmatch_diffX", "hmatch_diffX", 200, -100, 100);
         hmatch_diffY= new TH1D("hmatch_diffY", "hmatch_diffY", 200, -100, 100);
         hmatch_diffT= new TH1D("hmatch_diffT", "hmatch_diffT", 200, -100, 100);
         hmatch_diffX_diffY=new TH2D("hmatch_diffX_diffY", "hmatch_diffX_diffY", 200, -100, 100, 200, -100, 100);
         hmatch_diffT_cut= new TH1D("hmatch_diffT_cut", "hmatch_diffT_cut", 200, -100, 100);


         hTimeSeedcal_hodohit = new TH1D("hTimeSeedcal_hodohit", "hTimeSeedcal_hodohit", 600, -300, 300);
         hNclustervsNgamma = new TH2D("hNclustervsNgamma","hNclustervsNgamma", 10, 0, 10, 10, 0, 10);
         hpi0 = new TH1D("hpi0", "hpi0", 500, 0, 500);
         hpi0_raffa = new TH1D("hpi0_raffa", "hpi0_raffa", 500, 0, 500);
         hpi0_angle = new TH1D("hpi0_angle", "hpi0_angle", 500, 0, 500);



         htrigger = new TH1D("htrigger", "htrigger", 20, -0.5, 19.5);
         htrigger_2clusterJANA_ene = new TH1D("htrigger_2clusterJANA_ene", "htrigger_2clusterJANA_ene",  1500, 0, 15000);
         htrigger_2cluster_ene = new TH1D("htrigger_2cluster_ene", "htrigger_2cluster_ene",  1500, 0, 15000);
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
	auto hits_noCorr = aEvent->Get<FTCalHit>(); //vector degli hits dell'evento
//	auto hits_EneCorr = aEvent->Get<FTCalHitEneCorr>();
	auto hits = aEvent->Get<FTCalHitEneCorr>();
//	auto hits_TimeCorr = aEvent->Get<FTCalHitTimeCorr>();

//Clusters dell'evento
	auto clusters_noCorr = aEvent->Get<FTCalCluster>();
	auto clusters = aEvent->Get < FTCalCluster > ("EneCorr");
//	auto clusters_TimeCorr = aEvent->Get < FTCalCluster > ("TimeCorr");
//	auto clusters_EneCorr = aEvent->Get < FTCalCluster > ("EneCorr"); //vector dei clusters dell'evento con correzione sull'energia degli hit
//	auto clusters_TimeCorr = aEvent->Get<FTCalCluster>();
//	auto clusters_EneCorr = aEvent->Get<FTCalCluster>(); //vector dei clusters dell'evento con correzione sull'energia degli hit


// Hits Hodo
	auto hits_hodo = aEvent->Get<FTHodoHit>();
	auto clusters_hodo = aEvent->Get<FTHodoCluster>();

	// Hits Particle
	auto particles = aEvent->Get<FTParticle>();


//Numero dell'evento
	auto eventNumber = aEvent->GetEventNumber();

//lock
	m_root_lock->acquire_write_lock();

	//cout << "New event"<<endl;
	auto jana_cluster =0;
	auto jana_scaler=0;
	auto tridas_scaler=0;
	int i=0;
	for(auto trig_word:tridas_event->triggerWords){
        auto jana_id = trig_word >>16;
		auto trig_decision = (trig_word & 0xFFFF);
		//cout << i<< " "<< trig_decision<<endl;
	    if(i==7)  jana_cluster = trig_decision;
	    if(i==8)  jana_scaler = trig_decision;
	    if(i==11)  tridas_scaler = trig_decision;
		i = i+1;


	}
    if(jana_cluster==1 && jana_scaler==0 && tridas_scaler==0) htrigger->Fill(1);
    if(jana_cluster==0 && jana_scaler==1 && tridas_scaler==0) htrigger->Fill(2);
    if(jana_cluster==0 && jana_scaler==0 && tridas_scaler==1) htrigger->Fill(3);
    if(jana_cluster==1 && jana_scaler==1 && tridas_scaler==0) htrigger->Fill(4);
    if(jana_cluster==1 && jana_scaler==0 && tridas_scaler==1) htrigger->Fill(5);
    if(jana_cluster==0 && jana_scaler==1 && tridas_scaler==1) htrigger->Fill(6);
    if(jana_cluster==1 && jana_scaler==1 && tridas_scaler==1) htrigger->Fill(7);
    if(tridas_scaler==1 ) htrigger->Fill(9);
    if(jana_scaler==1 ) htrigger->Fill(10);
    if(jana_cluster==1 ) htrigger->Fill(11);
    if(jana_cluster==1 && tridas_scaler==1) htrigger->Fill(12);

    if(jana_cluster==1){
    	hClustersMolt_TrigCLus->Fill(clusters_noCorr.size());

    if(clusters_noCorr.size()==1){

    	cout<<"clus size "<< clusters_noCorr[0]->getClusterSize()<<endl;
    	cout<<"clus ene "<< clusters_noCorr[0]->getClusterEnergy()<<endl;
    	cout<<"clus seed ene "<<clusters_noCorr[0]->getHit(0)->getHitEnergy()<<endl;

    	cout << "hits info"<<endl;
    	cout<<hits_noCorr.size()<<endl;
        int check =0;

    		for (auto hit_noCorr: hits_noCorr) {
    			for (int i=0; i<clusters_noCorr[0]->getClusterSize(); i++){
    				if(clusters_noCorr[0]->getHit(i) == hit_noCorr){
    			     check=1;
    			     break;
    				}
    			}
    		if (check==0)cout<< hit_noCorr->m_channel.component<<" "<<hit_noCorr->getHitEnergy()<<" "<<hit_noCorr->getHitTime()<<endl;
    		check=0;
    		}


    }
    }




       if(clusters_noCorr.size()>=2){
    	   auto cluster_noCorr = clusters_noCorr[0];
    	   for(int i=1; i<clusters_noCorr.size(); i++){
    		   if(clusters_noCorr[i]->getClusterEnergy() > cluster_noCorr->getClusterEnergy()){
    			   cluster_noCorr = clusters_noCorr[i];
    		   }
    	   }
    		   if (jana_cluster==1) htrigger_2clusterJANA_ene->Fill(cluster_noCorr->getClusterEnergy());
    		   htrigger_2cluster_ene->Fill(cluster_noCorr->getClusterEnergy());

           }
/*

	std::sort(hits_hodo.begin(), hits_hodo.end(), compareHits);



  if(hits_hodo.size()>0) {
	 auto seed_hodo = hits_hodo[0];
	 for (auto hit_hodo : hits_hodo) {
		 if(seed_hodo->getHitEnergy()>=0.5) hHitsHODOTime->Fill(hit_hodo->getHitTime() - seed_hodo->getHitTime());
	 }
  }

	for (auto hit_hodo : hits_hodo) {
		hHitsHODOPosition->Fill(hit_hodo->getHitDx(),hit_hodo->getHitDy());
		if(hit_hodo->m_channel.layer == 1){
			if(hit_hodo->m_channel.sector == 1)	EneHitHODO_layer1_sector1[hit_hodo->m_channel.component - 1]->Fill(hit_hodo->getHitEnergy());
			if(hit_hodo->m_channel.sector == 2)	EneHitHODO_layer1_sector2[hit_hodo->m_channel.component - 1]->Fill(hit_hodo->getHitEnergy());
			if(hit_hodo->m_channel.sector == 3)	EneHitHODO_layer1_sector3[hit_hodo->m_channel.component - 1]->Fill(hit_hodo->getHitEnergy());
			if(hit_hodo->m_channel.sector == 4)	EneHitHODO_layer1_sector4[hit_hodo->m_channel.component - 1]->Fill(hit_hodo->getHitEnergy());
			if(hit_hodo->m_channel.sector == 5)	EneHitHODO_layer1_sector5[hit_hodo->m_channel.component - 1]->Fill(hit_hodo->getHitEnergy());
			if(hit_hodo->m_channel.sector == 6)	EneHitHODO_layer1_sector6[hit_hodo->m_channel.component - 1]->Fill(hit_hodo->getHitEnergy());
			if(hit_hodo->m_channel.sector == 7)	EneHitHODO_layer1_sector7[hit_hodo->m_channel.component - 1]->Fill(hit_hodo->getHitEnergy());
			if(hit_hodo->m_channel.sector == 8)	EneHitHODO_layer1_sector8[hit_hodo->m_channel.component - 1]->Fill(hit_hodo->getHitEnergy());
		}

		if(hit_hodo->m_channel.layer == 2){
			if(hit_hodo->m_channel.sector == 1)	EneHitHODO_layer2_sector1[hit_hodo->m_channel.component - 1]->Fill(hit_hodo->getHitEnergy());
			if(hit_hodo->m_channel.sector == 2)	EneHitHODO_layer2_sector2[hit_hodo->m_channel.component - 1]->Fill(hit_hodo->getHitEnergy());
			if(hit_hodo->m_channel.sector == 3)	EneHitHODO_layer2_sector3[hit_hodo->m_channel.component - 1]->Fill(hit_hodo->getHitEnergy());
			if(hit_hodo->m_channel.sector == 4)	EneHitHODO_layer2_sector4[hit_hodo->m_channel.component - 1]->Fill(hit_hodo->getHitEnergy());
			if(hit_hodo->m_channel.sector == 5)	EneHitHODO_layer2_sector5[hit_hodo->m_channel.component - 1]->Fill(hit_hodo->getHitEnergy());
			if(hit_hodo->m_channel.sector == 6)	EneHitHODO_layer2_sector6[hit_hodo->m_channel.component - 1]->Fill(hit_hodo->getHitEnergy());
			if(hit_hodo->m_channel.sector == 7)	EneHitHODO_layer2_sector7[hit_hodo->m_channel.component - 1]->Fill(hit_hodo->getHitEnergy());
			if(hit_hodo->m_channel.sector == 8)	EneHitHODO_layer2_sector8[hit_hodo->m_channel.component - 1]->Fill(hit_hodo->getHitEnergy());
		}

//
	}
	hClustHODOmult->Fill(clusters_hodo.size());
  //   cout << "plugin"<<endl;
	if(clusters_hodo.size()>0){
	//	cout << "new cluster hodo" << " "<< clusters_hodo.size()<<endl;
		for(int i=0; i<clusters_hodo.size(); i++){
		  auto cluster_hodo = clusters_hodo[i];
		  hClustHODOHitmult->Fill(cluster_hodo->getClusterSize());
		  hClustHODOEne->Fill(cluster_hodo->getClusterFullEnergy());
		//	cout<< cluster_hodo->getX()<< " "<<cluster_hodo->getY()<<endl;
		  hClustHODOPosition->Fill(cluster_hodo->getX(), cluster_hodo->getY());


		  auto seed_hodo = 	cluster_hodo->getHit(0);
		  for(int i = 1; i < cluster_hodo->getClusterSize(); i++){
			    auto hit_hodo = cluster_hodo->getHit(i);
	     	hClustHODOTimeSeed_hit->Fill(hit_hodo->getHitTime() - seed_hodo->getHitTime());
	     	hClustHODOTimeSeedEne_hit->Fill(hit_hodo->getHitEnergy(), hit_hodo->getHitTime() - seed_hodo->getHitTime());
	     	if(hit_hodo->m_channel.layer == 1) hClustHODOEneHit_layer1 -> Fill(hit_hodo->getHitEnergy());
	     	if(hit_hodo->m_channel.layer == 2) hClustHODOEneHit_layer2 -> Fill(hit_hodo->getHitEnergy());
		  }

		  double seed_layer1_ene =0;
		  double seed_layer2_ene =0;

		  double seed_layer1_t =0;
		  double seed_layer2_t =0;


		  for(int i = 0; i < cluster_hodo->getClusterSize(); i++){
			    auto hit_hodo = cluster_hodo->getHit(i);

			    if(hit_hodo->m_channel.layer == 1 && hit_hodo->getHitEnergy() > seed_layer1_ene) {
			    	seed_layer1_ene = hit_hodo->getHitEnergy();
			    	seed_layer1_t = hit_hodo->getHitTime();
			    }
			    if(hit_hodo->m_channel.layer == 2 && hit_hodo->getHitEnergy() > seed_layer2_ene) {
			    	seed_layer2_ene = hit_hodo->getHitEnergy();
			    	seed_layer2_t = hit_hodo->getHitTime();
			    }
		  }
		//  cout << seed_layer1_ene<< " "<<seed_layer2_ene<<endl;
		  hClustHODOSeed1vsSeed2->Fill(seed_layer1_ene,seed_layer2_ene);
		  hClustHODO_DTSeedvsSeed2->Fill(seed_layer2_t-seed_layer1_t,seed_layer2_ene);
		  if(seed_layer1_ene<0.5) hClustHODO_DTSeedvsSeed2_seed1th->Fill(seed_layer2_t-seed_layer1_t,seed_layer2_ene);
	}
	}


	// STUDIO per match con HODO

   int j=0;
	for (auto cluster : clusters) {
		if(j==0){
			auto seed_cal_time = cluster->getHit(0)->getHitTime();
			for (auto hit_hodo : hits_hodo) {
				hTimeSeedcal_hodohit->Fill(hit_hodo->getHitTime() - seed_cal_time) ;
			}
			j++;
		}

  //    cout << "new clusters"<<endl;
		for (auto hodoscope : clusters_hodo) {
			auto diffX = (hodoscope->getX() - cluster->getX());
			auto diffY = (hodoscope->getY() - cluster->getY());
	        auto difft = (hodoscope->getClusterTime() - cluster->getClusterTime());

	        hmatch_diffX->Fill(diffX);
	        hmatch_diffY->Fill(diffY);
	        hmatch_diffT->Fill(difft);
	        hmatch_diffX_diffY->Fill(diffX,diffY);
	        if(fabs(diffX)<=30 && fabs(diffY)<=30) {
	//        cout <<  "ECAL time clus "<< cluster->getClusterTime()<< " time seed "<< cluster->getHit(0)->getHitTime()<< " Time seed no corr "<< cluster->getHit(0)->getHitTime() -cluster->getHit(0)->getTimeWalkCorrection()<<endl;
	 //       cout << " HODO time clus" << hodoscope->getClusterTime()<< " "<< hodoscope->getHit(0)->getHitDx()<<" "<<hodoscope->getHit(0)->getHitDy()<<endl;
	  //      cout << "DIFF T"<< difft<<endl;

	       hmatch_diffT_cut->Fill(difft);
	        }
		}


	}


	// Using particle
	int Ngamma =0;

	vector<const FTParticle*> gammas;

	for (auto particle:particles){
		if(particle->getParticleCharge() ==0){
			Ngamma = Ngamma+1;
			gammas.push_back(particle);
		}
	}
   //  cout << clusters.size()<< " "<< gammas.size()<<" "<< Ngamma<<endl;
	hNclustervsNgamma->Fill(clusters.size(), Ngamma);

	if(gammas.size()>=2){

		for(int j=0; j<gammas.size(); j++){
          auto gamma1 = gammas[j];
          auto theta_gamma1 = (std::atan((std::sqrt(std::pow(gamma1->getParticleDx(), 2.) + std::pow(gamma1->getParticleDy(), 2.))) /gamma1->getParticleDz())) * (180. / M_PI);
          for(int k=j+1; k<gammas.size(); k++){
        	  auto gamma2 = gammas[k];
        	  auto theta_gamma2 = (std::atan((std::sqrt(std::pow(gamma2->getParticleDx(), 2.) + std::pow(gamma2->getParticleDy(), 2.))) /gamma2->getParticleDz())) * (180. / M_PI);
        	  if(fabs(gamma1->getParticleTime()-gamma2->getParticleTime())<2){

  			auto z01 = cos(gamma1->getCentroid().Angle(gamma2->getCentroid()));
  		//	 cout << "gamma energy "<<gamma1->getParticleEnergy()<< " "<< gamma2->getParticleEnergy()<<endl;

  			double M01 = sqrt(2 * gamma1->getParticleEnergy() * gamma2->getParticleEnergy() * (1 - z01));

  		//	cout << z01<< " "<<M01<<endl;
  			hpi0->Fill(M01);
  	  		if(gamma1->getParticleEnergy()>500 && gamma2->getParticleEnergy()>500 && acos(z01)*(180. / M_PI)>2.5){
  	  			hpi0_angle->Fill(M01);
  	  		}
  if(theta_gamma1<4.5 && theta_gamma2<4.5 && theta_gamma1>2.5 && theta_gamma2>2.5) {
  		if(gamma1->getParticleEnergy()>500 && gamma2->getParticleEnergy()>500 && acos(z01)*(180. / M_PI)>2.5){
  			hpi0_raffa->Fill(M01);
  		}
  }

        	  }
          }

		}

	}

*/

	//Analisi sull'evento
	double eventSeedTime = 1e20;
	hHitsMolt->Fill(hits.size());
	hClustersMolt->Fill(clusters.size());
	hClustersMolt_noCorr->Fill(clusters_noCorr.size());
	hClustersMolt_Corr_noCorr->Fill(clusters.size(),clusters_noCorr.size() );

	for (auto hit : hits) {
		if (hit->getHitEnergy() > 2000 && hit->getHitTime() < eventSeedTime) {
			eventSeedTime = hit->getHitTime();
		}
		hHitsEnergy->Fill(hit->getHitEnergy());
		hHitsPosition->Fill(hit->getHitIX(), hit->getHitIY());
		hHitsEnergyPosition->Fill(hit->getHitIX(), hit->getHitIY(), hit->getHitEnergy());
		EneCrystal[hit->m_channel.component]->Fill(hit->getHitEnergy());
	}

	for (auto hit : hits) {
		hDelayFromSeed->Fill(hit->getHitTime() - eventSeedTime);
	}

	//cout << "before"<< Nclusters<<endl;

	//cout << "after"<< Nclusters<<endl;


	if (clusters.size() == 1) {

		auto cluster = clusters[0];
		auto seed = cluster->getHit(0);
		hSCHitsMolt->Fill(cluster->getClusterSize());
		hSCHitsEnergy->Fill(seed->getHitEnergy());
		hSCtheta->Fill(cluster->getTheta());
   //    cout << "***** size cluster: "<<cluster->getClusterSize()<<endl;

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
		hDCEneClus0vsEneClus1->Fill(cluster0->getClusterFullEnergy(),cluster1->getClusterFullEnergy() );

		auto distance_seed = sqrt(pow((seed0->getHitX() - seed1->getHitX()),2)+pow((seed0->getHitY() - seed1->getHitY()),2));
		hDCdistance_seed->Fill(distance_seed);

		if (abs(cluster0->getClusterTime() - cluster1->getClusterTime()) < 2) {
			hDCSeedEnergy1VsSeedEnergy2->Fill(seed0->getHitEnergy(), seed1->getHitEnergy());


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

		//	cout << cluster0->getX() << " "<<cluster0->getY()<<" "<< cluster0->getZ()<<endl;

			double z = cos(cluster0->getCentroid().Angle(cluster1->getCentroid()));

			double M = sqrt(2 * cluster0->getClusterFullEnergy() * cluster1->getClusterFullEnergy() * (1 - z));
			hDCInvariantMass->Fill(M);
			hInVMass_angle->Fill(M, acos(z)*180/3.1415);
			hInVMass_distance->Fill(M, distance_seed);
			hangle_distance->Fill(acos(z)*180/3.1415, distance_seed);
			if(acos(z)*(180. / M_PI)>2.5) hDCInvariantMass_angle->Fill(M);

	//if(cluster0->getTheta()<4.5 && cluster1->getTheta()<4.5 && cluster0->getTheta()>2.5 && cluster1->getTheta()>2.5) {
		if(cluster0->getClusterFullEnergy()>500 && cluster1->getClusterFullEnergy()>500 && acos(z)*(180. / M_PI)>2.5){   //0.035 rad = 2 deg
		hDCInvariantMass_Raffa->Fill(M);
		if(jana_cluster==1)hDCInvariantMass_Raffa_triggerClus->Fill(M);
		}
	//	}
		}
     // cout << "Eseed0 "<< seed0->getHitEnergy()<< " Eseed1 "<<seed1->getHitEnergy()<<endl;
	//	cout << "distance "<<distance_seed<<endl;

		/*
        cout << seed0->getHitEnergy()/cluster0->getClusterFullEnergy()<< " "<< seed1->getHitEnergy()/cluster1->getClusterFullEnergy()<<endl;
		cout << cluster0->getX() - cluster1->getX()<<endl;
		cout << cluster0->getY() - cluster1->getY()<<endl;
		*/
		/*
		if(clusters_noCorr.size() ==1){

			for (auto hit : hits) {
				if(cluster0->getHit(0)->m_channel.component != hit->m_channel.component ){
					auto xDiff = std::fabs(hit->getHitIX() - cluster0->getHit(0)->getHitIX());
					auto yDiff = std::fabs(hit->getHitIY() - cluster0->getHit(0)->getHitIY());
                  if(xDiff <= 1 && yDiff <= 1 && (xDiff + yDiff) > 0 ){
				DT_Hit_seed[hit->m_channel.component]->Fill(hit->getHitTime() - seed0->getHitTime());
				DT_Hit_seed_ene[hit->m_channel.component]->Fill(hit->getHitEnergy(), hit->getHitTime() - seed0->getHitTime());
				hDT_Hit_seed_fake2Cluster->Fill(hit->getHitTime() - seed0->getHitTime());
				hDT_Hit_seed_Vs_component_fake2Cluster->Fill(hit->getHitTime() - seed0->getHitTime(), hit->m_channel.component);
                  }
				}
				}


		}
		*/
		/*
		if((cluster0->getClusterTime() - cluster1->getClusterTime())<-6 &&(cluster0->getClusterTime() - cluster1->getClusterTime())>-15 ){
			cout <<clusters_noCorr.size()<<" "<<clusters.size()<<endl;
            cout<< "******** No Corr ****"<<endl;
           for(int c=0; c<clusters_noCorr.size(); c++){
        	   auto cluster_noCorr = clusters_noCorr[c];
        	   for (int i = 0; i < cluster_noCorr->getClusterSize(); i++) {
        		   auto hit = cluster_noCorr->getHit(i);
          cout << hit->m_channel.component<< " "<<hit->getHitEnergy()<< " "<<hit->getHitTime()<< " "<<endl;
        	   }

           }


			cout << "**** cluster 0 ***"<<endl;
			cout << "Time "<< cluster0->getClusterTime()<<"E tot "<< cluster0->getClusterFullEnergy()<<"X "<< cluster0->getX()<<" Y "<<cluster0->getY()<< endl;
	       //  if(j<30){
			for (int i = 0; i < cluster0->getClusterSize(); i++) {
						auto hit = cluster0->getHit(i);
		//		XYDCPosClus0_DT[j]->Fill(hit->getHitIX(), hit->getHitIY());
			cout << hit->m_channel.component<< " "<<hit->getHitEnergy()<< " "<<hit->getHitTime()<< " "<<hit->getHitTime()-seed0->getHitTime()<<endl;
	     	cout << "***** " <<hit->getHitTime()<< " "<< hit->getTimeWalkCorrection()<<" "<<hit->getHitTime() -hit->getTimeWalkCorrection()<<endl;
			}

			cout << "*** cluster 1 ****"<<endl;
		//	cout << "Time "<< cluster1->getClusterTime()<<"E tot "<< cluster1->getClusterFullEnergy()<<"X "<< cluster1->getX()<<" Y "<<cluster1->getY()<< endl;

			for (int i = 0; i < cluster1->getClusterSize(); i++) {
						auto hit = cluster1->getHit(i);
			cout << hit->m_channel.component<< " "<<hit->getHitEnergy()<< " "<<hit->getHitTime()<< " "<<hit->getHitTime()-seed1->getHitTime()<<endl;
			cout << "***** " <<hit->getHitTime()<< " "<< hit->getTimeWalkCorrection()<<" "<<hit->getHitTime() -hit->getTimeWalkCorrection()<<endl;
		//	XYDCPosClus1_DT[j]->Fill(hit->getHitIX(), hit->getHitIY());
			}
		//	j++;
	   //      }
	         cout << "***********"<<endl;

			hDCEneClus0vsEneClus1_DT->Fill(cluster0->getClusterFullEnergy(),cluster1->getClusterFullEnergy() );
			hDCEClus1vsEseedClus1_DT->Fill(seed1->getHitEnergy(),cluster1->getClusterFullEnergy() );
		}

		if(abs((cluster0->getClusterTime() - cluster1->getClusterTime()))<5){
			hDCEClus1vsEseedClus1->Fill(seed1->getHitEnergy(),cluster1->getClusterFullEnergy() );
		}
*/




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


	}



//Riempe CorrectionCurve, TH2D ritardo hit (rispetto al seed) vs energy hit, uno diverso per ogni component, da cui ricavare la curva di correzione
/*
	if (clusters_noCorr.size() == 1) {
	 auto seed = clusters_noCorr[0]->getHit(0);
	 for (int i = 1; i < clusters_noCorr[0]->getClusterSize(); i++) {
	 auto hit = clusters_noCorr[0]->getHit(i);
	 CorrectionCurve[hit->m_channel.component]->Fill(hit->getHitEnergy(), hit->getHitTime() - seed->getHitTime());
	 }
	 }
*/



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
