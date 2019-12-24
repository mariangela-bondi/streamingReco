#ifndef ADD_RECO_FACTORIES_GENERATORS_H_G
#define ADD_RECO_FACTORIES_GENERATORS_H_G



#include "DAQ/JFactoryGenerator_DAQ.h"
#include "JANA/JApplication.h"

void addRecoFactoriesGenerators(JApplication *app){
	std::cout<<"addRecoFactoriesGenerators called"<<std::endl;
	app->Add(new JFactoryGenerator_DAQ());

	std::cout<<"done"<<std::endl;
}



#endif
