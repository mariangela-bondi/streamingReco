//
//    File: HallB_FT_monitoring/JEventProcessor_HallB_FT_monitoring.cc
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

#include "JEventProcessor_HallB_FT_monitoring.h"

#include "FT/FTCalHit.h"
#include "FT/FTHodoHit.h"
#include "FT/FTCalCluster.h"

#include "JANA/Services/JGlobalRootLock.h"
#include "JANA/JApplication.h"

#include <TDirectory.h>
#include <TH2.h>
#include <TH1.h>
#include <TProfile2D.h>
#include <TStyle.h>
#include "TROOT.h"

/*Here goes the histograms*/
static TH1D *hTest = 0;
static TH1D *hnClusters = 0;
static TH1D *hnHitsFT = 0;
static TH1D *hnHitsComponentFT=0;   // histo number of counts for each FT components
//static TH1D *hFTCrystalsEnergy[nTOT_FT] = { 0 };
static TH1D *hFTCrystalsEnergy_248component=0;
static TH1D *hFTCrystalsEnergy_257component=0;
static TH1D *hFTCrystalsEnergy_472component=0;
static TH1D *hFTCrystalsEnergy_473component=0;
static TH2D *hnHitsXYFT=0;

static TH1D *hCluster_TotEnergy_Trigger=0;
static TH1D *hCluster_EnergySeed_Trigger=0;
static TH1D *hnHitsInCluster_Trigger=0;
static TH1D *hnClusters_Trigger=0;
static TH2D *hClusXY_Trigger=0;

static TH1D *hClusM_Trigger=0;
static TH2D *hClusAngle_M_Trigger=0;



//---------------------------------
// JEventProcessor_HallB_FT_monitoring    (Constructor)
//---------------------------------
JEventProcessor_HallB_FT_monitoring::JEventProcessor_HallB_FT_monitoring() {

}

//---------------------------------
// ~JEventProcessor_HallB_FT_monitoring    (Destructor)
//---------------------------------
JEventProcessor_HallB_FT_monitoring::~JEventProcessor_HallB_FT_monitoring() {

}

//------------------
// Init
//------------------
void JEventProcessor_HallB_FT_monitoring::Init(void) {
	// This is called once at program startup.
	m_root_lock = japp->GetService<JGlobalRootLock>();

	m_root_lock->acquire_write_lock();
	if (hTest != NULL) {
		m_root_lock->release_lock();
		return;
	}

	gROOT->cd();
	TDirectory *main = gDirectory;
	gDirectory->mkdir("HallB_FT_monitoring")->cd();

	 hnClusters = new TH1D(" hnClusters", " hnClusters", 100, 0, 10);
	 hnHitsFT = new TH1D(" hnHitsFT", " hnHitsFT", 400, 0, 400);
	 hnHitsComponentFT = new TH1D(" hnHitsComponentFT", " hnHitsComponentFT", 500, 0, 500);
	 hnHitsXYFT = new TH2D("hnHitsXYFT","hnHitsXYFT",200,-200,200,200,-200,200);
	 hFTCrystalsEnergy_248component= new TH1D("hFTCrystalsEnergy_248component", "hFTCrystalsEnergy_248component", 300, 0, 2000.);
	 hFTCrystalsEnergy_257component= new TH1D("hFTCrystalsEnergy_257component", "hFTCrystalsEnergy_257component", 300, 0, 2000.);
     hFTCrystalsEnergy_472component= new TH1D("hFTCrystalsEnergy_472component", "hFTCrystalsEnergy_472component", 300, 0, 2000.);
	 hFTCrystalsEnergy_473component= new TH1D("hFTCrystalsEnergy_473component", "hFTCrystalsEnergy_473component", 300, 0, 2000.);


	 hCluster_TotEnergy_Trigger = new TH1D("hCluster_TotEnergy_Trigger", "hCluster_TotEnergy_Trigger", 300, 0, 6000.);
	 hCluster_EnergySeed_Trigger = new TH1D("hCluster_EnergySeed_Trigger","hCluster_EnergySeed_Trigger", 300,0, 6000.);
	 hnHitsInCluster_Trigger = new TH1D("hnHitsInCluster_Trigger", "hnHitsInCluster_Trigger", 400, 0, 400);
	 hnClusters_Trigger = new TH1D("hnClusters_Trigger", "hnClusters_Trigger", 100, 0, 100);
	 hClusM_Trigger=new TH1D("hClusM_Trigger","hClusM_Trigger",300,0,300);
	 hClusXY_Trigger=new TH2D("hClusXY_Trigger","hClusXY_Trigger",200,-200,200,200,-200,200);

	 hClusAngle_M_Trigger=new TH2D("hClusAngle_M_Trigger","hClusAngle_M_Trigger", 200, -3.14,3.14, 300, 0, 300);


	 m_root_lock->release_lock();

}

//------------------
// Process
//------------------
void JEventProcessor_HallB_FT_monitoring::Process(const std::shared_ptr<const JEvent>& aEvent) {

	// conditions to be a good cluster
	double minSeed = 100;
	double minEnergy = 300;
	double minSize = 3;

	int nCluster_th = 1;  // number of clusters required to do trigger


	auto calhits = aEvent->Get<FTCalHit>();
	auto calclusters = aEvent->Get<FTCalCluster>();


	bool isSet = false;


	/*
	 * for (auto triggerDecision : triggerDecisions) {
		if (triggerDecision->GetDecision()) {
			isSet = true;
			break;
		}
	}*/
	//lock
	m_root_lock->acquire_write_lock();
	for (auto cluster : calclusters) {

	}
	 hnClusters->Fill(calclusters.size());
	for (auto calhit : calhits) {

    hnHitsComponentFT->Fill(calhit->m_channel.component);
    if(calhit->m_channel.component==248) hFTCrystalsEnergy_248component->Fill(calhit->getHitEnergy());
    if(calhit->m_channel.component==257) hFTCrystalsEnergy_257component->Fill(calhit->getHitEnergy());
    if(calhit->m_channel.component==472) hFTCrystalsEnergy_472component->Fill(calhit->getHitEnergy());
    if(calhit->m_channel.component==473) hFTCrystalsEnergy_473component->Fill(calhit->getHitEnergy());

    hnHitsXYFT->Fill(calhit->getHitIX(), calhit->getHitIY());
	}
	 hnHitsFT->Fill(calhits.size());




	 //	 std::cout<<"histo monitoring"<<std::endl;


	 // monitoring histogram Trigger Decision.
	 auto calclus = aEvent->Get<FTCalCluster>();
	 int nCluster=0;
	 for(int ii=0; ii<calclus.size();ii++){
		 auto clus = calclus[ii];
			if(clus->getClusterSize()>minSize && clus->getClusterSeedEnergy() >minSeed && clus->getClusterEnergy()>minEnergy){
				nCluster++;
			         }
		}
	 if (nCluster>=nCluster_th){

		    hnClusters_Trigger->Fill(nCluster);
		    for(int ii=0; ii<calclus.size();ii++){
		    	auto clus = calclus[ii];
		    hCluster_TotEnergy_Trigger->Fill(clus->getClusterEnergy());
		    hCluster_EnergySeed_Trigger->Fill(clus->getClusterSeedEnergy());
		    }

		  //mass pi0
		auto ftCalClusters = aEvent->Get<FTCalCluster>();
        for (int ii=0;ii<ftCalClusters.size();ii++) {
				auto cluster = ftCalClusters[ii];
				hClusXY_Trigger->Fill(cluster->getX(),cluster->getY());
				for (int jj=(ii+1);jj<ftCalClusters.size();jj++){
					auto cluster2 = ftCalClusters[jj];
					auto z = cos(cluster->getCentroid().Angle(cluster2->getCentroid()));
					auto M = sqrt(2*cluster->getClusterEnergy()*cluster2->getClusterEnergy()*(1-z))*1000;
					auto phi = cluster->getPhi();
				//	std::cout<<z<<" "<<M<<std::endl;
					hClusM_Trigger->Fill(M);
					hClusAngle_M_Trigger->Fill(M,cluster->getCentroid().Angle(cluster2->getCentroid()));
				}
			}
	 }








	m_root_lock->release_lock();
	//unlock

}

//------------------
// Finish
//------------------
void JEventProcessor_HallB_FT_monitoring::Finish(void) {
	// This is called when at the end of event processing
}
