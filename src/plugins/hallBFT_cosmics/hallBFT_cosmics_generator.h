#ifndef _HALLBFT_TRIGGERS_GENERATOR_H_
#define _HALLBFT_TRIGGERS_GENERATOR_H_

#include <JANA/JFactoryGenerator.h>
#include <JANA/JFactoryT.h>

#include "TriggerDecision_cosmics_factory.h"

class hallBFT_cosmics_generator: public JFactoryGenerator {
public:
	void GenerateFactories(JFactorySet *factory_set) {
		factory_set->Add(new TriggerDecision_cosmics_factory());
	}
};

#endif // _JFACTORYGENERATOR_EXAMPLE2_H_
