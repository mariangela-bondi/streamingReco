#ifndef _HALLBFT_TRIGGERS_GENERATOR_H_
#define _HALLBFT_TRIGGERS_GENERATOR_H_

#include <JANA/JFactoryGenerator.h>
#include <JANA/JFactoryT.h>

#include "TriggerDecision_default_factory.h"
#include "TriggerDecision_second_factory.h"

class hallBFT_triggers_generator: public JFactoryGenerator {
public:
	void GenerateFactories(JFactorySet *factory_set) {
		factory_set->Add(new TriggerDecision_default_factory());
		factory_set->Add(new TriggerDecision_second_factory());
	}
};

#endif // _JFACTORYGENERATOR_EXAMPLE2_H_
