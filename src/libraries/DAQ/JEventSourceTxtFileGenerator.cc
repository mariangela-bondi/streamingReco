// C++ headers
#include <string>
using namespace std;

// reco headers
#include <DAQ/JEventSourceTxtFileGenerator.h>

std::string JEventSourceTxtFileGenerator::GetType(void) const {
	return "TxtFile";
}

std::string JEventSourceTxtFileGenerator::GetDescription(void) const {
	return "TRIDAS post trigger file";
}

JEventSource* JEventSourceTxtFileGenerator::MakeJEventSource(std::string source) {

	int m_isMC = 0;
	if (m_isMC == 0) {
		std::cout<< "JEventSourceTxtFileGenerator::MakeJEventSource for DATA " << std::endl;
		return new JEventSourceTxtFile(source, mApplication );
	} else {
		std::cerr << "MC - TRIDAS format not yet supported!!" << std::endl;
		throw JException("Failed to open MC TRIDAS file - no MC support yet");
	}
}

//---------------------------------
// CheckOpenable
//---------------------------------
double JEventSourceTxtFileGenerator::CheckOpenable(string source) {
	// This should return a value between 0 and 1 inclusive
	// with 1 indicating it definitely can read events from
	// the specified source and 0 meaning it definitely can't.
	// Typically, this will just check the file suffix.

	if (source.find("txt") != std::string::npos) {
		std::cout << "JEventSourceTxtFileGenerator: source name " << source << " contains \"txt\" substring. Open it" << std::endl;
		return 1.0;
	} else {
		std::cout << "JEventSourceTxtFileGenerator failed on source " << source << std::endl;
		return 0.0;
	}
}

