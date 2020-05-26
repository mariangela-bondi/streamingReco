#ifndef _JFACTORYGENERATOR_FT_H_
#define _JFACTORYGENERATOR_FT_H_

#include <JANA/JFactoryGenerator.h>
#include <JANA/JFactoryT.h>
//#include "MyCluster.h"
//#include "MyHit.h"

#include "FT/FTCalHit_factory.h"
#include "FT/FTCalHitEneCorr_factory.h"
#include "FT/FTCalHitSummary_factory.h"
#include "FT/FTCalCluster_factory.h"
#include "FT/FTCalCluster_factory_EneCorr.h"
#include "FT/FTHodoHit_factory.h"
#include "FT/FTHodoCluster_factory.h"
#include "FT/FTParticle_factory.h"
class JFactoryGenerator_FT: public JFactoryGenerator {
public:

	void GenerateFactories(JFactorySet *factory_set) {
		factory_set->Add(new FTCalHit_factory());
		factory_set->Add(new FTCalHitEneCorr_factory());
		factory_set->Add(new FTCalHitSummary_factory());
		factory_set->Add(new FTCalCluster_factory());
		factory_set->Add(new FTCalCluster_factory_EneCorr()); //tagged factory
		factory_set->Add(new FTCalCluster_factory_TimeCorr()); //tagged factory

		factory_set->Add(new FTHodoHit_factory());
		factory_set->Add(new FTHodoCluster_factory());

		factory_set->Add(new FTParticle_factory());
		//factory_set->Add( new JFactoryT<MyHit>()     );
		//factory_set->Add( new JFactoryT<MyCluster>() );

	}
};

#endif   // _JFACTORYGENERATOR_EXAMPLE2_H_
