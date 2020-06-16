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
//#include "FT/FTCalHitTimeCorr.h"
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

using namespace std;

/*Here goes the histograms*/
static TH1D *hTest = 0;
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
static vector<TH1D *> CristalTimeDistribution;
static vector<TH1D *> CristalTimeDistribution_TimeCorr;
static vector<TH2D *> CorrectionCurve2GeV;
static vector<TH2D *> CorrectionCurve4GeV;
static vector<TH2D *> CorrectionCurve6GeV;
static vector<TH1D *> CrystalEnergy;
static vector<TH1D *> CrystalEnergy_corr;
static vector<TH1D *> CrystalTimeCorrection;

static TH2D *hSeedDx = 0;
static TH2D *hSeedSx = 0;

static vector<TH2D *> IntEvent;
static vector<TH2D *> dTimeVsEne;

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

static TH2D *hMoltHitVsEnergyClus = 0;
static TH2D *hMoltHitVsEnergyClus_corr = 0;
static TH2D *hMoltHitVsComponentSeed = 0;
static TH2D *hMoltHitVsComponentSeed_corr = 0;
static TH2D *hMoltEventVsMoltHit = 0;
static TH2D *hMoltEventVsMoltHit_corr = 0;
static TH2D *hEneClusVsEneSeed = 0;
static TH2D *hEneClusVsEneSeed_corr = 0;
static TH3D *hMolHitVsXVsY = 0;

static TH1D *hInvMass = 0;
static TH1D *hInvMass_sideband150 = 0;
static TH1D *hInvMass_sidebandMinus120 = 0;

//Selezione eventi "basica"
const int firstEvent = 0;
const int lastEvent = 50;
static int eventCounter = 0;

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

	hTest = new TH1D("hTest", "hTest", 20, -.5, 19.5);

	/*
	 //	hSeedDx = new TH2D("hSeedDx", "hSeedDx", 1000, 0, 10000, 40, -5.5, 34.5);
	 //	hSeedSx = new TH2D("hSeedSx", "hSeedSx", 1000, 0, 10000, 40, -5.5, 34.5);

	 hdTime = new TH1D("hdTime", "hdTime", 80, -40.5, 39.5);
	 hdTime_corr = new TH1D("hdTime_corr", "hdTime_corr", 80, -40.5, 39.5);

	 hMoltHit = new TH1D("hMoltHit", "hMoltHit", 30, -0.5, 29.5);
	 hMoltHit_corr = new TH1D("hMoltHit_corr", "hMoltHit_corr", 30, -0.5, 29.5);

	 hMoltClus = new TH1D("hMoltClus", "hMoltClus", 10, -0.5, 9.5);
	 hMoltClus_corr = new TH1D("hMoltClus_corr", "hMoltClus_corr", 10, -0.5, 9.5);

	 hEneClus = new TH1D("hEneClus", "hEneClus", 1500, 0, 15000);
	 hEneClus_corr = new TH1D("hEneClus_corr", "hEneClus_corr", 1500, 0, 15000);

	 hTimeClus = new TH1D("hTimeClus", "hTimeClus", 60, -30, 30);
	 hTimeClus_corr = new TH1D("hTimeClus_corr", "hTimeClus_corr", 60, -30, 30);
	 h2ClusTimeDist = new TH1D("h2ClusTimeDist", "2hClusTimeDist", 801, -400, 400);
	 h2ClusTimeDist_corr = new TH1D("h2ClusTimeDist_corr", "2hClusTimeDist_corr", 801, -400, 400);

	 hEneSeed = new TH1D("hEneSeed", "hEneSeed", 1500, 0, 15000);
	 hEneSeed_corr = new TH1D("hEneSeed_corr", "hEneSeed_corr", 1500, 0, 15000);

	 hClusterEnergyVsTheta = new TH2D("hClusterEnergyVsTheta", "hClusterEnergyVsTheta", 28, 0, 7, 1500, 0, 15000);
	 hClusterEnergyVsTheta_TimeCorr = new TH2D("hClusterEnergyVsTheta_TimeCorr", "hClusterEnergyVsTheta_TimeCorr", 28, 0, 7, 1500, 0, 15000);

	 hInvMass = new TH1D("hInvMass", "hInvMass", 500, 0, 500);
	 hInvMass_sideband150 = new TH1D("hInvMass_sideband150", "hInvMass_sideband150", 500, 0, 500);
	 hInvMass_sidebandMinus120 = new TH1D("hInvMass_sidebandMinus120", "hInvMass_sidebandMinus120", 500, 0, 500);

	 hMoltHitVsEnergyClus = new TH2D("hMoltHitVsEnergyClus", "hMoltHitVsEnergyClus", 1500, 0, 15000, 20, 0, 20);
	 hMoltHitVsEnergyClus_corr = new TH2D("hMoltHitVsEnergyClus_corr", "hMoltHitVsEnergyClus_corr", 1500, 0, 15000, 20, 0, 20);

	 hMoltHitVsComponentSeed = new TH2D("hMoltHitVsComponentSeed", "hMoltHitVsComponentSeed", 500, 0, 500, 20, 0, 20);
	 hMoltHitVsComponentSeed_corr = new TH2D("hMoltHitVsComponentSeed_corr", "hMoltHitVsComponentSeed_corr", 500, 0, 500, 20, 0, 20);
	 hMolHitVsXVsY = new TH3D("hMolHitVsXVsY", "hMolHitVsXVsY", 25, -0.5, 24.5, 25, -0.5, 24.5, 20, 0, 20);

	 hMoltEventVsMoltHit = new TH2D("hMoltEventVsMoltHit", "hMoltEventVsMoltHit", 30, 0, 30, 30, 0, 30);
	 hMoltEventVsMoltHit_corr = new TH2D("hMoltEventVsMoltHit_corr", "hMoltEventVsMoltHit_corr", 30, 0, 30, 30, 0, 30);

	 hEneClusVsEneSeed = new TH2D("hEneClusVsEneSeed", "hEneClusVsEneSeed", 1500, 0, 15000, 1500, 0, 15000);
	 hEneClusVsEneSeed_corr = new TH2D("hEneClusVsEneSeed_corr", "hEneClusVsEneSeed_corr", 1500, 0, 15000, 1500, 0, 15000);

	 for (int i = 0; i < 500; i++) {
	 TH1D *hCrystalEnergy = new TH1D(Form("hCrystalEnergy%d", i), Form("hCrystalEnergy%d", i), 1500, 0, 15000);
	 CrystalEnergy.push_back(hCrystalEnergy);
	 TH1D *hCrystalEnergy_corr = new TH1D(Form("hCrystalEnergy_corr%d", i), Form("hCrystalEnergy_corr%d", i), 1500, 0, 15000);
	 CrystalEnergy_corr.push_back(hCrystalEnergy_corr);
	 }*/

	for (int i = 0; i < 500; i++) {
		TH2D *hdTimeVsEne = new TH2D(Form("hdTimeVsEne%d", i), Form("hdTimeVsEne%d", i), 60, -30, 30, 15000, 0, 15000);
		dTimeVsEne.push_back(hdTimeVsEne);
	}

	/*	for (int i = 0; i < 500; i++) {
	 TH1D *hCrystalTimeCorrection = new TH1D(Form("hCrystalTimeCorrection%d", i), Form("hCrystalTimeCorrection%d", i), 100, -80, 20);
	 CrystalTimeCorrection.push_back(hCrystalTimeCorrection);
	 }*/

	/*	for (int j = 0; j < 500; j++) {
	 //		TH2D *hCorrectionCurve = new TH2D(Form("hCorrectionCurve%d", j), Form("hCorrectionCurve%d", j), 1000, 0, 10000, 60, -25.5, 34.5);
	 //		CorrectionCurve.push_back(hCorrectionCurve);
	 TH2D *hCorrectionCurve2GeV = new TH2D(Form("hCorrectionCurve2GeV%d", j), Form("hCorrectionCurve2GeV%d", j), 1000, 0, 10000, 60, -25.5, 34.5);
	 CorrectionCurve2GeV.push_back(hCorrectionCurve2GeV);
	 TH2D *hCorrectionCurve4GeV = new TH2D(Form("hCorrectionCurve4GeV%d", j), Form("hCorrectionCurve4GeV%d", j), 1000, 0, 10000, 60, -25.5, 34.5);
	 CorrectionCurve4GeV.push_back(hCorrectionCurve4GeV);
	 TH2D *hCorrectionCurve6GeV = new TH2D(Form("hCorrectionCurve6GeV%d", j), Form("hCorrectionCurve6GeV%d", j), 1000, 0, 10000, 60, -25.5, 34.5);
	 CorrectionCurve6GeV.push_back(hCorrectionCurve6GeV);
	 }*/
	/*	for (int j = 0; j < 500; j++) {
	 TH1D *hCristalTimeDistribution = new TH1D(Form("hCristalTimeDistribution%d", j), Form("hCristalTimeDistribution%d", j), 81, -40.5, 40.5);
	 CristalTimeDistribution.push_back(hCristalTimeDistribution);
	 TH1D *hCristalTimeDistribution_TimeCorr = new TH1D(Form("hCristalTimeDistribution_TimeCorr%d", j), Form("hCristalTimeDistribution_TimeCorr%d", j), 81, -40.5, 40.5);
	 CristalTimeDistribution_TimeCorr.push_back(hCristalTimeDistribution_TimeCorr);

	 }*/

	/*	for (int j = 0; j < 500; j++) {
	 TH2D *hTwentyNsSx = new TH2D(Form("hTwentyNsSx%d", j), Form("hTwentyNsSx%d", j), 1000, 0, 10000, 60, -25.5, 34.5);
	 TH2D *hTwentyNsDx = new TH2D(Form("hTwentyNsDx%d", j), Form("hTwentyNsDx%d", j), 1000, 0, 10000, 60, -25.5, 34.5);
	 TwentyNsSx.push_back(hTwentyNsSx);
	 TwentyNsDx.push_back(hTwentyNsDx);
	 }*/

	/*	for (int j = 0; j < 500; j++) {
	 TH2D *hEnergyVsCorrEnergy = new TH2D(Form("hEnergyVsCorrEnergy%d", j), Form("hEnergyVsCorrEnergy%d", j), 1000, 0, 10000, 1000, 0, 10000);
	 EnergyVsCorrEnergy.push_back(hEnergyVsCorrEnergy);
	 }*/

	gDirectory->cd();
	m_root_lock->release_lock();

}

//------------------
// Process
//------------------
void JEventProcessor_HallBFT_simone::Process(const std::shared_ptr<const JEvent>& aEvent) {

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
//	auto hits_TimeCorr = aEvent->Get<const FTCalHitTimeCorr>();

//Clusters dell'evento
	auto clusters = aEvent->Get<FTCalCluster>();
	auto clusters_TimeCorr = aEvent->Get < FTCalCluster > ("TimeCorr");
	auto clusters_EneCorr = aEvent->Get < FTCalCluster > ("EneCorr"); //vector dei clusters dell'evento con correzione sull'energia degli hit

//Numero dell'evento
	auto eventNumber = aEvent->GetEventNumber();

//lock
	m_root_lock->acquire_write_lock();

	//RIEMPE istogrammi per i cristalli della colonna x=12. Histo ritardo hit vs energy. Due histo per seed nella metà di destra o nella metà di sinistra del calorimetro
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
	/*	if (eventNumber > 1000000) {
	 if (clusters_TimeCorr.size() == 1) {
	 auto seed = clusters_TimeCorr[0]->getHit(0);
	 for (int i = 1; i < clusters_TimeCorr[0]->getClusterSize(); i++) {
	 auto hit = clusters_TimeCorr[0]->getHit(i);
	 CorrectionCurve[hit->m_channel.component]->Fill(hit->getHitEnergy(), hit->getHitTime() - seed->getHitTime());
	 }
	 }
	 }*/

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

	//Riempe istogramma 1D della distribuzione del tempo degli hit relativo al seed, per ogni cristallo.
	/*	if (eventNumber > 1000000) {
	 if (clusters.size() == 1 && clusters_TimeCorr.size() == 1) {
	 auto seed = clusters[0]->getHit(0);
	 for (int i = 0; i < clusters[0]->getClusterSize(); i++) {
	 auto hit = clusters[0]->getHit(i);
	 CristalTimeDistribution[hit->m_channel.component]->Fill(hit->getHitTime() - seed->getHitTime());
	 }
	 auto seed_corr = clusters_TimeCorr[0]->getHit(0);
	 for (int i = 0; i < clusters_TimeCorr[0]->getClusterSize(); i++) {
	 auto hit = clusters_TimeCorr[0]->getHit(i);
	 CristalTimeDistribution_TimeCorr[hit->m_channel.component]->Fill(hit->getHitTime() - seed_corr->getHitTime());
	 }
	 }
	 }*/

//	TH2D Energia corretta vs Energia per ogni cristallo
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

//	Distribuzione per ogni cristallo delle energie misurate, non corrette.
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
	 }

	 //	Distribuzione aggregata dei ritardi degli hit dei cluster. Per eventi con 1 cluster e 1 cluster con tempi corretti, produce la distribuzione temporale degli hit del cluster per entrambi i casi.
	 if (clusters.size() == 1) {
	 auto seed = clusters[0]->getHit(0);
	 for (int i = 0; i < clusters[0]->getClusterSize(); i++) {
	 auto hit = clusters[0]->getHit(i);
	 hdTime->Fill(hit->getHitTime() - seed->getHitTime());
	 }
	 }
	 if (clusters_TimeCorr.size() == 1) {
	 auto seed_TimeCorr = clusters_TimeCorr[0]->getHit(0);
	 for (int i = 0; i < clusters_TimeCorr[0]->getClusterSize(); i++) {
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
	 if (clusters.size() == 1) {
	 hMoltHitVsComponentSeed->Fill(clusters[0]->getHit(0)->m_channel.component, clusters[0]->getClusterSize());
	 }
	 if (clusters_TimeCorr.size() == 1) {
	 hMoltHitVsComponentSeed_corr->Fill(clusters_TimeCorr[0]->getHit(0)->m_channel.component, clusters_TimeCorr[0]->getClusterSize());
	 hMolHitVsXVsY->Fill(clusters_TimeCorr[0]->getCentroid().X(), clusters_TimeCorr[0]->getCentroid().Y(), clusters_TimeCorr[0]->getClusterSize());
	 }

	 // Molteplicità hit nell'evento vs molteplicità hit nel cluster
	 /*	if (clusters.size() == 1) {
	 hMoltEventVsMoltHit->Fill(hits.size(), clusters[0]->getClusterSize());
	 }*/

//	Energia del cluster vs energia del seed
	/*	if (clusters.size() == 1) {
	 hEneClusVsEneSeed->Fill(clusters[0]->getClusterEnergy(), clusters[0]->getHit(0)->getHitEnergy());
	 }
	 if (clusters_TimeCorr.size() == 1) {
	 hEneClusVsEneSeed_corr->Fill(clusters_TimeCorr[0]->getClusterEnergy(), clusters_TimeCorr[0]->getHit(0)->getHitEnergy());
	 }*/

	if (clusters_TimeCorr.size() == 1) {
		for (int i = 0; i < clusters_TimeCorr[0]->getClusterSize(); i++) {
			auto hit = clusters_TimeCorr[0]->getHit(i);
			dTimeVsEne[hit->m_channel.component]->Fill(hit->getTimeWalkCorrection(), hit->getHitEnergy());
		}
	}

	/* produce la distribuzione energetica dei cluster in funzione del coseno dell'angolo polare
	 if (clusters.size() == 1) {
	 hClusterEnergyVsTheta->Fill(clusters[0]->getCentroid().CosTheta(), clusters[0]->getClusterEnergy());
	 for (int i = 0; i < clusters[0]->getClusterSize(); i++) {
	 auto hit = clusters[0]->getHit(i);
	 cout << hit->getHitEnergy() << " " << hit->getHitTime() << " " << hit->getHitIX() << " " << hit->getHitIY() << endl;
	 }
	 cout << clusters[0]->getCentroid().CosTheta() << " " << clusters[0]->getClusterEnergy() << endl;
	 cout << clusters[0]->getCentroid().X() << " " << clusters[0]->getCentroid().Y() << " " << clusters[0]->getCentroid().Z() << endl;
	 }*/

//	Produce la distribuzione energetica dei cluster in funzione del coseno dell'angolo polare, per eventi con tempo corretto.
	/*	if (clusters.size() == 1 && clusters_TimeCorr.size() == 1) {
	 hClusterEnergyVsTheta->Fill(clusters[0]->getCentroid().Theta() * 180 / M_PI, clusters[0]->getClusterEnergy());
	 hClusterEnergyVsTheta_TimeCorr->Fill(clusters_TimeCorr[0]->getCentroid().Theta() * 180 / M_PI, clusters_TimeCorr[0]->getClusterEnergy());
	 }*/

//	Eventi a due cluster, distribuzione dei tempi
	/*	if (clusters.size() == 2) {
	 h2ClusTimeDist->Fill(clusters[0]->getClusterTime() - clusters[1]->getClusterTime());
	 }
	 if (clusters_TimeCorr.size() == 2) {
	 h2ClusTimeDist_corr->Fill(clusters_TimeCorr[0]->getClusterTime() - clusters_TimeCorr[1]->getClusterTime());
	 }*/

//	Istogramma della molteplicità degli hit vs energia del cluster; versione senza correzione e con correzione.
//	Pi0 mass find
	/*	if (clusters_TimeCorr.size() == 2) {
	 auto cluster1 = clusters_TimeCorr[0];
	 auto cluster2 = clusters_TimeCorr[1];
	 if (abs(cluster1->getClusterTime() - cluster2->getClusterTime()) < 6) {
	 auto z = cos(cluster1->getCentroid().Angle(cluster2->getCentroid()));
	 auto M = sqrt(2 * cluster1->getClusterEnergy() * cluster2->getClusterEnergy() * (1 - z));
	 hInvMass->Fill(M);
	 }
	 if (cluster1->getClusterTime() - cluster2->getClusterTime() > 150 && cluster1->getClusterTime() - cluster2->getClusterTime() < 162) {
	 auto z = cos(cluster1->getCentroid().Angle(cluster2->getCentroid()));
	 auto M = sqrt(2 * cluster1->getClusterEnergy() * cluster2->getClusterEnergy() * (1 - z));
	 hInvMass_sideband150->Fill(M);
	 }
	 if (cluster1->getClusterTime() - cluster2->getClusterTime() > -120 && cluster1->getClusterTime() - cluster2->getClusterTime() < -108) {
	 auto z = cos(cluster1->getCentroid().Angle(cluster2->getCentroid()));
	 auto M = sqrt(2 * cluster1->getClusterEnergy() * cluster2->getClusterEnergy() * (1 - z));
	 hInvMass_sidebandMinus120->Fill(M);
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

//	Correzioni applicate su ogni cristallo
	/*	if (clusters_TimeCorr.size() == 1) {
	 for (int i = 0; i < clusters_TimeCorr[0]->getClusterSize(); i++) {
	 auto hit = clusters_TimeCorr[0]->getHit(i);
	 CrystalTimeCorrection[hit->m_channel.component]->Fill(hit->getTimeWalkCorrection());
	 }
	 }*/

	m_root_lock->release_lock();
//unlock

}

//------------------
// Finish
//------------------
void JEventProcessor_HallBFT_simone::Finish(void) {
// This is called when at the end of event processing

//	hMinvRapportoSideband->Add("hMinv2C2GeV30ns", -"hMinvSideband");

//hMinvSideband->GetEntries(), hMinv2C2GeV30ns->GetEntries()

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
