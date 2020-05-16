#ifndef _JFACTORYGENERATOR_HALLD_H_
#define _JFACTORYGENERATOR_HALLD_H_

#include <JANA/JFactoryGenerator.h>
#include <JANA/JFactoryT.h>
#include "HallD/HallDCalHit_factory.h"

class JFactoryGenerator_HallD: public JFactoryGenerator {
public:

	void GenerateFactories(JFactorySet *factory_set) {
		factory_set->Add(new HallDCalHit_factory());

	}
};

#endif
