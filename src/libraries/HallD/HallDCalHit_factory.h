/*
 * HallDCalHit_factory
 *
 *  Created on: Dec 23, 2019
 *      Author: celentan
 */

#ifndef SRC_LIBRARIES_HallD_HallDCALHIT_FACTORY_H_
#define SRC_LIBRARIES_HallD_HallDCALHIT_FACTORY_H_

#include "JANA/JFactoryT.h"
#include "HallDCalHit.h"
#include "TT/TranslationTable.h"
class TranslationTable;

class HallDCalHit_factory: public JFactoryT<HallDCalHit> {
public:


	HallDCalHit_factory();
	virtual ~HallDCalHit_factory();

	// Overloaded by user Factories
	virtual void Init();
	virtual void ChangeRun(const std::shared_ptr<const JEvent> &aEvent);
	virtual void Process(const std::shared_ptr<const JEvent> &aEvent);

private:


	TranslationTable const *m_tt;


};

#endif /* SRC_LIBRARIES_HallD_HallDCALHIT_FACTORY_H_ */
