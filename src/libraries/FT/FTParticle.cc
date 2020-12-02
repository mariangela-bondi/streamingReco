/*
 * FTParticle.h
 *
 *  Created on: Jan 24, 2020
 *      Author: svallarino
 */
#include "FTParticle.h"
#include "FTCalCluster_factory.h"
#include "FTHodoCluster_factory.h"

#include <cmath>

//Need file of constant
//int minClusterSize = 3; //Need size > to min for accept cluster. Not >=.
//double minClusterEnergy = 1; //Need size > to min for accept cluster. Not >=.
//int time_window = 50;
//double tabledHitZ = 1;

//---------------------------------
// FTCalCluster    (Constructor)
//---------------------------------

FTParticle::FTParticle() {
	time = 0;
	energy = 0;
	particleX = 0;
	particleY = 0;
	particleZ = 0;
	hodo_index = -1;
	charge = 0;
	clus_index = -1;
	centroid_particle.SetXYZ(0, 0, 0);
}

FTParticle::~FTParticle() {
}

float FTParticle::getParticleEnergy() const {
	return energy;
}

void FTParticle::setParticleEnergy(float value) {
	energy = value;
}

double FTParticle::getParticleTime() const {
	return time;
}

void FTParticle::setParticleTime(double value) {
	time = value;
}

int FTParticle::getParticleCharge() const {
	return charge;
}
;

void FTParticle::setParticleCharge(int value) {
	charge = value;
}

int FTParticle::getParticleHodoIndex() const {
	return hodo_index;
}

void FTParticle::setParticleHodoIndex(int value) {
	hodo_index = value;
}

int FTParticle::getParticleClusIndex() const {
	return clus_index;
}

void FTParticle::setParticleClusIndex(int value) {
	clus_index = value;
}

double FTParticle::getParticleDx() const {
	return particleX;
}

void FTParticle::setParticleDx(double value) {
	particleX = value;
}

double FTParticle::getParticleDy() const {
	return particleY;
}

void FTParticle::setParticleDy(double value) {
	particleY = value;
}

double FTParticle::getParticleDz() const {
	return particleZ;
}

void FTParticle::setParticleDz(double value) {
	particleZ = value;
}

void FTParticle::setCentroid(TVector3 value){
	centroid_particle = value;
}

TVector3 FTParticle::getCentroid() const {
	return centroid_particle;
}




