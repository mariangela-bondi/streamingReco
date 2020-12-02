/*
 * FTParticle.h
 *
 *  Created on: Jan 24, 2020
 *      Author: svallarino
 */

#ifndef SRC_LIBRARIES_FT_FTPARTICLE_H_
#define SRC_LIBRARIES_FT_FTPARTICLE_H_

#include <JANA/JObject.h>
#include <JANA/JFactory.h>
#include "FTCalCluster_factory_EneCorr.h"
#include "FTHodoCluster_factory.h"
#include "TVector3.h"

// #include "TT/TranslationTable.h"      I think don't needed.
// #include "DAQ/chronoTypeDef.h"        I think don't needed.

class FTParticle: public JObject {
public:
	FTParticle();
	virtual ~FTParticle();

	float getParticleEnergy() const;

	void setParticleEnergy(float value);

	double getParticleTime() const;

	void setParticleTime(double value);

	int getParticleCharge() const;

	void setParticleCharge(int value);

	int getParticleHodoIndex() const;

	void setParticleHodoIndex(int value);

	int getParticleClusIndex() const;

	void setParticleClusIndex(int value);

	double getParticleDx() const;

	void setParticleDx(double value);

	double getParticleDy() const;

	void setParticleDy(double value);

	double getParticleDz() const;

	void setParticleDz(double value);

	void setCentroid(TVector3 value);

	TVector3 getCentroid() const;

// 	TranslationTable::FTHODO_Index_t m_channel;   I think don't needed.

protected:

private:
	double time;
	float energy;
	double particleX;
	double particleY;
	double particleZ;
	int hodo_index;
	int clus_index;
	int charge;
	TVector3 centroid_particle;
};

#endif /* SRC_LIBRARIES_FT_FTPARTICLE_H_ */
