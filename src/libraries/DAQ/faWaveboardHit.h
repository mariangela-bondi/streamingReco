// $Id$
//
//    File: fa250Mode1Hit.h
// Created: Mon Dec 28 11:04:04 CET 2015
// Creator: celentan (on Linux apcx4 2.6.32-504.30.3.el6.x86_64 x86_64)
//

#ifndef _fa250WaveboardHit_
#define _fa250WaveboardHit_

#include <JANA/JObject.h>
#include <JANA/JFactory.h>
#include "faHit.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/cstdint.hpp>

#include <vector>
#include <chrono>


/* These typedefs may already be defined, but this is not a problem,
 * C++ supports this explicitly */
typedef std::chrono::duration<boost::int_least64_t, std::ratio<1, 8000> > T125usec;
typedef std::chrono::duration<boost::int_least64_t, std::ratio<1, 250000000> > T4nsec;
typedef std::chrono::duration<boost::int_least64_t, std::ratio<86400> > days;


class faWaveboardHit: public faHit {
public:


	faWaveboardHit();
	virtual ~faWaveboardHit();
	std::vector<uint16_t> samples; //these are the raw samples

	T4nsec m_time; //in ns

	float charge; //as reported from the waveboard
	float m_dT; //sampling time

	virtual void Summarize(JObjectSummary& summary) const {
		summary.add(m_channel.crate,"CRATE","%f","The crate id of this board");
		summary.add(m_channel.slot,"SLOT","%f","The slot of this board");
		summary.add(m_channel.channel,"CHANNEL","%f","The channel");

};

//void toHisto(TH1D *h) const;

//virtual TCanvas* Draw(int id=0) const;

protected:
//mutable TH1D *hWave;
};

#endif // _fa250Mode1Hit_

