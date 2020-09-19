
#ifndef _FTCosmicTrack_factory_h_
#define _FTCosmicTrack_factory_h_

#include <JANA/JFactoryT.h>

#include "FTCosmicTrack.h"

class FTCosmicTrack_factory : public JFactoryT<FTCosmicTrack> {

    // Insert any member variables here
	static const size_t GRID_HEIGHT = 3;
	static const size_t GRID_WIDTH  = 3;
	
	double t_window; // (see FTCosmicTrack_factory::ChangeRun)
	int MIN_HITS_PER_TRACK;

public:
    FTCosmicTrack_factory() : JFactoryT<FTCosmicTrack>(NAME_OF_THIS) {};
    void Init() override;
    void ChangeRun(const std::shared_ptr<const JEvent> &event) override;
    void Process(const std::shared_ptr<const JEvent> &event) override;

    int match_track_pattern(FTCosmicTrack::hit_iter iter_start, FTCosmicTrack::hit_iter iter_end);
    void CheckNextRow( uint64_t prev_row, uint32_t irow, std::vector<uint64_t> &v, int &Nmatches );
};

#endif // _FTCosmicTrack_factory_h_
