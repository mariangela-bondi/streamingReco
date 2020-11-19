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

double EN_THRES = 0.25 ;
class FTHodoHit: public JObject {
public:
	FTHodoHit();
	virtual ~FTHodoHit();

	float getHitEnergy() const {
		return energy;
	}

	void setHitEnergy(float charge) {
		this->energy = charge;
	}

	float getHitTime() const {
		return time;
	}

	void setHitTime(float time) {
		this->time = time;
	}

	double getHitDx()const{
		return Dx;
	}

	double getHitDy()const{
		return Dy;
	}

	double getHitDz()const{
		return Dz;
	}

	void setDx(double value){
		this->Dx=value;
	}

	void setDy(double value){
		this->Dy=value;
	}

	void setDz(double value){
		this->Dz=value;
	}

  bool passHitSelection(const FTHodoHit* hit) {
	// a selection cut to pass the hit.
	if(hit.getHitEnergy() > EN_THRES) {
		return true;
	} else {
		return false;
	}
}

	TranslationTable::FTHODO_Index_t m_channel;

protected:

private:
	float time;
	float energy;
	double Dx;
	double Dy;
	double Dz;
};

#endif /* SRC_LIBRARIES_FT_FTHODOHIT_H_ */
