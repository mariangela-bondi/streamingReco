#ifndef _JEventSourceGenerator_TxtFile_
#define _JEventSourceGenerator_TxtFile_

// JANA headers
#include "JANA/JEventSourceGeneratorT.h"
#include "JEventSource_TxtFile.h"

class JEventSourceTxtFileGenerator: public JEventSourceGenerator{
	public:
		JEventSourceTxtFileGenerator(){}
		virtual ~JEventSourceTxtFileGenerator(){}

		virtual std::string GetType(void) const;
		virtual std::string GetDescription(void) const;
		virtual JEventSource* MakeJEventSource( std::string source);
		virtual double CheckOpenable( std::string source );
};

#endif // _JEventSourceGenerator_TxtFile_

