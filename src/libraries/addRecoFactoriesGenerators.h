#ifndef ADD_RECO_FACTORIES_GENERATORS_H_G
#define ADD_RECO_FACTORIES_GENERATORS_H_G



#include "JANA/JApplication.h"

#include "DAQ/JFactoryGenerator_DAQ.h"
#include "TT/JFactoryGenerator_TT.h"
#include "FT/JFactoryGenerator_FT.h"
#include "HallD/JFactoryGenerator_HallD.h"

void addRecoFactoriesGenerators(JApplication *app){
	std::cout<<"addRecoFactoriesGenerators called"<<std::endl;
	app->Add(new JFactoryGenerator_DAQ());
	app->Add(new JFactoryGenerator_TT());
	app->Add(new JFactoryGenerator_FT());
	app->Add(new JFactoryGenerator_HallD());
	std::cout<<"done"<<std::endl;
}



#endif
