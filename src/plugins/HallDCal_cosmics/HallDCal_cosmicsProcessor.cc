
#include "HallD/HallDCalHit.h"
#include "HallDCal_cosmicsProcessor.h"
#include <JANA/JLogger.h>
#include "JANA/Services/JGlobalRootLock.h"
#include "JANA/JApplication.h"

#include "TFile.h"
#include "TH1D.h"
#include "TFolder.h"
#include "TROOT.h"

HallDCal_cosmicsProcessor::HallDCal_cosmicsProcessor() {
    SetTypeName(NAME_OF_THIS); // Provide JANA with this class's name
}

void HallDCal_cosmicsProcessor::Init() {
    LOG << "HallDCal_cosmicsProcessor::Init" << LOG_END;
    // Open TFiles, set up TTree branches, etc


	m_root_lock = japp->GetService<JGlobalRootLock>();

	m_root_lock->acquire_write_lock();
	if (hQ[0] != NULL) {
		m_root_lock->release_lock();
		return;
	}

	gROOT->cd();
	TDirectory *main = gDirectory;
	gDirectory->mkdir("HallDCal_cosmics")->cd();

	for (int ii=0;ii<9;ii++){
		hQ[ii]=new TH1D(Form("hQ_%i",ii),Form("hQ_%i",ii),100,0,10E3);
	}


	gDirectory->cd();
	m_root_lock->release_lock();

}

void HallDCal_cosmicsProcessor::Process(const std::shared_ptr<const JEvent> &event) {
    LOG << "HallDCal_cosmicsProcessor::Process, Event #" << event->GetEventNumber() << LOG_END;
    
    /// Do everything we can in parallel
    /// Warning: We are only allowed to use local variables and `event` here
    //auto hits = event->Get<Hit>();

    auto hits = event->Get<HallDCalHit>();

    /// Lock mutex
    m_root_lock->acquire_write_lock();

    for (auto hit : hits){
    	int iX=hit->m_channel.iX;
    	int iY=hit->m_channel.iY;
    	int id=iX*3+iY;
    	double Q=hit->getHitEnergy();

    	hQ[id]->Fill(Q);

    }


    m_root_lock->release_lock();
}

void HallDCal_cosmicsProcessor::Finish() {
    // Close any resources
    LOG << "HallDCal_cosmicsProcessor::Finish" << LOG_END;


	auto app = japp;
	std::string outFileName;
	TFile *fout;
	if (app->GetJParameterManager()->Exists("HallDCal_cosmics:output_file") == true) {
		gROOT->cd();
		TDirectory *main = gDirectory;

		app->GetJParameterManager()->GetParameter("HallDCal_cosmics:output_file", outFileName);
		std::cout << "JEventProcessor_HallDCal_cosmis::Finish " << this << " " << outFileName << std::endl;
		fout = new TFile(outFileName.c_str(), "recreate");

		main->cd("HallDCal_cosmics");
		TIter next(gDirectory->GetList());
		TObject* object = 0;
		fout->cd();


		while (object =  next()) {

			if (object->InheritsFrom(TH1::Class())) {

				fout->cd();
				object->Write();

				std::cout << "JEventProcessor_HallDCal_cosmis::wrote " << object->GetName() << std::endl;
			}

		}


		fout->Write();
		fout->Close();
	}




}

