/*
 * fa250Hit.h
 *
 *  Created on: Jan 25, 2016
 *      Author: celentan
 */

#ifndef FAHIT_H_
#define FAHIT_H_

#include <JANA/JObject.h>
#include <JANA/JFactory.h>
#include <TT/TranslationTable.h>
#include <JANA/JObject.h>


//base class for all fadc hits. This should support:
//Waveboard hit
//fa250 hit - mode 1
//fa250 hit - mode 7
class faHit : public JObject{
public:


	TranslationTable::csc_t m_channel;
	//int trigger;
	//uint64_t timestamp;



};

#endif /* FA250HIT_H_ */
