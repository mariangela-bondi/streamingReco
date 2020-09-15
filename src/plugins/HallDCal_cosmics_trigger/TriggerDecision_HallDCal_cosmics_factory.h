
#ifndef _HallDCal_cosmicsTriggerProcessor_h_
#define _HallDCal_cosmicsTriggerProcessor_h_

#include <JANA/JFactoryT.h>
#include <JANA/JEvent.h>
#include <Trigger/TriggerDecision.h>


class TriggerDecision_HallDCal_cosmics_factory : public JFactoryT<TriggerDecision> {

public:

    TriggerDecision_HallDCal_cosmics_factory();
    virtual ~TriggerDecision_HallDCal_cosmics_factory() = default;

    void Init() override;
    void Process(const std::shared_ptr<const JEvent>& event) override;

    bool ENABLED;
    int MIN_TRACKS;
    int MAX_TRACKS;
};


#endif // _HallDCal_cosmicsTriggerProcessor_h_

