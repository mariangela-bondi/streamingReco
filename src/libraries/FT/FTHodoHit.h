/*
 * FTHodoHit.h
 *
 *  Created on: Jan 13, 2020
 *      Author: celentan
 */

#ifndef SRC_LIBRARIES_FT_FTHODOHIT_H_
#define SRC_LIBRARIES_FT_FTHODOHIT_H_

#include "JANA/JObject.h"
#include "TT/TranslationTable.h"
#include "DAQ/chronoTypeDef.h"

class FTHodoHit: public JObject {
public:
	FTHodoHit();
	virtual ~FTHodoHit();

	float getEnergy() const {
		return energy;
	}

	void setEnergy(float charge) {
		this->energy = energy;
	}

	T4nsec getTime() const {
		return time;
	}

	void setTime(T4nsec time) {
		this->time = time;
	}

	TranslationTable::FTHODO_Index_t m_channel;

protected:

private:
	T4nsec time;
	float energy;
};

#endif /* SRC_LIBRARIES_FT_FTHODOHIT_H_ */
