/*
 * FTParticle_factory
 *
 *  Created on: Jan 24, 2020
 *      Author: svallarino
 */

#ifndef SRC_LIBRARIES_FT_FTParticle_FACTORY_H_
#define SRC_LIBRARIES_FT_FTParticle_FACTORY_H_

#include "JANA/JFactoryT.h"
#include "FTCalCluster.h"
#include "FTHodoCluster.h"
#include "FTParticle.h"

class FTParticle_factory: public JFactoryT<FTParticle> {
public:
	FTParticle_factory();
	virtual ~FTParticle_factory();

	// Overloaded by user Factories
	virtual void Init();
	virtual void ChangeRun(const std::shared_ptr<const JEvent> &aEvent);
	virtual void Process(const std::shared_ptr<const JEvent> &aEvent);
};

#endif
