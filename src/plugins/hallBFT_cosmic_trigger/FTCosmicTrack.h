//
// Hall-B Forward Tagger Calorimeter cosmic track
//
// Objects of this class represent patterns in the FT that
// look like a minimum ionizing track.
//

#ifndef _FTCosmicTrack_h_
#define _FTCosmicTrack_h_

#include <JANA/JObject.h>

#include <FT/FTCalHitEneCorr.h>


class FTCosmicTrack : public JObject {

	public:
	
	std::string description;

	/// List of hits belonging to this track
	std::vector<const FTCalHitEneCorr*> hits;
	
	/// Properties of the track
	float t_start;
	float t_end;
	uint32_t Nhits;

	/// Make it convenient to construct one of these things
	typedef std::vector<const FTCalHitEneCorr*>::iterator hit_iter; // (make the next line more compact/readable)
	FTCosmicTrack(hit_iter begin, hit_iter end){

		hits.insert(hits.begin(), begin, end);
		t_start = hits.front()->getHitTime();
		t_end   = hits.back()->getHitTime();
		Nhits   = hits.size();
	}
	
	/// Convenience functions
	float getTrackStartTime(void){ return t_start; }
	float getTrackEndTime(void)  { return t_end; }
	std::vector<const FTCalHitEneCorr*> GetHits() { return hits; }
	int GetNumHits() { return Nhits; }


	/// Override className to tell JANA to store the exact name of this class where we can
	/// access it at runtime. JANA provides a NAME_OF_THIS macro so that this will return the correct value
	/// even if you rename the class using automatic refactoring tools.

	const std::string className() const override {
		return NAME_OF_THIS;
	}

    /// Override Summarize to tell JANA how to produce a convenient string representation for our JObject.
    /// This can be used called from user code, but also lets JANA automatically inspect its own data. For instance,
    /// adding JCsvWriter<Hit> will automatically generate a CSV file containing each hit. Warning: This is obviously
    /// slow, so use this for debugging and monitoring but not inside the performance critical code paths.

    void Summarize(JObjectSummary& summary) const override {
        summary.add(t_start, NAME_OF(t_start), "%f", "Time of earliest hit");
        summary.add(t_end  , NAME_OF(t_end)  , "%f", "Time of latest hit"  );
        summary.add(Nhits  , NAME_OF(Nhits)  , "%d", "Number of blocks hit"  );
        summary.add(description.c_str(), NAME_OF(description), "%s", "Description");
    }
};


#endif // _FTCosmicTrack_h_

