//
//    File: FTCalHitSummary.cc
// Created: Wed Jan  8 12:49:28 CET 2020
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

#include "FTCalHitSummary.h"


//---------------------------------
// FTCalHitSummary    (Constructor)
//---------------------------------
FTCalHitSummary::FTCalHitSummary(){
	hHITS=0;
}

//---------------------------------
// ~FTCalHitSummary    (Destructor)
//---------------------------------
FTCalHitSummary::~FTCalHitSummary()
{

}

TCanvas* FTCalHitSummary::Draw(int id) const{


	if (m_canvas==0){
		if (id<0){
			m_canvas=new TCanvas();
		}
		else{
			m_canvas=new TCanvas(Form("c_%i",id),100,100,id);
		}
	}
	m_canvas->cd();

	if (hHITS!=0) delete hHITS;
	hHITS=new TH2D(Form("hHITS"),Form("hHITS"),23,-0.5,22.5,23,-0.5,22.5);
	this->toHisto(hHITS);
	hHITS->Draw("colz");
	return m_canvas;
}


void FTCalHitSummary::toHisto(TH2D *h)const{
	if (h==0){
		cerr<<"fa250Mode1CalibPedSubHit::toHisto, h pointer is null. Do nothing"<<std::endl;
	}
	h->Reset();
	for (auto hit : hits){
		h->Fill(hit->getHitIX(),hit->getHitIY(),hit->getHitEnergy());
	}
	return;
}
