
#ifndef _TriggerDecision_HallDCal_beam_factory_h_
#define _TriggerDecision_HallDCal_beam_factory_h_

#include <JANA/JFactoryT.h>
#include <JANA/JEvent.h>
#include <Trigger/TriggerDecision.h>


class TriggerDecision_HallDCal_beam_factory : public JFactoryT<TriggerDecision> {

public:

    TriggerDecision_HallDCal_beam_factory();
    virtual ~TriggerDecision_HallDCal_beam_factory() = default;

    void Init() override;
    void Process(const std::shared_ptr<const JEvent>& event) override;

    bool ENABLED;
    int MIN_BLOCKS;
    int MIN_HODO_HITS;
};


#endif // _TriggerDecision_HallDCal_beam_factory_h_

