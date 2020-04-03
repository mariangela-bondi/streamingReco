// $Id$
//
//    File: JEventProcessor_janaview.h
// Created: Fri Oct  3 08:14:14 EDT 2014
// Creator: davidl (on Darwin harriet.jlab.org 13.4.0 i386)
//

#ifndef _JEventProcessor_janaview_
#define _JEventProcessor_janaview_

#include <set>
using std::set;

#include <TLatex.h>

#include <JANA/JEventProcessor.h>
#include "jv_mainframe.h"

#include <JVFactoryInfo.h>

class JEventProcessor_janaview:public JEventProcessor{
	public:
	
		class CGobj{
			public:
				CGobj(string nametag):nametag(nametag),x1(0.0),y1(0.0),x2(0.0),y2(0.0),rank(0){
					TLatex ltmp(0.0, 0.0, nametag.c_str());
					ltmp.SetTextSizePixels(20);
					ltmp.GetBoundingBox(w, h);
				}
			
				string nametag;
				Float_t x1;
				Float_t y1;
				Float_t x2;
				Float_t y2;
				Float_t ymid;
				UInt_t w;   // width in pixels
				UInt_t h;   // height in pixels
				Int_t rank; // rank
				
				set<CGobj*> callees;
		};
		
		class CGrankprop{
			public:
				CGrankprop(void):totwidth(0),totheight(0){}
				vector<CGobj*> cgobjs;
				Int_t totwidth;  // pixels -- just max box size, no spacing
				Int_t totheight; // pixels -- sum of box heights, no spacing
		};
	
	
		JEventProcessor_janaview();
		~JEventProcessor_janaview();
		const char* className(void){return "JEventProcessor_janaview";}
		
		pthread_mutex_t mutex;
		pthread_cond_t cond;
		std::shared_ptr<const JEvent> event;
		int eventnumber;

		void Lock(void){pthread_mutex_lock(&mutex);}
		void Unlock(void){pthread_mutex_unlock(&mutex);}
		
		void NextEvent(void);
		string MakeNametag(const string &name, const string &tag);
		void GetObjectTypes(vector<JVFactoryInfo> &facinfo);
		void GetAssociatedTo(JObject *jobj, vector<const JObject*> &associatedTo);
		void GetAssociated(JObject *jobj, vector<const JObject*> &associated);
		void MakeCallGraph(string nametag="");

	private:

		virtual void Init(void);
		virtual void Process(const std::shared_ptr<const JEvent>& aEvent);
		virtual void Finish(void);


};

extern JEventProcessor_janaview *JEP;

#endif // _JEventProcessor_janaview_

