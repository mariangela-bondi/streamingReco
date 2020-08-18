#ifndef _HALLBFT_TRIGGERS_GENERATOR_H_
#define _HALLBFT_TRIGGERS_GENERATOR_H_

#include <JANA/JFactoryGenerator.h>
#include <JANA/JFactoryT.h>

#include "TriggerDecision_FTCalCluster_factory.h"
#include "TriggerDecision_MinBias_factory.h"

class hallBFT_triggers_generator: public JFactoryGenerator {
public:
	void GenerateFactories(JFactorySet *factory_set) {
		factory_set->Add(new TriggerDecision_FTCalCluster_factory());
		factory_set->Add(new TriggerDecision_MinBias_factory());
	}
};

#endif // _JFACTORYGENERATOR_EXAMPLE2_H_
