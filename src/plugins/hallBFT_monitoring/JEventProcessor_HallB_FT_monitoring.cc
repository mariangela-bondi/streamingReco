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
	 hnHitsComponentFT = new TH1D(" hnHitsComponentFT", " hnHitsComponentFT", 400, 0, 400);

	 m_root_lock->release_lock();

}

//------------------
// Process
//------------------
void JEventProcessor_HallB_FT_monitoring::Process(const std::shared_ptr<const JEvent>& aEvent) {


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
	for (auto calhit : calhits) {

    hnHitsComponentFT->Fill(calhit->m_channel.component);

	}



	 hnClusters->Fill(calclusters.size());
	 hnHitsFT->Fill(calhits.size());


	m_root_lock->release_lock();
	//unlock

}

//------------------
// Finish
//------------------
void JEventProcessor_HallB_FT_monitoring::Finish(void) {
	// This is called when at the end of event processing
}
