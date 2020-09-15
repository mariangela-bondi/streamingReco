
#ifndef _HallDCalTrack_Factory_h_
#define _HallDCalTrack_Factory_h_

#include <JANA/JFactoryT.h>

#include "HallDCalTrack.h"

class HallDCalTrack_Factory : public JFactoryT<HallDCalTrack> {

    // Insert any member variables here
	static const size_t GRID_HEIGHT = 3;
	static const size_t GRID_WIDTH  = 3;
	
	double t_window; // (see HallDCalTrack_Factory::ChangeRun)

public:
    HallDCalTrack_Factory() : JFactoryT<HallDCalTrack>(NAME_OF_THIS) {};
    void Init() override;
    void ChangeRun(const std::shared_ptr<const JEvent> &event) override;
    void Process(const std::shared_ptr<const JEvent> &event) override;

	static int match_track_pattern(bool pixel_grid[GRID_HEIGHT][GRID_WIDTH]);
};

#endif // _HallDCalTrack_Factory_h_
