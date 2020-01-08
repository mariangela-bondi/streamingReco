#ifndef ADD_RECO_FACTORIES_GENERATORS_H_G
#define ADD_RECO_FACTORIES_GENERATORS_H_G



#include "JANA/JApplication.h"

#include "DAQ/JFactoryGenerator_DAQ.h"
#include "FT/JFactoryGenerator_FT.h"

void addRecoFactoriesGenerators(JApplication *app){
	std::cout<<"addRecoFactoriesGenerators called"<<std::endl;
	app->Add(new JFactoryGenerator_DAQ());
	app->Add(new JFactoryGenerator_FT());

	std::cout<<"done"<<std::endl;
}



#endif
