#ifndef _JEventSourceGenerator_PTFile_
#define _JEventSourceGenerator_PTFile_

// JANA headers
#include "JANA/JEventSourceGeneratorT.h"
#include "JEventSource_PTFile.h"

class JEventSourcePTFileGenerator: public JEventSourceGenerator{
	public:
		JEventSourcePTFileGenerator(){}
		virtual ~JEventSourcePTFileGenerator(){}

		virtual std::string GetType(void) const;
		virtual std::string GetDescription(void) const;
		virtual JEventSource* MakeJEventSource( std::string source);
		virtual double CheckOpenable( std::string source );
};

#endif // _JEventSourceGenerator_PTFile_

