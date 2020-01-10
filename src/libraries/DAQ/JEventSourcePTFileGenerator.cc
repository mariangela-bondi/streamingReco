// C++ headers
#include <string>
using namespace std;

// reco headers
#include <DAQ/JEventSourcePTFileGenerator.h>

std::string JEventSourcePTFileGenerator::GetType(void) const {
	return "PTFile";
}

std::string JEventSourcePTFileGenerator::GetDescription(void) const {
	return "TRIDAS post trigger file";
}

JEventSource* JEventSourcePTFileGenerator::MakeJEventSource(std::string source) {

	int m_isMC = 0;
	if (m_isMC == 0) {
		jout<< "JEventSourcePTFileGenerator::MakeJEventSource for DATA " << endl;
		return new JEventSourcePTFile(source, mApplication );
	} else {
		std::cerr << "MC - TRIDAS format not yet supported!!" << std::endl;
		throw JException("Failed to open MC TRIDAS file - no MC support yet");
	}
}

//---------------------------------
// CheckOpenable
//---------------------------------
double JEventSourcePTFileGenerator::CheckOpenable(string source) {
	// This should return a value between 0 and 1 inclusive
	// with 1 indicating it definitely can read events from
	// the specified source and 0 meaning it definitely can't.
	// Typically, this will just check the file suffix.

	if (source.find("pt") != std::string::npos) {
		std::cout << "JEventSourcePTFileGenerator: source name " << source << " contains \"pt\" substring. Open it" << endl;
		return 1.0;
	} else {
		std::cout << "JEventSourcePTFileGenerator failed on source " << source << endl;
		return 0.0;
	}
}

