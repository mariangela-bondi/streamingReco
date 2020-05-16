
#ifndef _HallDCal_cosmicsProcessor_h_
#define _HallDCal_cosmicsProcessor_h_

#include <JANA/JEventProcessor.h>

class TH1D;
class JGlobalRootLock;
class HallDCal_cosmicsProcessor : public JEventProcessor {


    
public:

    HallDCal_cosmicsProcessor();
    virtual ~HallDCal_cosmicsProcessor() = default;

    void Init() override;
    void Process(const std::shared_ptr<const JEvent>& event) override;
    void Finish() override;

    TH1D *hQ[9];

    std::shared_ptr<JGlobalRootLock> m_root_lock;
};


#endif // _HallDCal_cosmicsProcessor_h_

