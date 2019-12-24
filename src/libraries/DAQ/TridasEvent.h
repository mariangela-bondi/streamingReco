//
// Created by Nathan Brei on 2019-12-15.
//

#ifndef JANA2_TRIDASEVENT_H
#define JANA2_TRIDASEVENT_H
#include <chrono>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/cstdint.hpp>

/*When the TridasEvent file is included in the TrigJANA plugin,
 * these typedefs may already be defined, but this is not a problem,
 * C++ supports this explicitly
 */
typedef std::chrono::duration<boost::int_least64_t, std::ratio<1, 8000> > T125usec;
typedef std::chrono::duration<boost::int_least64_t, std::ratio<1, 250000000> > T4nsec;
typedef std::chrono::duration<boost::int_least64_t, std::ratio<86400> > days;


/*In order to minimize interference between Tridas and JANA,
 * we define here a minimal structure representing a single FADC hit.
 * This is supposed to not change during time.
 */
struct fadcHit{
	uint8_t crate,slot,channel;
	T4nsec time;
	float charge;  				//Charge corrected by ADC pedestals
	std::vector<uint16_t> data; //I assume the hits are sampled with 16bit digitizers at maximum
};


/// TridasEvent is an adapter between TRIDAS objects and JANA objects. The event source should
/// insert one TridasEvent into each JEvent.
struct TridasEvent : public JObject {

    std::vector<fadcHit> hits;

    int run_number;
    int event_number;

    mutable bool should_keep;  // TODO: This needs to be mutable because we will be updating a const JObject
                               //       This won't be a problem with the 'real' TRIDAS, whose should_keep lives behind the
                               //       tridas_data pointer, but we should start thinking about a more elegant way to handle
                               //       the general case.
};


#endif //JANA2_TRIDASEVENT_H
