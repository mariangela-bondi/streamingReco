//
//    File: FTHodoCluster.cc
// Created:
// Creator: valla
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

#include "FTHodoCluster.h"
#include "FTHodoHit.h"

#include <cmath>

int minClusterSize_hodo = 2; //Need size > to min for accept cluster. Not >=.
double minClusterEnergy_hodo = 1; //Need size > to min for accept cluster. Not >=.
double time_window_hodo = 50;
double x_window_hodo = 30; //Need to set it
double y_window_hodo = 30; //Need to set it
//double tabledHitZ = 1;

//---------------------------------
// FTHodoCluster    (Constructor)
//---------------------------------
FTHodoCluster::FTHodoCluster() {
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
	_clusCenter.SetXYZ(0, 0, 0);
}

FTHodoCluster::FTHodoCluster(int clusid) {
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
	_clusCenter.SetXYZ(0, 0, 0);
}

//---------------------------------
// ~FTHodoCluster    (Destructor)
//---------------------------------
FTHodoCluster::~FTHodoCluster() {
}

int FTHodoCluster::getClusterId() const {
	return _clusID;
}

void FTHodoCluster::setClusterID(int clusid) {
	_clusID = clusid;
}

void FTHodoCluster::computeCluster() {
	//Cluster size
	_clusSize = hits.size();

	//Compute energy
	_clusEnergy = 0;
	for (int i = 0; i < _clusSize; i++)
		_clusEnergy += hits[i]->getHitEnergy();

	//Compute corrected energy;
	//Need to known correction.
	_clusRecEnergy = _clusEnergy;

	//Seed Energy
	_clusSeedEnergy = hits[0]->getHitEnergy();

	//Cluster time
	_clusTime = 0;
	for (int i = 0; i < _clusSize; i++) {
		const FTHodoHit *hit = hits[i];
		_clusTime += hit->getHitTime() * hit->getHitEnergy();
	}
	_clusTime /= _clusEnergy;

	//Cluster center
	double w_tot = 0;
	double x = 0;
	double y = 0;
	double z = 0;
	for (int i = 0; i < _clusSize; i++) {
		const FTHodoHit *hit = hits[i];
		x += hit->getHitEnergy() * hit->getHitDx();
		y += hit->getHitEnergy() * hit->getHitDy();
		z += hit->getHitEnergy() * hit->getHitDz();
		_clusXX = hit->getHitEnergy() * hit->getHitDx() * hit->getHitDx();
		_clusYY = hit->getHitEnergy() * hit->getHitDy() * hit->getHitDy();
	}
	x /= _clusEnergy;
	y /= _clusEnergy;
	z /= _clusEnergy;

	_clusCenter.SetXYZ(x, y, z);
	_clusXX /= _clusEnergy;
	_clusYY /= _clusEnergy;

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
	_clusPhi = std::atan2(_clusCenter.Y(), _clusCenter.X()) * (180. / M_PI); //

	bool layer1 = false;
	bool layer2 = false;
	//Cluster contain layer 1 and layer 2 hit?
	for (auto hit : hits) {
		if (hit->m_channel.layer == 1) layer1 = true;
		if (hit->m_channel.layer == 2) layer2 = true;
	}

	if (_clusSize > minClusterSize_hodo && _clusEnergy > minClusterEnergy_hodo && layer1 == true && layer2 == true)
		_goodCluster = true;
	else
		_goodCluster = false;

}

//Why _clusID isn't a parameter? _clusID and a loop inside this is inefficent?
int FTHodoCluster::getClusterSize() const {
	return _clusSize;
}

//Why _clusID isn't a parameter? Same question above. Perche' utilizzo "this", che riferisce in automatico al cluster?. Predisposizione per il calcolo dell'energia del cluster.
float FTHodoCluster::getClusterEnergy() const {
	return _clusEnergy;
}

//Return energy of a cluster with correction.
float FTHodoCluster::getClusterFullEnergy() const {
	return _clusRecEnergy;
}

float FTHodoCluster::getClusterSeedEnergy() const {
	//Restituisce l'energia del cristallo [0] del cluster, che essendo i cluster costruiti dai cristalli ordinati in energia e' sempre il max del cluster.
	return _clusSeedEnergy;
}

double FTHodoCluster::getClusterTime() const {
	return _clusTime;
}

//Return center of cluster.
TVector3 FTHodoCluster::getCentroid() const {
	return _clusCenter;
}

double FTHodoCluster::getX() const {
	return _clusCenter.X();
}

double FTHodoCluster::getY() const {
	return _clusCenter.Y();
}

double FTHodoCluster::getZ() const {
	return _clusCenter.Z();
}

double FTHodoCluster::getXX() const {
	return _clusXX;
}

double FTHodoCluster::getYY() const {
	return _clusYY;
}

double FTHodoCluster::getWidthX() const {
	return _clusSigmaX;
}

double FTHodoCluster::getWidthY() const {
	return _clusSigmaY;
}

double FTHodoCluster::getRadius() const {
	return _clusRadius;
}

double FTHodoCluster::getTheta() const {
	return _clusTheta;
}

double FTHodoCluster::getPhi() const {
	return _clusPhi;
}

const FTHodoHit* FTHodoCluster::getHit(int i) const {
	return hits[i];
}

bool FTHodoCluster::isGoodCluster() const {
	return _goodCluster;
}

bool FTHodoCluster::containsHit(const FTHodoHit* hit) const {
	bool flag = false;
	for (int i = 0; i < hits.size(); i++) {
		const FTHodoHit *hit_conf = hits[i];
		double tDiff = std::fabs( (hit->getHitTime() - hit_conf->getHitTime())); //ns
		auto xDiff = std::fabs(hit->getHitDx() - hit_conf->getHitDx());
		auto yDiff = std::fabs(hit->getHitDy() - hit_conf->getHitDy());
		if (tDiff < time_window_hodo && xDiff <= x_window_hodo && yDiff <= y_window_hodo && (xDiff + yDiff) > 0) flag = true;
	}
	return flag;
}

void FTHodoCluster::push_hit(const FTHodoHit* hit) {
	hits.push_back(hit);
}
