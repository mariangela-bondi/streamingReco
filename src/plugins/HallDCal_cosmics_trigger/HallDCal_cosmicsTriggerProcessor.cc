
#include <JANA/JLogger.h>
#include <JANA/JApplication.h>
#include <JANA/JFactoryGenerator.h>

#include "HallDCalTrack_Factory.h"
#include "HallDCal_cosmicsTriggerProcessor.h"
#include "DAQ/TridasEvent.h"



extern "C" {
void InitPlugin(JApplication* app) {

    // This code is executed when the plugin is attached.
    // It should always call InitJANAPlugin(app) first, and then do one or more of:
    //   - Read configuration parameters
    //   - Register JFactoryGenerators
    //   - Register JEventProcessors
    //   - Register JEventSourceGenerators (or JEventSources directly)
    //   - Register JServices

    InitJANAPlugin(app);

    LOG << "Loading HallDCal_cosmics_trigger" << LOG_END;
    app->Add( new HallDCal_cosmicsTriggerProcessor() );
    app->Add( new JFactoryGeneratorT<HallDCalTrack_Factory>() );
}
}

//-----------------------------------------------
// HallDCal_cosmicsTriggerProcessor (constructor)
//-----------------------------------------------
HallDCal_cosmicsTriggerProcessor::HallDCal_cosmicsTriggerProcessor() {
    SetTypeName(NAME_OF_THIS); // Provide JANA with this class's name
}

//-----------------------------------------------
// Init
//-----------------------------------------------
void HallDCal_cosmicsTriggerProcessor::Init() {
	LOG << "HallDCal_cosmicsTriggerProcessor::Init" << LOG_END;
}

//-----------------------------------------------
// Process
//-----------------------------------------------
void HallDCal_cosmicsTriggerProcessor::Process(const std::shared_ptr<const JEvent> &event) {

	// Get track objects from factory
	auto trks = event->Get<HallDCalTrack>();
	
	try{	
		// The TridasEvent object is created in the JEventSource_PTFile
		// class (or the JEventSource used for online streaming).
		// It has one mutable member called "should_keep" that we can set
		// true here if the event should be kept.
		auto tridasEvent = event->GetSingle<TridasEvent>();
		tridasEvent->should_keep = trks.size()>0; // keep anything with a track
		
	}catch(JException &e){
		// Ignore exceptions for now.
	}   
}

//-----------------------------------------------
// Finish
//-----------------------------------------------
void HallDCal_cosmicsTriggerProcessor::Finish() {
	// Close any resources
	LOG << "HallDCal_cosmicsTriggerProcessor::Finish" << LOG_END;
}

