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
static TH1D *hnClusters = 0; //Number of cluster found
static TH1D *hnHitsFT = 0; //Number of hits founf
static TH1D *hnHitsComponentFT=0;   // histo number of counts for each FT components

static TH1D *hAllHitsEnergy=0;

static TH2D *hnHitsXYFT=0; //"Ring" of FTCal, number of Hits in every scintillator

static TH1D *hCluster_TotEnergy=0; //Energy of cluster of event that verify the trigger
static TH1D *hCluster_EnergySeed=0; //Energy of seed cluster of event that verify the trigger

static TH1D *hTotEnergy=0; //Total energy summing over clusters in this event


static TH1D *hnHitsInCluster_Trigger=0; //Number of hits in cluster of event that verify the trigger
static TH1D *hnClusters_Trigger=0; //Number of cluster of event that verify the trigger
static TH2D *hClusXY_Trigger=0; //Position of clusters of event that verify the trigger

static TH1D *hClusM_Trigger=0; //pi0 mass
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

  hnClusters = new TH1D(" hnClusters", " hnClusters", 21, -0.5, 20);
  hnHitsFT = new TH1D(" hnHitsFT", " hnHitsFT", 400, 0, 400);
  hnHitsComponentFT = new TH1D(" hnHitsComponentFT", " hnHitsComponentFT", 500, 0, 500);
  hnHitsComponentFT->SetFillColor(4);
  hnHitsXYFT = new TH2D("hnHitsXYFT","hnHitsXYFT",24,-23.5,.5,24,-.5,23.5);
 
  hAllHitsEnergy=new TH1D("hAllHitsEnergy","hAllHitsEnergy",10000,0,10000);

  hTotEnergy = new TH1D("hTotEnergy", "hTotEnergy", 300, 0, 11000.);
  hCluster_TotEnergy = new TH1D("hCluster_TotEnergy", "hCluster_TotEnergy", 300, 0, 11000.);
  hCluster_EnergySeed = new TH1D("hCluster_EnergySeed","hCluster_EnergySeed", 300,0, 11000.);

  hnHitsInCluster_Trigger = new TH1D("hnHitsInCluster_Trigger", "hnHitsInCluster_Trigger", 400, 0, 400);
  hnClusters_Trigger = new TH1D("hnClusters_Trigger", "hnClusters_Trigger", 100, 0, 100);
 
 hClusM_Trigger=new TH1D("hClusM_Trigger","hClusM_Trigger",500,0,500);
  hClusXY_Trigger=new TH2D("hClusXY_Trigger","hClusXY_Trigger",200,-200,200,200,-200,200);
  hClusAngle_M_Trigger=new TH2D("hClusAngle_M_Trigger","hClusAngle_M_Trigger", 500,0,500,100,0.9,1);


  m_root_lock->release_lock();

}

//------------------
// Process
//------------------
void JEventProcessor_HallB_FT_monitoring::Process(const std::shared_ptr<const JEvent>& aEvent) {

  // conditions to be a good cluster; //Condition on clusters are implemented in FTCalCluster.cc, if there are not yet an external file reading.
  //double minSeed = 10;
  //double minEnergy = 30;
  //double minSize = 2;

  //////////////////COPY TRIGGER CONDITION FOR MONITORING HERE
  //condition on trigger   
  int nCluster_th = 1;  // number of clusters required to do trigger 
  //Searching pi0
  int nCluster_pi0 = 3;
  

  auto hits = aEvent->Get<FTCalHit>(); //vector degli hits dell'evento
  auto clusters = aEvent->Get<FTCalCluster>(); //vector dei clusters dell'evento

  bool isSet = false;

  //lock
  m_root_lock->acquire_write_lock();

  // for (auto cluster : calclusters) {}

  //Number of clusters
  hnClusters->Fill(clusters.size());
 
  //Number of hits 
  hnHitsFT->Fill(hits.size());

  for (auto hit : hits) {
    //Number of hit vs crystal
    hnHitsComponentFT->Fill(hit->m_channel.component);
    
    //Energy of all hits
    hAllHitsEnergy->Fill(hit->getHitEnergy());
   
    //2D histo of FTCal
    hnHitsXYFT->Fill(-hit->getHitIX(), hit->getHitIY());
  }
 
 

  // monitoring histogram Trigger Decision.
  int nCluster=0;
  double totE=0;
  for(auto cluster : clusters){ 
    nCluster++; 
    totE+=cluster->getClusterEnergy();
    hCluster_TotEnergy->Fill(cluster->getClusterEnergy());
    hCluster_EnergySeed->Fill(cluster->getClusterSeedEnergy());
  }
  hTotEnergy->Fill(totE);
  //Plot quantities related to trigger decision
  if (nCluster>=nCluster_th){
    hnClusters_Trigger->Fill(nCluster);
    for(auto cluster : clusters){
      hClusXY_Trigger->Fill(cluster->getX(),cluster->getY());
      hnHitsInCluster_Trigger->Fill(cluster->getClusterSize());
    }
  }
   
 
  //plot the invariant mass of ALL clusters pairs
  if (clusters.size()>1){
  for(int ii=0; ii<clusters.size(); ii++){
    auto cluster1 = clusters[ii];
    if (cluster1->getClusterEnergy()<1.) continue;
    hClusXY_Trigger->Fill(cluster1->getX(),cluster1->getY());
    for (int jj=(ii+1);jj<clusters.size();jj++){
      auto cluster2 = clusters[jj];
      if (cluster2->getClusterEnergy()<1.) continue;
      auto z = cos(cluster1->getCentroid().Angle(cluster2->getCentroid()));
      auto M = sqrt(2*cluster1->getClusterEnergy()*cluster2->getClusterEnergy()*(1-z))*1000;
      hClusM_Trigger->Fill(M);
      hClusAngle_M_Trigger->Fill(M,z);   
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
