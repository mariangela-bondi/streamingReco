
#include <JANA/JLogger.h>
#include <JANA/JApplication.h>
#include <JANA/JFactoryGenerator.h>

#include "HallDCalTrack_Factory.h"
#include "TriggerDecision_HallDCal_cosmics_factory.h"
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
    app->Add( new JFactoryGeneratorT<TriggerDecision_HallDCal_cosmics_factory>() );
    app->Add( new JFactoryGeneratorT<HallDCalTrack_Factory>() );
}
}

//-----------------------------------------------
// TriggerDecision_HallDCal_cosmics_factory (constructor)
//-----------------------------------------------
TriggerDecision_HallDCal_cosmics_factory::TriggerDecision_HallDCal_cosmics_factory() {
	mTag="HallDCal_cosmics";
}

//-----------------------------------------------
// Init
//-----------------------------------------------
void TriggerDecision_HallDCal_cosmics_factory::Init() {

	ENABLED    = true;
	MIN_TRACKS = 1;
	MAX_TRACKS = 1000;

	mApp->SetDefaultParameter("TRIGGER:HallDCal_cosmics:ENABLED", ENABLED, "Set to 0 to disable the HallDCal_cosmics trigger completely (no TriggerDecision objects will be produced).");
	mApp->SetDefaultParameter("TRIGGER:HallDCal_cosmics:MIN_TRACKS", MIN_TRACKS, "Minimum number of HallDCalTrack objects to trigger.");
	mApp->SetDefaultParameter("TRIGGER:HallDCal_cosmics:MAX_TRACKS", MAX_TRACKS, "Maximum number of HallDCalTrack objects to trigger.");
}

//-----------------------------------------------
// Process
//-----------------------------------------------
void TriggerDecision_HallDCal_cosmics_factory::Process(const std::shared_ptr<const JEvent> &event) {

	if( !ENABLED ) return; // allow user to disable this via JANA config. param.

	// Get track objects from factory
	auto trks = event->Get<HallDCalTrack>();
	int Ntrks = trks.size();

	bool decision = ((Ntrks>=MIN_TRACKS) && (Ntrks<=MAX_TRACKS));

	// Create TriggerDecision object to publish the decision
	// Argument is trigger description. It will end up in metadata file so keep it simple.
	// I think a good convention here is to just give it the tag of the factory.
	auto mTriggerDecision = new TriggerDecision( mTag ); 
	mTriggerDecision->SetDecision( decision );
	mTriggerDecision->SetID(0x01); // this will show up in 16 high order bit in TriggeredEvent::plugin_nseeds[] (lower 16 will be 0 or 1 depending on whether trigger fired)
	mData.push_back(mTriggerDecision);	
}



