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

//Selezione eventi "basica"
const int firstEvent = 0;
const int lastEvent = 20;

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
	//auto clusters_ECorr = aEvent->Get < FTCalCluster > ("EneCorr"); //vector dei clusters dell'evento con correzione sull'energia degli hit

	//Numero dell'evento
	auto eventNumber = aEvent->GetEventNumber();

	//lock
	m_root_lock->acquire_write_lock();

	if (eventNumber >= firstEvent && eventNumber <= lastEvent) {
		TH2D *hHitsEnergy = new TH2D(Form("hHitsEnergy%d", eventNumber), Form("hHitsEnergy%d", eventNumber), 25, 0, 25, 25, 0, 25);
		TH2D *hHitsTime = new TH2D(Form("hHitsTime%d", eventNumber), Form("hHitsTime%d", eventNumber), 25, 0, 25, 25, 0, 25);
		TH2D *hClusterHitsEnergy = new TH2D(Form("hClusterHitsEnergy%d", eventNumber), Form("hClusterHitsEnergy%d", eventNumber), 25, 0, 25, 25, 0, 25);
		TH2D *hClusterHitsTime = new TH2D(Form("hClusterHitsTime%d", eventNumber), Form("hClusterHitsTime%d", eventNumber), 25, 0, 25, 25, 0, 25);

//		TH2D *hHitsEnergy_timeCorr = new TH2D(Form("hHitsEnergy_timeCorr%d", eventNumber), Form("hHitsEnergy_timeCorr%d", eventNumber), 25, 0, 25, 25, 0, 25);
//		TH2D *hHitsTime_timeCorr = new TH2D(Form("hHitsTime_timeCorr%d", eventNumber), Form("hHitsTime_timeCorr%d", eventNumber), 25, 0, 25, 25, 0, 25);
		TH2D *hClusterHitsEnergy_timeCorr = new TH2D(Form("hClusterHitsEnergy_timeCorr%d", eventNumber), Form("hClusterHitsEnergy_timeCorr%d", eventNumber), 25, 0, 25, 25, 0, 25);
		TH2D *hClusterHitsTime_timeCorr = new TH2D(Form("hClusterHitsTime_timeCorr%d", eventNumber), Form("hClusterHitsTime_timeCorr%d", eventNumber), 25, 0, 25, 25, 0, 25);

		for (auto hit : hits) {
			hHitsEnergy->Fill(hit->getHitIX(), hit->getHitIY(), hit->getHitEnergy());
			if (hit->getHitTime() != 0) {
				hHitsTime->Fill(hit->getHitIX(), hit->getHitIY(), hit->getHitTime());
			} else {
				hHitsTime->Fill(hit->getHitIX(), hit->getHitIY(), 1);
			}
		}

//		for (auto hit : hits_timeCorr) {
//			hHitsEnergy_timeCorr->Fill(hit->getHitIX(), hit->getHitIY(), hit->getHitEnergy());
//			if (hit->getHitTime() != 0) {
//				hHitsTime_timeCorr->Fill(hit->getHitIX(), hit->getHitIY(), hit->getHitTime());
//			} else {
//				hHitsTime_timeCorr->Fill(hit->getHitIX(), hit->getHitIY(), 1);
//			}
//		}

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

		for (auto cluster : clusters_timeCorr) {
			for (int i = 0; i < cluster->getClusterSize(); i++) {
				auto hit = cluster->getHit(i);
				hClusterHitsEnergy_timeCorr->Fill(hit->getHitIX(), hit->getHitIY(), hit->getHitEnergy());
				if (hit->getHitTime() != 0) {
					hClusterHitsTime_timeCorr->Fill(hit->getHitIX(), hit->getHitIY(), hit->getHitTime());
				} else {
					hClusterHitsTime_timeCorr->Fill(hit->getHitIX(), hit->getHitIY(), 1);
				}
			}
		}

		HitsEnergy.push_back(hHitsEnergy);
		HitsTime.push_back(hHitsTime);
		ClusterHitsEnergy.push_back(hClusterHitsEnergy);
		ClusterHitsTime.push_back(hClusterHitsTime);

//		HitsEnergy_timeCorr.push_back(hHitsEnergy_timeCorr);
//		HitsTime_timeCorr.push_back(hHitsTime_timeCorr);
		ClusterHitsEnergy_timeCorr.push_back(hClusterHitsEnergy_timeCorr);
		ClusterHitsTime_timeCorr.push_back(hClusterHitsTime_timeCorr);
	}

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
