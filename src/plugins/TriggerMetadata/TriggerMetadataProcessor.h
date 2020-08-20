
#ifndef _TriggerMetadataProcessor_h_
#define _TriggerMetadataProcessor_h_

#include <JANA/JEventProcessor.h>
#include <JANA/Services/JGlobalRootLock.h>


#include <TFile.h>
#include <TTree.h>

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
		int  triggerID;
		char trigger_description[256];
		int  trigger_decision;

		std::shared_ptr<JGlobalRootLock> m_root_lock;
};


#endif // _TriggerMetadataProcessor_h_

