#ifndef PACKAGES_DATAFORMATS_F_DATAFORMAT_BDX_HPP
#define PACKAGES_DATAFORMATS_F_DATAFORMAT_BDX_HPP

#include <chrono>
#include <ratio>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/cstdint.hpp>

#include <cstddef>
#include <cassert>
#include <ostream>
#include "../TRIDAS/chrono_io.hpp"
#include "../TRIDAS/s_dataformat_bdx.hpp"

// It is possible to represent a full century time
// in unit of 5 nano seconds with a 64bit integer.
typedef std::chrono::duration<boost::int_least64_t, std::ratio<1, 8000> > T125usec;
typedef std::chrono::duration<boost::int_least64_t, std::ratio<1, 250000000> > T4nsec;
typedef std::chrono::duration<boost::int_least64_t, std::ratio<86400> > days;

namespace tridas {
namespace bdx {

typedef T125usec coarse_time;
typedef T4nsec     fine_time;

inline
DataFrameHeader* dataframeheader_cast(unsigned char* pointer)
{
  return static_cast<DataFrameHeader*>(
    static_cast<void*>(pointer));
}

inline
const DataFrameHeader* dataframeheader_cast(unsigned char const* pointer)
{
  return static_cast<DataFrameHeader const*>(
    static_cast<void const*>(pointer));
}


// TODO: Remove them after passing to unsigned char* in the whole TriDAS
inline
DataFrameHeader* dataframeheader_cast(char* pointer)
{
  return static_cast<DataFrameHeader*>(
    static_cast<void*>(pointer));
}

inline
const DataFrameHeader* dataframeheader_cast(char const* pointer)
{
  return static_cast<DataFrameHeader const*>(
    static_cast<void const*>(pointer));
}

inline
bool operator ==(DataFrameHeader const& first, DataFrameHeader const& second)
{
  return
     first.PMTID        == second.PMTID
  && first.EFCMID       == second.EFCMID
  && first.TowerID      == second.TowerID
  && first.SyncBytes    == second.SyncBytes
  && first.T4ns         == second.T4ns
  && first.FrameCounter == second.FrameCounter
  && first.Seconds      == second.Seconds
  && first.Days         == second.Days
  && first.Years        == second.Years
  && first.NDataSamples == second.NDataSamples
  && first.FifoFull     == second.FifoFull
  && first.Charge       == second.Charge
  && first.FragFlag     == second.FragFlag
  && first.ZipFlag      == second.ZipFlag;
}

inline
bool compressed(bdx::DataFrameHeader const& header)
{
  return header.ZipFlag;
}

inline
bool subsequent(bdx::DataFrameHeader const& header)
{
  return header.FragFlag;
}

inline
unsigned int getDFHSampleSize(bdx::DataFrameHeader const& header)
{
  return 2;
}

inline
fine_time getCurrentTime()
{
  // This is the time in seconds elapsed since the epoch of the 1-gen-2000 0:00
  const static std::chrono::seconds unix_time_1_1_2000(946684800);
  return std::chrono::duration_cast<fine_time>(std::chrono::system_clock::now().time_since_epoch() - unix_time_1_1_2000);
}

inline
bool testDFHSync(bdx::DataFrameHeader const& header)
{
  return header.SyncBytes == 21930;
}

inline
unsigned int getDFHCharge(bdx::DataFrameHeader const& header)
{
  return header.Charge;
}

inline
std::size_t getDFHPayloadSize(bdx::DataFrameHeader const& header)
{
  unsigned const pad = header.NDataSamples % 2 == 0 ? 0 : 2;
  return header.NDataSamples * getDFHSampleSize(header) + pad;
}

inline
std::size_t getDFHNSamples(bdx::DataFrameHeader const& header)
{
  return header.NDataSamples;
}

// Converts the year BCD format in binary

inline
unsigned int getDFHYears(bdx::DataFrameHeader const& header)
{
  const static uint8_t mask1 = 15, mask2 = 240;
  unsigned int const r = header.Years & mask1;
  return r + ((10 * (header.Years & mask2)) >> 4);
}

// Converts the day BCD format in binary

inline
unsigned int getDFHDays(bdx::DataFrameHeader const& header)
{
  const static unsigned int mask1 = 15, mask2 = 240, mask3 = 768;
  unsigned int r = header.Days & mask1;
  r += (10  * (header.Days & mask2)) >> 4;
  return r + ((100 * (header.Days & mask3)) >> 8);
}

// Time in seconds since midnight

inline
fine_time getDFHDayTime(bdx::DataFrameHeader const& header)
{
  return std::chrono::seconds(header.Seconds) +
    T125usec(header.FrameCounter) +
    T4nsec(header.T4ns);
}

// Time in seconds since the 1-gen of this year

inline
fine_time getDFHYearTime(bdx::DataFrameHeader const& header)
{
  return std::chrono::seconds(86400 * getDFHDays(header)) +
    getDFHDayTime(header);
}

// Time elapsed since 1-gen-2000

inline
fine_time getDFHFullTime(bdx::DataFrameHeader const& header)
{
  unsigned int const years = getDFHYears(header);
  unsigned int bissextile_days = (years >> 2) + 1;

  if (years % 4 == 0) {
    --bissextile_days;
  }

  return std::chrono::seconds(
    31536000 * years + 86400 * bissextile_days)
      + getDFHYearTime(header);
}

// Set the Days field. "gregorian" is a number representing the number of
// days since the start of the year. 1 Jan == 0

inline
void setDFHDays(unsigned int gregorian, bdx::DataFrameHeader& header)
{
  assert(gregorian < 367);
  unsigned int const hundreds = gregorian / 100;
  unsigned int const tens = (gregorian % 100) / 10;
  unsigned int const units = gregorian % 10;
  header.Days = (hundreds << 8) + (tens << 4) + units;
}

// Set the Years field. "year" is a number representing the number of
// years since the start of the century. 2000 == 0

inline
void setDFHYears(unsigned int year, bdx::DataFrameHeader& header)
{
  assert(year < 100);
  unsigned int const tens = year / 10;
  unsigned int const units = year % 10;
  header.Years = (tens << 4) + units;
}

inline
void setDFHDayTime(fine_time const& time, bdx::DataFrameHeader& header)
{
  assert(time < days(1));
  std::chrono::seconds const secs = std::chrono::duration_cast<std::chrono::seconds>(time);
  header.Seconds = secs.count();

  T125usec const framecounter = std::chrono::duration_cast<T125usec>(time - secs);
  header.FrameCounter = framecounter.count();

  header.T4ns = (time - secs - framecounter).count();
}

// Set the time since the beginning of the year.

inline
void setDFHYearTime(fine_time const& time, bdx::DataFrameHeader& header)
{
  days const gregorian = std::chrono::duration_cast<days>(time);

  setDFHDays(gregorian.count(), header);

  setDFHDayTime(time - gregorian, header);
}

// Set the time since Jan 1 2000.

inline
void setDFHFullTime(fine_time const& time, bdx::DataFrameHeader& header)
{
  std::chrono::seconds const s = std::chrono::duration_cast<std::chrono::seconds>(time);

  // Please note that boost::posix_time::seconds uses a signed 32-bit integer
  // as internal storage for the time, while std::chrono::seconds uses a
  // least64. The following line will silently fail if `time` refers to a time
  // point which is after about the year 2068.
  // A better solution shall be found before that date.
  boost::posix_time::ptime const t(
      boost::gregorian::date(2000, boost::date_time::Jan, 1),
      boost::posix_time::seconds(s.count()));

  boost::gregorian::date const d = t.date();

  unsigned int const year = d.year() - 2000;

  setDFHYears(year, header);

  boost::posix_time::ptime const first_of_the_year(
      boost::gregorian::date(d.year(), boost::date_time::Jan, 1));

  std::chrono::seconds const x(
      (t - first_of_the_year).total_seconds());

  fine_time const rest = time - s;

  setDFHYearTime(x + rest, header);
}

inline
TS_t getTimesliceId(DataFrameHeader const& dfh, std::chrono::milliseconds ts_size)
{
  assert(ts_size > std::chrono::milliseconds::zero());
  std::chrono::milliseconds const total_ms =
      std::chrono::duration_cast<std::chrono::milliseconds>(
        getDFHFullTime(dfh));
  return total_ms.count() / ts_size.count();
}

inline
std::size_t maxFrameSize()
{
  // See the dataformat document (WVB_DataFrame.docx):
  // Il numero di DWORD del DF va da 4 (zero campioni) a 67 (4+126/2).
  // sizeof(DWORD) = 4

  return 67 * 4;
}

inline
std::ostream& operator <<(std::ostream& stream, tridas::bdx::DataFrameHeader const& header)
{
  return stream
      // First DWORD: Sync and ID
      << " == Sync & ID  ==\n\n"
      << "SyncBytes:     "  << header.SyncBytes << '\n'
      << "TowerID:       "  << header.TowerID   << '\n'
      << "EFCMID:        "  << header.EFCMID    << '\n'
      << "PMTID:         "  << header.PMTID     << '\n'

      // Second and third DWORD: Time
      << "\n ==   Time   ==\n\n"
      << "Years (BCD):   "  << header.Years        << '\n'
      << "Days (BCD):    "  << header.Days         << '\n'
      << "Seconds:       "  << header.Seconds      << '\n'
      << "FrameCounter:  "  << header.FrameCounter << '\n'
      << "T4ns:          "  << header.T4ns         << '\n'

      << "\nYears (human): "  << getDFHYears(header) << '\n'
      << "Days (human) : "  << getDFHDays(header)    << '\n'

      << "\nCentury time in 4 nanoseconds unit: " << getDFHFullTime(header) << '\n'

      // Forth DWORD: Hit info
      << "\n == Hit info ==\n\n"
      << "ZipFlag:       "  << header.ZipFlag      << '\n'
      << "FragFlag:      "  << header.FragFlag     << '\n'
      << "Charge:        "  << header.Charge       << '\n'
      << "FifoFull:      "  << header.FifoFull     << '\n'
      << "NDataSamples:  "  << header.NDataSamples << '\n'

      << "\nPayload size:  "  << getDFHPayloadSize(header) << '\n';
}

} // ns bdx
} // ns tridas

inline
std::ostream& operator <<(std::ostream& stream, tridas::bdx::TEHeaderInfo const& header)
{
  return stream
      << "EventTag:         " << header.EventTag    << '\n'
      << "EventID:          " << header.EventID     << '\n'
      << "Event length:     " << header.EventL      << '\n'
      << "Number of hits:   " << header.nHit        << '\n'
      << "Start time [4ns]: " << header.StartTime   << '\n'
      << "Completed:        " << header.TSCompleted << '\n';
}

inline
std::ostream& operator <<(std::ostream& stream, tridas::bdx::TimeSliceHeader const& header)
{
  return stream
      << "TS ID:            " << header.TS_ID   << '\n'
      << "Number of events: " << header.NEvents << '\n'
      << "Time Slice size:  " << header.TS_size << '\n';
}

inline
std::ostream& operator <<(std::ostream& stream, tridas::bdx::PTHeader const& header)
{
  return stream
      << "Run number:                 " << header.run_number           << '\n'
      << "File number:                " << header.file_number          << '\n'
      << "Run start time (Unix time): " << header.run_start_time       << '\n'
      << "Datacard size:              " << header.datacard_size        << '\n'
      << "Number of events:           " << header.number_of_events     << '\n'
      << "Number of time slices:      " << header.number_of_timeslices << '\n'
      << "File size:                  " << header.effective_file_size  << '\n';
}
#endif
