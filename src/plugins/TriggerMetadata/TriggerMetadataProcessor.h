
#ifndef _TriggerMetadataProcessor_h_
#define _TriggerMetadataProcessor_h_

#include <JANA/JEventProcessor.h>
#include <JANA/Services/JGlobalRootLock.h>


#include <TFile.h>
#include <TTree.h>
#include <TH2.h>

class TriggerMetadataProcessor : public JEventProcessor {

    
	public:

    		TriggerMetadataProcessor();
    		virtual ~TriggerMetadataProcessor() = default;

    		void Init() override;
		void OpenMetadataFile(uint64_t runnumber);
    		void Process(const std::shared_ptr<const JEvent>& event) override;
   		void Finish() override;

	protected:

    		// Used for metadata file
    		TFile *rootfile = nullptr;
    		TTree *trig_tree = nullptr;
    		TTree *trig_descriptions_tree = nullptr;
    		int32_t last_runnumber = 0;
    		std::map<std::string,int> triggerIDmap;

		// Used for tree branches
		uint64_t trigger_eventnumber;
		uint16_t  triggerID;
		char trigger_description[256];
		uint16_t  trigger_decision;

		// Analysis histograms
		TH1 *hTimeSlice = nullptr;
		TH2 *hTriggerID = nullptr;
		TH2 *hTriggerID_norm = nullptr;

		uint64_t min_time_slice = 0;
		uint64_t max_time_slice = 0;
		uint64_t num_time_slice = 0;
		uint64_t min_event = 0;
		uint64_t max_event = 0;
		uint64_t num_events = 0;

		std::shared_ptr<JGlobalRootLock> m_root_lock;
};


#endif // _TriggerMetadataProcessor_h_

