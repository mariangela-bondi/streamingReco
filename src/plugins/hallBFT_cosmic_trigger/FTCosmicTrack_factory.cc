//
// This factory is used to identify tracks within a time frame/slice.
// For each track it identifies, a HallDCalTrack object is created.
// Tracks are identified by looking for known hit patterns in the
// calorimeter blocks that are within CALTRACK:COINICIDENCE_WINDOW
// ns of each other. The default time window is 100 ns.
//
//


#include "FTCosmicTrack_factory.h"

#include <JANA/JEvent.h>

//-----------------------------------
// Init
//-----------------------------------
void FTCosmicTrack_factory::Init() {

}

//-----------------------------------
// ChangeRun
//-----------------------------------
void FTCosmicTrack_factory::ChangeRun(const std::shared_ptr<const JEvent> &event) {

	// Set the default value for the coincidence window and 
	// declare it asa parameter so it can be changed at run
	// time.
	t_window = 100.0;
	MIN_HITS_PER_TRACK = 8;
	GetApplication()->GetJParameterManager()->SetDefaultParameter("FTCOSMICTRACK:COINICIDENCE_WINDOW", t_window, "Coincidence window width in ns for identifying cosmic tracks in calorimeter");
	GetApplication()->GetJParameterManager()->SetDefaultParameter("FTCOSMICTRACK:MIN_HITS_PER_TRACK", MIN_HITS_PER_TRACK, "Minimum number of hits in a row to call it a track.");
}

//-----------------------------------
// Process
//-----------------------------------
void FTCosmicTrack_factory::Process(const std::shared_ptr<const JEvent> &event) {

	// We need to identify cosmic tracks in the calorimeter
	// by both hit pattern and time. We do this by first ordering
	// the hits by time and then looking for sequences within
	// t_window of each other that fit one of the predefined patterns.

	// Get list of hits
	auto hits = event->Get<FTCalHitEneCorr>();

	// Sort hits in order of time
	auto mylambda = [](const FTCalHitEneCorr *a, const FTCalHitEneCorr *b ){return a->getHitTime() < b->getHitTime();};
	std::sort( hits.begin(), hits.end(), mylambda);

	// Loop over hits. For each, find list of hits within
	// the t_window ns following it.
	for( uint32_t i=0; (i+2)< hits.size(); i++){
	
		// time of first (earliest) hit in this sequence
		auto t_start = hits[i]->getHitTime();
		
		// find latest hit still within t_window of t_start
		auto j = i+2; // we need minimum of 3 hits
		for( ; j<hits.size(); j++){
			auto delta_t = hits[j]->getHitTime() - t_start;
			if( delta_t > t_window ) break;
		}
		
		// Check if hits match a track pattern
		if (match_track_pattern(hits.begin()+i, hits.begin()+j) != -1) {

			// Found a track! Publish outputs
			Insert( new FTCosmicTrack(hits.begin()+i, hits.begin()+j) );
		}

	} // end loop over i
}

//-----------------------------------
// match_track_pattern
//
// return -1 if no track found. Return
// anything else if a track is found.
//-----------------------------------
int FTCosmicTrack_factory::match_track_pattern(FTCosmicTrack::hit_iter iter_start, FTCosmicTrack::hit_iter iter_end) {

	// The iter_start and iter_end allow iteration over FTHitEneCorr*
	// objects that should be searched for a pattern that looks like
	// a cosmic track. 
	//
	// Empirically, the values of iX and iY range from 1-22.
	// Make an array of 22 64bit integers, each representing 1
	// iy-value. Bits 22-43 correspond to ix values 1-22. 
	// We then use bit shift operations to look for hits in adjacent
	// rows. We use bits 22-43 to give room for shifting (though
	// we really don't need that much).
	// 
	
	std::vector<uint64_t> v(22, 0); // initialize to 22 elements, all zeros
	for( auto it=iter_start; it!=iter_end; it++){
		auto iX = (*it)->getHitIX();
		auto iY = (*it)->getHitIY();
		assert( iX>=1 && iX<=22 );
		assert( iY>=1 && iY<=22 );
		v[iY-1] |= 0x1<<(iX+21);
	}

	// Loop over rows
	for( uint32_t j=0; j<v.size()-MIN_HITS_PER_TRACK-1; j++ ){
		if( v[j] == 0 ) continue; // don't bother with rows that have noblocks hit
		int Nmatches = 1; // count this row
		CheckNextRow( v[j], j+1, v, Nmatches ); // recursively walk through rows counting how many we can chain
		if( Nmatches >= MIN_HITS_PER_TRACK ){
			//_DBG_<< " Found cosmic track!" << std::endl;
			return Nmatches;
		}
	}

	return -1;
}

//------------------------------------------------------------------------------
// CheckNextRow
//
// This is a recursive method that will check if a hit in the current row
// touches a hit in the given prev_row. It assumes a hit touches if 
// it is within one bit of a hit in prev_row (i.e iX is within +/-1).
//
// Only matched bits will be passed to the next call of CheckNextRow
// thus, chains of hits will be built.
//------------------------------------------------------------------------------
void FTCosmicTrack_factory::CheckNextRow( uint64_t prev_row, uint32_t irow, std::vector<uint64_t> &v, int &Nmatches ){
	
	if( irow >= v.size() ) return; // no more rows to check

	auto Nmatches_max = Nmatches;

	uint64_t cur_row = (v[irow]>>1); // bit shift right 1 so we can loop over shifting right one, no shift, left one

	// Loop over 3 possible bit shifts
	for(int ishift=0; ishift<=3; ishift++){
		auto overlap = cur_row & prev_row;
		if( overlap ){
			// OK, at least 1 bit matches recall ourself to check the next row
			auto Nmatches_this = Nmatches+1;
			CheckNextRow( overlap, irow+1, v, Nmatches_this);
			if( Nmatches_this > Nmatches_max ) Nmatches_max = Nmatches_this;
		}
		cur_row = (cur_row<<1);	// bit shift forward 1
	}
	
	Nmatches = Nmatches_max;
}

