/*
 * FTHodoCluster_factory
 *
 *  Created on: Jan 23, 2019
 *      Author: valla
 */

#ifndef SRC_LIBRARIES_FT_FTHODOCluster_FACTORY_H_
#define SRC_LIBRARIES_FT_FTHODOCluster_FACTORY_H_

#include "JANA/JFactoryT.h"
#include "FTHodoCluster.h"

class FTHodoCluster_factory: public JFactoryT<FTHodoCluster> {
public:
	FTHodoCluster_factory();
	virtual ~FTHodoCluster_factory();

	// Overloaded by user Factories
	virtual void Init();
	virtual void ChangeRun(const std::shared_ptr<const JEvent> &aEvent);
	virtual void Process(const std::shared_ptr<const JEvent> &aEvent);
};

#endif /* SRC_LIBRARIES_FT_FTHODOCluster_FACTORY_H_ */
