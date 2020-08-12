
#include <JANA/JApplication.h>
#include <JANA/JFactoryGenerator.h>
#include <JANA/JLogger.h>

#include <Trigger/TriggerDecision.h>
#include "TriggerMetadataProcessor.h"

//----=-----=----=----=----=-----=----=----=----=-----=----=----=
// Make this a plugin
extern "C" {
void InitPlugin(JApplication* app) {

    InitJANAPlugin(app);

    LOG << "Loading TriggerMetadata" << LOG_END;
    app->Add(new TriggerMetadataProcessor);
}
}
//----=-----=----=----=----=-----=----=----=----=-----=----=----=


//--------------------------------------------------------
// TriggerMetadataProcessor  (Constructor)
//--------------------------------------------------------
TriggerMetadataProcessor::TriggerMetadataProcessor() {
	SetTypeName(NAME_OF_THIS); // Provide JANA with this class's name
}

//--------------------------------------------------------
// Init
//--------------------------------------------------------
void TriggerMetadataProcessor::Init() {
	LOG << "TriggerMetadataProcessor::Init" << LOG_END;
    
	m_root_lock = japp->GetService<JGlobalRootLock>();

	// Do not open ROOT file here. Default filename is based on run number
	// so wait until Process method when we have access to run number.
}

//--------------------------------------------------------
// Process
//--------------------------------------------------------
void TriggerMetadataProcessor::Process(const std::shared_ptr<const JEvent> &event) {

	// Open a new metadata file if the run number changes
	auto runnumber = event->GetRunNumber();
	if( runnumber != last_runnumber){

		// Lock ROOT access
		m_root_lock->acquire_write_lock();
		
		// If file is already open for a different run number then close it.
		if( rootfile != nullptr ){
			LOG << "Closing " << rootfile->GetName() << LOG_END;
			rootfile->Write();
			delete rootfile;
		}
		
		// Determine ROOT filename
		std::string METADATAFILENAME = "AUTO"; // special name meaning to automatically form filename from runnumber
		GetApplication()->SetDefaultParameter("METADATAFILENAME", METADATAFILENAME, "File name for ROOT file to write the JANA trigger metadata into. Do not set to have filename auto-generated based on run number.");
		if( METADATAFILENAME == "AUTO" ){
			char str[256];
			sprintf(str, "JANA_Triggers_%06d.root", runnumber);
			METADATAFILENAME = str;
		}

		// Open ROOT file
		rootfile = new TFile(METADATAFILENAME.c_str(), "recreate");

		// Add trees
		trig_tree = new TTree("trig", "JANA Trigger metadata");
		trig_tree->Branch("event",    &trigger_eventnumber, "event/l");
		trig_tree->Branch("id",       &triggerID,           "id/i");
		trig_tree->Branch("decision", &trigger_decision,    "decision/i");

		trig_descriptions_tree = new TTree("trig_descriptions", "JANA Trigger Descriptions");
		trig_descriptions_tree->Branch("id",          &triggerID,                 "id/i");
		trig_descriptions_tree->Branch("description", (void*)trigger_description, "description/C", 256);

		// Release ROOT lock
		m_root_lock->release_lock();

		last_runnumber = runnumber;
	}

	// Get all TriggerDecision objects from all plugins, libraries, etc ...
	std::vector<const TriggerDecision*> triggers;
	event->GetAll(triggers);

	// Lock ROOT access
	m_root_lock->acquire_write_lock();

	// Loop over trigger objects adding them to tree
	for (auto trigger : triggers){

		// Here the trigger information is stored to a metadata file.
		// This will allow one to correlate each trigger's decision
		// with an event (i.e. "tag" it). Eventually, this type of
		// metadata will be passed to Tridas for inclusion in the 
		// output stream directly.
		//
		// A trigger ID is used to identify each trigger inserted into
		// the file. The ID is generated here based on the description
		// returned from the TriggerDecision object. This avoids storing
		// the description itself with every event which would be
		// inefficient. In order to make it easy to identify the trigger
		// within the file, a second tree is created that holds the
		// actual description and the ID.

		// Add trigger description to tree if needed
		auto description = trigger->GetDescription();
		if( triggerIDmap.count( description ) == 0 ){
			triggerIDmap[ description ] = triggerIDmap.size()+1;
			triggerID = triggerIDmap[ description ];
			sprintf(trigger_description, "%s", description.c_str());
			trig_descriptions_tree->Fill();
		}

		// Add trigger decision to tree
		trigger_eventnumber = event->GetEventNumber();
		triggerID = triggerIDmap[ description ];
		trigger_decision = trigger->GetDecision();
		trig_tree->Fill();
	}

	// Release ROOT lock
	m_root_lock->release_lock();
}

//--------------------------------------------------------
// Finish
//--------------------------------------------------------
void TriggerMetadataProcessor::Finish() {

	LOG << "TriggerMetadataProcessor::Finish" << LOG_END;

	// Flush ROOT file with metadata and close it
	if( rootfile != nullptr ){
		rootfile->Write();
		delete rootfile;
		rootfile = nullptr;  // am I paranoid?
	}
}

