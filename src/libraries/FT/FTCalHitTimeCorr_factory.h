/*
 * FTCalHitTimeCorr_factory
 *
 *      Author: svallarino
 */

#ifndef SRC_LIBRARIES_FT_FTCALHITTIMECORR_FACTORY_H_
#define SRC_LIBRARIES_FT_FTCALHITTIMECORR_FACTORY_H_

#include "JANA/JFactoryT.h"
#include "FTCalHitTimeCorr.h"
#include "TT/TranslationTable.h"
class TranslationTable;

class FTCalHitTimeCorr_factory: public JFactoryT<FTCalHitTimeCorr> {
public:

	FTCalHitTimeCorr_factory();
	virtual ~FTCalHitTimeCorr_factory();

	// Overloaded by user Factories
	virtual void Init();
	virtual void ChangeRun(const std::shared_ptr<const JEvent> &aEvent);
	virtual void Process(const std::shared_ptr<const JEvent> &aEvent);

private:

	TranslationTable const *m_tt;

	// GEOMETRY PARAMETERS
	double CRYS_DELTA;
	double CRYS_WIDTH;													  // crystal width in mm
	double CRYS_LENGTH;													  // crystal length in mm
	double CRYS_ZPOS;

	//I am hard-coding the indexes here, since it will always be 1 sector, 1 layer, 332 components.
	double mips_charge[332];

	//crate,slot,channel. crate: 70=adcft1, 71=adcft2
	double tw[500][4];
	double daq_gain[2][22][16];
};

#endif /* SRC_LIBRARIES_FT_FTCALHIT_FACTORY_H_ */
