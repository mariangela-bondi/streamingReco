/*
 * FTCalHit_factory
 *
 *  Created on: Dec 23, 2019
 *      Author: celentan
 */

#ifndef SRC_LIBRARIES_FT_FTCALHIT_FACTORY_H_
#define SRC_LIBRARIES_FT_FTCALHIT_FACTORY_H_

#include "JANA/JFactoryT.h"
#include "FTCalHit.h"

class TranslationTable;

class FTCalHit_factory: public JFactoryT<FTCalHit> {
public:


	FTCalHit_factory();
	virtual ~FTCalHit_factory();

	// Overloaded by user Factories
	virtual void Init();
	virtual void ChangeRun(const std::shared_ptr<const JEvent> &aEvent);
	virtual void Process(const std::shared_ptr<const JEvent> &aEvent);

private:


	TranslationTable *m_tt;
};

#endif /* SRC_LIBRARIES_FT_FTCALHIT_FACTORY_H_ */
