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
static vector<TH2D *> HitsEnergy_timeCorr;
static vector<TH2D *> HitsTime_timeCorr;
static vector<TH2D *> ClusterHitsEnergy_timeCorr;
static vector<TH2D *> ClusterHitsTime_timeCorr;
static vector<TH2D *> TimeWalkViewer;
static vector<TH1D *> TimeDistribution;
static vector<TH1D *> TimeDistribution_timeCorr;
static vector<TH2D *> CorrectionCurve;
static vector<TH2D *> EnergyVsCorrEnergy;

static TH2D *hSeedDx = 0;
static TH2D *hSeedSx = 0;

static TH2D *hClusterEnergyVsTheta = 0;
static TH2D *hClusterEnergyVsTheta_timeCorr = 0;

static vector<TH2D *> IntEvent;

static TH1D *hdTime = 0;
static TH1D *hdTime_corr = 0;

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

//	hSeedDx = new TH2D("hSeedDx", "hSeedDx", 1000, 0, 10000, 40, -5.5, 34.5);
//	hSeedSx = new TH2D("hSeedSx", "hSeedSx", 1000, 0, 10000, 40, -5.5, 34.5);

//	hdTime = new TH1D("hdTime", "hdTime", 60, -20.5, 39.5);
//	hdTime_corr = new TH1D("hdTime_corr", "hdTime_corr", 60, -20.5, 39.5);

//	for (int j = 0; j < 500; j++) {
//		TH2D *hCorrectionCurve = new TH2D(Form("hCorrectionCurve%d", j), Form("hCorrectionCurve%d", j), 1000, 0, 10000, 40, -5.5, 34.5);
//		CorrectionCurve.push_back(hCorrectionCurve);
//	}

	for (int j = 0; j < 500; j++) {
		TH2D *hEnergyVsCorrEnergy = new TH2D(Form("hEnergyVsCorrEnergy%d", j), Form("hEnergyVsCorrEnergy%d", j), 1000, 0, 10000, 1000, 0, 10000);
		EnergyVsCorrEnergy.push_back(hEnergyVsCorrEnergy);
	}

//	hClusterEnergyVsTheta = new TH2D("hClusterEnergyVsTheta", "hClusterEnergyVsTheta", 100, 0.995, 1, 5000, 0, 10000);
//	hClusterEnergyVsTheta_timeCorr = new TH2D("hClusterEnergyVsTheta_timeCorr", "hClusterEnergyVsTheta_timeCorr", 100, 0.995, 1, 5000, 0, 10000);

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
//	auto hits_timeCorr = aEvent->Get<const FTCalHitTimeCorr>();

	//Clusters dell'evento
	auto clusters = aEvent->Get<FTCalCluster>();
	auto clusters_timeCorr = aEvent->Get < FTCalCluster > ("TimeCorr");
	auto clusters_EneCorr = aEvent->Get < FTCalCluster > ("EneCorr"); //vector dei clusters dell'evento con correzione sull'energia degli hit

	//Numero dell'evento
	auto eventNumber = aEvent->GetEventNumber();

	//lock
	m_root_lock->acquire_write_lock();

	/*if (clusters.size() == 1) {
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
	 for (int i = 0; i < clusters[0]->getClusterSize(); i++) {
	 auto hit = clusters[0]->getHit(i);
	 if (hit->getHitIX() == 12) {
	 hSeedSx->Fill(hit->getHitEnergy(), hit->getHitTime() - seed->getHitTime());
	 }
	 }
	 } else {
	 for (int i = 0; i < clusters[0]->getClusterSize(); i++) {
	 auto hit = clusters[0]->getHit(i);
	 if (hit->getHitIX() == 12) {
	 hSeedDx->Fill(hit->getHitEnergy(), hit->getHitTime() - seed->getHitTime());
	 }
	 }
	 }
	 }
	 }*/

	/*	if (eventNumber > 1000000) {
	 if (clusters.size() == 1) {
	 auto seed = clusters[0]->getHit(0);
	 for (int i = 0; i < clusters[0]->getClusterSize(); i++) {
	 auto hit = clusters[0]->getHit(i);
	 CorrectionCurve[hit->m_channel.component]->Fill(hit->getHitEnergy(), hit->getHitTime() - seed->getHitTime());
	 }
	 }
	 }
	 */

	if (clusters.size() == 1 && clusters_EneCorr.size() == 1) {
		if (clusters[0]->getClusterSize() == clusters_EneCorr[0]->getClusterSize()) {
			for (int i = 0; i < clusters[0]->getClusterSize(); i++) {
				auto hit = clusters[0]->getHit(i);
				auto hit_EC = clusters_EneCorr[0]->getHit(i);
				if (hit->m_channel.component == hit_EC->m_channel.component) {
					EnergyVsCorrEnergy[hit->m_channel.component]->Fill(hit_EC->getHitEnergy(), hit->getHitEnergy());
				}
			}
		}
	}

//	if (clusters.size() == 1) {
//		bool flag = false;
//		for (int i = 0; i < clusters[0]->getClusterSize(); i++) {
//			auto hit = clusters[0]->getHit(i);
//			if (hit->getHitIX() == 12) {
//				flag = true;
//				break;
//			}
//		}
//		if (flag == true) {
//			TH2D *hEvent = new TH2D(Form("hEvent%d", eventNumber), Form("hEvent%d", eventNumber), 25, -0.5, 24.5, 25, -0.5, 24.5);
//			auto seed = clusters[0]->getHit(0);
//			for (int i = 0; i < clusters[0]->getClusterSize(); i++) {
//				auto hit = clusters[0]->getHit(i);
//				if (hit->getHitTime() - seed->getHitTime() != 0) {
//					hEvent->Fill(hit->getHitIX(), hit->getHitIY(), hit->getHitTime() - seed->getHitTime());
//				} else {
//					hEvent->Fill(hit->getHitIX(), hit->getHitIY(), 1);
//				}
//			}
//			IntEvent.push_back(hEvent);
//		}
//	}
//	if (eventNumber >= firstEvent && eventNumber <= lastEvent && firstEvent != lastEvent) {
//	if (eventCounter < 50) {
//		eventCounter++;
//		TH2D *hHitsEnergy = new TH2D(Form("hHitsEnergy%d", eventNumber), Form("hHitsEnergy%d", eventNumber), 25, -0.5, 24.5, 25, -0.5, 24.5);
//		TH2D *hHitsTime = new TH2D(Form("hHitsTime%d", eventNumber), Form("hHitsTime%d", eventNumber), 25, -0.5, 24.5, 25, -0.5, 24.5);
//		TH2D *hClusterHitsEnergy = new TH2D(Form("hClusterHitsEnergy%d", eventNumber), Form("hClusterHitsEnergy%d", eventNumber), 25, -0.5, 24.5, 25, -0.5, 24.5);
//		TH2D *hClusterHitsTime = new TH2D(Form("hClusterHitsTime%d", eventNumber), Form("hClusterHitsTime%d", eventNumber), 25, -0.5, 24.5, 25, -0.5, 24.5);
//
//		TH2D *hClusterHitsEnergy_timeCorr = new TH2D(Form("hClusterHitsEnergy_timeCorr%d", eventNumber), Form("hClusterHitsEnergy_timeCorr%d", eventNumber), 25, -0.5, 24.5, 25, -0.5, 24.5);
//		TH2D *hClusterHitsTime_timeCorr = new TH2D(Form("hClusterHitsTime_timeCorr%d", eventNumber), Form("hClusterHitsTime_timeCorr%d", eventNumber), 25, -0.5, 24.5, 25, -0.5, 24.5);
//
//		TH2D *hTimeSpread = new TH2D(Form("hTimeSpread%d", eventNumber), Form("hTimeSpread%d", eventNumber), 25, -0.5, 24.5, 25, -0.5, 24.5);
//		for (auto hit : hits) {
//			hHitsEnergy->Fill(hit->getHitIX(), hit->getHitIY(), hit->getHitEnergy());
//			if (hit->getHitTime() != 0) {
//				hHitsTime->Fill(hit->getHitIX(), hit->getHitIY(), hit->getHitTime());
//			} else {
//				hHitsTime->Fill(hit->getHitIX(), hit->getHitIY(), 1);
//			}
//		}
//
//		for (auto cluster : clusters) {
//			for (int i = 0; i < cluster->getClusterSize(); i++) {
//				auto hit = cluster->getHit(i);
//				hClusterHitsEnergy->Fill(hit->getHitIX(), hit->getHitIY(), hit->getHitEnergy());
//				if (hit->getHitTime() != 0) {
//					hClusterHitsTime->Fill(hit->getHitIX(), hit->getHitIY(), hit->getHitTime());
//				} else {
//					hClusterHitsTime->Fill(hit->getHitIX(), hit->getHitIY(), 1);
//				}
//			}
//		}
//
//		for (auto cluster : clusters_timeCorr) {
//			for (int i = 0; i < cluster->getClusterSize(); i++) {
//				auto hit = cluster->getHit(i);
//				hClusterHitsEnergy_timeCorr->Fill(hit->getHitIX(), hit->getHitIY(), hit->getHitEnergy());
//				if (hit->getHitTime() != 0) {
//					hClusterHitsTime_timeCorr->Fill(hit->getHitIX(), hit->getHitIY(), hit->getHitTime());
//				} else {
//					hClusterHitsTime_timeCorr->Fill(hit->getHitIX(), hit->getHitIY(), 1);
//				}
//			}
//		}
//
//		if (clusters.size() == 1 && clusters_timeCorr.size() == 1) {
//			TH1D *hTimeDistribution = new TH1D(Form("hTimeDistribution%d", eventNumber), Form("hTimeDistribution%d", eventNumber), 45, -10.5, 34.5);
//			TH1D *hTimeDistribution_timeCorr = new TH1D(Form("hTimeDistribution_timeCorr%d", eventNumber), Form("hTimeDistribution_timeCorr%d", eventNumber), 45, -10.5, 34.5);
//
//			auto seed = clusters[0]->getHit(0);
//			for (int i = 0; i < clusters[0]->getClusterSize(); i++) {
//				auto hit = clusters[0]->getHit(i);
//				if (hit->getHitTime() - seed->getHitTime() != 0) {
////					hTimeSpread->Fill(hit->getHitIX(), hit->getHitIY(), hit->getHitTime() - seed->getHitTime());
//				} else {
////					hTimeSpread->Fill(hit->getHitIX(), hit->getHitIY(), 1);
//				}
//
//				hTimeDistribution->Fill(hit->getHitTime() - seed->getHitTime());
//			}
//			auto seed_timeCorr = clusters_timeCorr[0]->getHit(0);
//			for (int i = 0; i < clusters_timeCorr[0]->getClusterSize(); i++) {
//				auto hit = clusters_timeCorr[0]->getHit(i);
//				hTimeDistribution_timeCorr->Fill(hit->getHitTime() - seed_timeCorr->getHitTime());
//			}
//			TimeDistribution.push_back(hTimeDistribution);
//			TimeDistribution_timeCorr.push_back(hTimeDistribution_timeCorr);
//		}
//		HitsEnergy.push_back(hHitsEnergy);
//		HitsTime.push_back(hHitsTime);
//		ClusterHitsEnergy.push_back(hClusterHitsEnergy);
//		ClusterHitsTime.push_back(hClusterHitsTime);
//
//		ClusterHitsEnergy_timeCorr.push_back(hClusterHitsEnergy_timeCorr);
//		ClusterHitsTime_timeCorr.push_back(hClusterHitsTime_timeCorr);
//
//		TimeWalkViewer.push_back(hTimeSpread);
//	}
//
//	if (clusters.size() == 1 && clusters_timeCorr.size() == 1) {
//		auto seed = clusters[0]->getHit(0);
//		for (int i = 0; i < clusters[0]->getClusterSize(); i++) {
//			auto hit = clusters[0]->getHit(i);
//			hdTime->Fill(hit->getHitTime() - seed->getHitTime());
//		}
//		auto seed_timeCorr = clusters_timeCorr[0]->getHit(0);
//		for (int i = 0; i < clusters_timeCorr[0]->getClusterSize(); i++) {
//			auto hit = clusters_timeCorr[0]->getHit(i);
//			hdTime_corr->Fill(hit->getHitTime() - seed_timeCorr->getHitTime());
//		}
//	}
//	if (clusters.size() == 1) {
//		hClusterEnergyVsTheta->Fill(clusters[0]->getCentroid().CosTheta(), clusters[0]->getClusterEnergy());
//		for (int i = 0; i < clusters[0]->getClusterSize(); i++) {
//			auto hit = clusters[0]->getHit(i);
//			cout << hit->getHitEnergy() << " " << hit->getHitTime() << " " << hit->getHitIX() << " " << hit->getHitIY() << endl;
//		}
//		cout << clusters[0]->getCentroid().CosTheta() << " " << clusters[0]->getClusterEnergy() << endl;
//		cout << clusters[0]->getCentroid().X() << " " << clusters[0]->getCentroid().Y() << " " << clusters[0]->getCentroid().Z() << endl;
//	}
//	if (clusters_timeCorr.size() == 1) {
//		hClusterEnergyVsTheta_timeCorr->Fill(clusters_timeCorr[0]->getCentroid().CosTheta(), clusters_timeCorr[0]->getClusterEnergy());
//		for (int i = 0; i < clusters_timeCorr[0]->getClusterSize(); i++) {
//			auto hit = clusters_timeCorr[0]->getHit(i);
//			cout << hit->getHitEnergy() << " " << hit->getHitTime() << " " << hit->getHitIX() << " " << hit->getHitIY() << endl;
//		}
//		cout << clusters_timeCorr[0]->getCentroid().X() << " " << clusters_timeCorr[0]->getCentroid().Y() << " " << clusters_timeCorr[0]->getCentroid().Z() << endl << endl;
//	}
	hTest->Fill(clusters.size());

	hTest->Fill(clusters.size() + 10);

//	for (auto hit : hits)
//		cout << hit->m_channel.component << endl;

//	if (clusters.size() == 1 && clusters_timeCorr.size() == 1) {
//		cout << "Id " << clusters[0]->getClusterId() << " " << clusters_timeCorr[0]->getClusterId() << endl;
//		cout << "Size " << clusters[0]->getClusterSize() << " " << clusters_timeCorr[0]->getClusterSize() << endl;
//		cout << "Energy " << clusters[0]->getClusterEnergy() << " " << clusters_timeCorr[0]->getClusterEnergy() << endl;
//		cout << "Time " << clusters[0]->getClusterTime() << " " << clusters_timeCorr[0]->getClusterTime() << endl;
//		cout << "X " << clusters[0]->getCentroid().X() << " " << clusters_timeCorr[0]->getCentroid().X() << endl;
//		cout << "Y " << clusters[0]->getCentroid().Y() << " " << clusters_timeCorr[0]->getCentroid().Y() << endl;
//		cout << "Y " << clusters[0]->getCentroid().Z() << " " << clusters_timeCorr[0]->getCentroid().Z() << endl << endl;
//	}

//	if (clusters.size() == 1) {
//		auto seed = clusters[0]->getHit(0);
//		for (int i = 0; i < clusters[0]->getClusterSize(); i++) {
//			auto hit = clusters[0]->getHit(i);
//			CorrectionCurve[hit->m_channel.component]->Fill(hit->getHitEnergy(), hit->getHitTime() - seed->getHitTime());
//		}
//	}

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
