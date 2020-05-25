/*
 * FTCalCluster_factory_TimeCorr
 *
 *      Author: svallarino
 */

#ifndef SRC_LIBRARIES_FT_FTCALCluster_FACTORY_TIMECORR_H_
#define SRC_LIBRARIES_FT_FTCALCluster_FACTORY_TIMECORR_H_

#include "JANA/JFactoryT.h"
#include "FTCalCluster.h"

class FTCalCluster_factory_TimeCorr: public JFactoryT<FTCalCluster> {
public:
	FTCalCluster_factory_TimeCorr();
	virtual ~FTCalCluster_factory_TimeCorr();

	// Overloaded by user Factories
	virtual void Init();
	virtual void ChangeRun(const std::shared_ptr<const JEvent> &aEvent);
	virtual void Process(const std::shared_ptr<const JEvent> &aEvent);

	static bool compareHits(const FTCalHit* a, const FTCalHit* b);
};

#endif /* SRC_LIBRARIES_FT_FTCALCluster_FACTORY_H_ */
