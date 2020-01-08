#ifndef _JFACTORYGENERATOR_DAQ_H_
#define _JFACTORYGENERATOR_DAQ_H_

#include <JANA/JFactoryGenerator.h>
#include <JANA/JFactoryT.h>

#include "DAQ/faWaveboardHit_factory.h"
#include "DAQ/fa250VTPMode7Hit_factory.h"


class JFactoryGenerator_DAQ:public JFactoryGenerator{
	public:

	void GenerateFactories(JFactorySet *factory_set){
		factory_set->Add(new faWaveboardHit_factory());
		factory_set->Add(new fa250VTPMode7Hit_factory());
	}
};

#endif   // _JFACTORYGENERATOR_EXAMPLE2_H_
