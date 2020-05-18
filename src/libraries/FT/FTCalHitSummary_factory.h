/*
 * FTCalHitSummary_factory
 *
 *  Created on: Dec 23, 2019
 *      Author: celentan
 */

#ifndef SRC_LIBRARIES_FT_FTCalHitSummary_FACTORY_H_
#define SRC_LIBRARIES_FT_FTCalHitSummary_FACTORY_H_

#include "JANA/JFactoryT.h"
#include "FTCalHitSummary.h"

class FTCalHitSummary_factory: public JFactoryT<FTCalHitSummary> {
public:
	FTCalHitSummary_factory();
	virtual ~FTCalHitSummary_factory();

	// Overloaded by user Factories
	virtual void Init();
	virtual void ChangeRun(const std::shared_ptr<const JEvent> &aEvent);
	virtual void Process(const std::shared_ptr<const JEvent> &aEvent);
};

#endif /* SRC_LIBRARIES_FT_FTCalHitSummary_FACTORY_H_ */
