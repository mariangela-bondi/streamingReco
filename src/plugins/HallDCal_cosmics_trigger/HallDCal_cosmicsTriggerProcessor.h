
#ifndef _HallDCal_cosmicsTriggerProcessor_h_
#define _HallDCal_cosmicsTriggerProcessor_h_

#include <JANA/JEventProcessor.h>

class HallDCal_cosmicsTriggerProcessor : public JEventProcessor {

public:

    HallDCal_cosmicsTriggerProcessor();
    virtual ~HallDCal_cosmicsTriggerProcessor() = default;

    void Init() override;
    void Process(const std::shared_ptr<const JEvent>& event) override;
    void Finish() override;
};


#endif // _HallDCal_cosmicsTriggerProcessor_h_

