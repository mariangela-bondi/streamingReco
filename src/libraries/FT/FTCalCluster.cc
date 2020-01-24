//
//    File: FTCalCluster.cc
// Created: Wed Jan  8 12:49:31 CET 2020
// Creator: celentan (on Linux apcx4 3.10.0-957.el7.x86_64 x86_64)
//
// ------ Last repository commit info -----
// [ Date ]
// [ Author ]
// [ Source ]
// [ Revision ]
//
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Jefferson Science Associates LLC Copyright Notice:
// Copyright 251 2014 Jefferson Science Associates LLC All Rights Reserved. Redistribution
// and use in source and binary forms, with or without modification, are permitted as a
// licensed user provided that the following conditions are met:
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice, this
//    list of conditions and the following disclaimer in the documentation and/or other
//    materials provided with the distribution.
// 3. The name of the author may not be used to endorse or promote products derived
//    from this software without specific prior written permission.
// This material resulted from work developed under a United States Government Contract.
// The Government retains a paid-up, nonexclusive, irrevocable worldwide license in such
// copyrighted data to reproduce, distribute copies to the public, prepare derivative works,
// perform publicly and display publicly and to permit others to do so.
// THIS SOFTWARE IS PROVIDED BY JEFFERSON SCIENCE ASSOCIATES LLC "AS IS" AND ANY EXPRESS
// OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
// JEFFERSON SCIENCE ASSOCIATES, LLC OR THE U.S. GOVERNMENT BE LIABLE TO LICENSEE OR ANY
// THIRD PARTES FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
// OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include "FTCalCluster.h"
#include "FTCalHit.h"

#include <cmath>


//Need file of constant!!!!!!!!!!
int minClusterSize = 3; //Need size > to min for accept cluster. Not >=.
double minClusterEnergy = 1; //Need size > to min for accept cluster. Not >=.
int time_window = 50;


//---------------------------------
// FTCalCluster    (Constructor)
//---------------------------------
FTCalCluster::FTCalCluster() {
	_clusID = 0;
	_clusSize = 0;
	_clusEnergy = 0;
	_clusRecEnergy = 0;
	_clusTime = 0;
	_clusXX = 0;
	_clusYY = 0;
	_clusSigmaX = 0;
	_clusSigmaY = 0;
	_clusRadius = 0;
	_clusSeedEnergy = 0;
	_clusTheta = 0;
	_clusPhi = 0;
	_goodCluster = false;
	_clusCenter.SetXYZ(0,0,0);

	//Geometry, this is hard-coded in CLAS12 java
	CRYS_ZPOS = 1898;
	depth_z = 65; //ok, this was not hard-coded BUT it is a single number in CCDB
}

FTCalCluster::FTCalCluster(int clusid) {
	_clusID = clusid;
	_clusSize = 0;
	_clusEnergy = 0;
	_clusRecEnergy = 0;
	_clusTime = 0;
	_clusXX = 0;
	_clusYY = 0;
	_clusSigmaX = 0;
	_clusSigmaY = 0;
	_clusRadius = 0;
	_clusSeedEnergy = 0;
	_clusTheta = 0;
	_clusPhi = 0;
	_goodCluster = false;
	_clusCenter.SetXYZ(0,0,0);

	//Geometry, this is hard-coded in CLAS12 java
	CRYS_ZPOS = 1898;
	depth_z = 65; //ok, this was not hard-coded BUT it is a single number in CCDB
}

//---------------------------------
// ~FTCalCluster    (Destructor)
//---------------------------------
FTCalCluster::~FTCalCluster() {
}

int FTCalCluster::getClusterId() const {
	return _clusID;
}

void FTCalCluster::setClusterID(int clusid) {
	_clusID = clusid;
}

void FTCalCluster::computeCluster() {
	//Cluster size
	_clusSize = hits.size();

	//Compute energy
	_clusEnergy = 0;
	for (int i = 0; i < _clusSize; i++)
		_clusEnergy += hits[i]->getHitEnergy();

	//Compute corrected energy;
	//Need to known correction
	_clusRecEnergy = _clusEnergy;

	//Seed Energy
	_clusSeedEnergy = hits[0]->getHitEnergy();

	//Cluster time
	_clusTime = 0;
	for (int i = 0; i < _clusSize; i++) {
		const FTCalHit *hit = hits[i];
		_clusTime += 4 * hit->getHitTime().count() * hit->getHitEnergy();
	}
	_clusTime /= _clusEnergy;

	//Cluster center
	double w_tot = 0;
	double x,y;
	x=0;
	y=0;
	for (int i = 0; i < _clusSize; i++) {
		const FTCalHit *hit = hits[i];
		double w1 = std::max(0., (3.45 + std::log(hit->getHitEnergy() / _clusEnergy)));
		x += w1 * hit->getHitX();
		y += w1 * hit->getHitY();
		_clusXX = w1 * (double) hit->getHitX() * (double) hit->getHitX();
		_clusYY = w1 * (double) hit->getHitY() * (double) hit->getHitY();
		w_tot += w1;
	}

	_clusCenter.SetX(x/w_tot);
	_clusCenter.SetY(y/w_tot);
	_clusCenter.SetZ(CRYS_ZPOS+depth_z);


	_clusXX /= w_tot;
	_clusYY /= w_tot;

	//Cluster sigmaX
	double sigmax2 = _clusXX - std::pow(_clusCenter.X(), 2.);
	if (sigmax2 < 0) sigmax2 = 0;
	_clusSigmaX = std::sqrt(sigmax2);

	//Cluster sigmaY
	double sigmay2 = _clusYY - std::pow(_clusCenter.Y(), 2.);
	if (sigmay2 < 0) sigmay2 = 0;
	_clusSigmaY = std::sqrt(sigmay2);

	//Cluster radius
	double radius2 = (sigmax2 + sigmay2);
	if (radius2 < 0) radius2 = 0;
	_clusRadius = std::sqrt(radius2);

	//Cluster theta (Z is the depth in the crystal starting from entrance as z=0 along the beam direction)
	_clusTheta = (std::atan((std::sqrt(std::pow(_clusCenter.X(), 2.) + std::pow(_clusCenter.Y(), 2.))) / _clusCenter.Z())) * (180. / M_PI);

	//Cluster phi
	_clusPhi = std::atan2(_clusCenter.Y(), _clusCenter.Y()) * (180. / M_PI); //

	if (_clusSize > minClusterSize && _clusEnergy > minClusterEnergy)
		_goodCluster = true;
	else
		_goodCluster = false;

}

//Why _clusID isn't a parameter? _clusID and a loop inside this is inefficent?
int FTCalCluster::getClusterSize() const {
	return _clusSize;
}

//Why _clusID isn't a parameter? Same question above. Perche' utilizzo "this", che riferisce in automatico al cluster?. Predisposizione per il calcolo dell'energia del cluster.
float FTCalCluster::getClusterEnergy() const {
	return _clusEnergy;
}

//Return energy of a cluster with correction.
float FTCalCluster::getClusterFullEnergy() const {
	return _clusRecEnergy;
}

float FTCalCluster::getClusterSeedEnergy() const {
	//Restituisce l'energia del cristallo [0] del cluster, che essendo i cluster costruiti dai cristalli ordinati in energia e' sempre il max del cluster.
	return _clusSeedEnergy;
}

double FTCalCluster::getClusterTime() const {
	return _clusTime;
}
;

//Return center of cluster.
TVector3 FTCalCluster::getCentroid() const {
	return _clusCenter;
}

double FTCalCluster::getX() const {
	return _clusCenter.X();
}

double FTCalCluster::getY() const {
	return _clusCenter.Y();
}

double FTCalCluster::getZ() const {
	return _clusCenter.Z();
}

double FTCalCluster::getXX() const {
	return _clusXX;
}

double FTCalCluster::getYY() const {
	return _clusYY;
}

double FTCalCluster::getWidthX() const {
	return _clusSigmaX;
}

double FTCalCluster::getWidthY() const {
	return _clusSigmaY;
}

double FTCalCluster::getRadius() const {
	return _clusRadius;
}

double FTCalCluster::getTheta() const {
	return _clusTheta;
}

double FTCalCluster::getPhi() const {
	return _clusPhi;
}

bool FTCalCluster::isGoodCluster() const {
	return _goodCluster;
}

bool FTCalCluster::containsHit(const FTCalHit* hit) const {
	bool flag = false;
	for (int i = 0; i < hits.size(); i++) {
		const FTCalHit *hit_conf = hits[i];
		double tDiff = std::fabs(4 * (hit->getHitTime().count() - hit_conf->getHitTime().count())); //ns
		auto xDiff = std::fabs(hit->getHitIX() - hit_conf->getHitIX());
		auto yDiff = std::fabs(hit->getHitIY() - hit_conf->getHitIY());
		if (tDiff < time_window && xDiff <= 1 && yDiff <= 1 && (xDiff + yDiff) > 0) flag = true;
	}
	return flag;
}

void FTCalCluster::push_hit(const FTCalHit* hit) {
	hits.push_back(hit);
}
