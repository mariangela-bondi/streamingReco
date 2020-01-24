// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME srcdIexternaldIRootSpydIsrcdIdOdOLinux_x86_64dIRootSpydIDialog_SelectHists_Dict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "src/external/RootSpy/src/RootSpy/Dialog_SelectHists.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void delete_Dialog_SelectHists(void *p);
   static void deleteArray_Dialog_SelectHists(void *p);
   static void destruct_Dialog_SelectHists(void *p);
   static void streamer_Dialog_SelectHists(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Dialog_SelectHists*)
   {
      ::Dialog_SelectHists *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Dialog_SelectHists >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Dialog_SelectHists", ::Dialog_SelectHists::Class_Version(), "RootSpy/src/RootSpy/Dialog_SelectHists.h", 37,
                  typeid(::Dialog_SelectHists), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Dialog_SelectHists::Dictionary, isa_proxy, 16,
                  sizeof(::Dialog_SelectHists) );
      instance.SetDelete(&delete_Dialog_SelectHists);
      instance.SetDeleteArray(&deleteArray_Dialog_SelectHists);
      instance.SetDestructor(&destruct_Dialog_SelectHists);
      instance.SetStreamerFunc(&streamer_Dialog_SelectHists);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Dialog_SelectHists*)
   {
      return GenerateInitInstanceLocal((::Dialog_SelectHists*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Dialog_SelectHists*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr Dialog_SelectHists::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Dialog_SelectHists::Class_Name()
{
   return "Dialog_SelectHists";
}

//______________________________________________________________________________
const char *Dialog_SelectHists::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Dialog_SelectHists*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Dialog_SelectHists::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Dialog_SelectHists*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Dialog_SelectHists::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Dialog_SelectHists*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Dialog_SelectHists::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Dialog_SelectHists*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void Dialog_SelectHists::Streamer(TBuffer &R__b)
{
   // Stream an object of class Dialog_SelectHists.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TGMainFrame::Streamer(R__b);
      R__b >> timer;
      R__b >> sleep_time;
      R__b >> last_called;
      R__b >> last_ping_time;
      R__b >> last_hist_time;
      {
         vector<hid_t> &R__stl =  last_hids;
         R__stl.clear();
         TClass *R__tcl1 = TBuffer::GetClass(typeid(class hid_t));
         if (R__tcl1==0) {
            Error("last_hids streamer","Missing the TClass object for class hid_t!");
            return;
         }
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            hid_t R__t;
            R__b.StreamObject(&R__t,R__tcl1);
            R__stl.push_back(R__t);
         }
      }
      {
         map<hid_t,TGListTreeItem*> &R__stl =  server_items;
         R__stl.clear();
         TClass *R__tcl1 = TBuffer::GetClass(typeid(class hid_t));
         if (R__tcl1==0) {
            Error("server_items streamer","Missing the TClass object for class hid_t!");
            return;
         }
         TClass *R__tcl2 = TBuffer::GetClass(typeid(class TGListTreeItem *));
         if (R__tcl2==0) {
            Error("server_items streamer","Missing the TClass object for class TGListTreeItem *!");
            return;
         }
         int R__i, R__n;
         R__b >> R__n;
         for (R__i = 0; R__i < R__n; R__i++) {
            hid_t R__t;
            R__b.StreamObject(&R__t,R__tcl1);
            TGListTreeItem* R__t2;
            if (R__b.GetInfo() && R__b.GetInfo()->GetOldVersion()<=3) {
               R__ASSERT(0);// TGListTreeItem is abstract. We assume that older file could not be produced using this streaming method.
            } else {
               R__t2 = (TGListTreeItem*)R__b.ReadObjectAny(R__tcl2);
            }
            typedef class hid_t Value_t;
            std::pair<Value_t const, class TGListTreeItem * > R__t3(R__t,R__t2);
            R__stl.insert(R__t3);
         }
      }
      {
         map<hid_t,TGListTreeItem*> &R__stl =  hist_items;
         R__stl.clear();
         TClass *R__tcl1 = TBuffer::GetClass(typeid(class hid_t));
         if (R__tcl1==0) {
            Error("hist_items streamer","Missing the TClass object for class hid_t!");
            return;
         }
         TClass *R__tcl2 = TBuffer::GetClass(typeid(class TGListTreeItem *));
         if (R__tcl2==0) {
            Error("hist_items streamer","Missing the TClass object for class TGListTreeItem *!");
            return;
         }
         int R__i, R__n;
         R__b >> R__n;
         for (R__i = 0; R__i < R__n; R__i++) {
            hid_t R__t;
            R__b.StreamObject(&R__t,R__tcl1);
            TGListTreeItem* R__t2;
            if (R__b.GetInfo() && R__b.GetInfo()->GetOldVersion()<=3) {
               R__ASSERT(0);// TGListTreeItem is abstract. We assume that older file could not be produced using this streaming method.
            } else {
               R__t2 = (TGListTreeItem*)R__b.ReadObjectAny(R__tcl2);
            }
            typedef class hid_t Value_t;
            std::pair<Value_t const, class TGListTreeItem * > R__t3(R__t,R__t2);
            R__stl.insert(R__t3);
         }
      }
      {
         map<string,bool> &R__stl =  item_checked;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         for (R__i = 0; R__i < R__n; R__i++) {
            string R__t;
            {TString R__str;
             R__str.Streamer(R__b);
             R__t = R__str.Data();}
            bool R__t2;
            R__b >> R__t2;
            typedef class std::__cxx11::basic_string<char> Value_t;
            std::pair<Value_t const, _Bool > R__t3(R__t,R__t2);
            R__stl.insert(R__t3);
         }
      }
      R__b >> last_type_filters;
      R__b >> bFilterTH1;
      R__b >> bFilterTH2;
      R__b >> bFilterTProfile;
      R__b >> bFilterMacro;
      R__b >> canvas;
      R__b >> listTree;
      R__b >> viewByObject;
      R__b >> viewByServer;
      R__b >> filterTextBox;
      R__b >> folder_t;
      R__b >> ofolder_t;
      R__b >> redx_t;
      R__b >> package_t;
      R__b >> h1_s;
      R__b >> h1_t;
      R__b >> h2_s;
      R__b >> h2_t;
      R__b >> h3_s;
      R__b >> h3_t;
      R__b >> profile_t;
      R__b >> pack_t;
      R__b >> hdisk_t;
      R__b >> checked_t;
      R__b >> unchecked_t;
      { TString R__str; R__str.Streamer(R__b); filter_str = R__str.Data(); }
      { TString R__str; R__str.Streamer(R__b); last_filter_str = R__str.Data(); }
      R__b.CheckByteCount(R__s, R__c, Dialog_SelectHists::IsA());
   } else {
      R__c = R__b.WriteVersion(Dialog_SelectHists::IsA(), kTRUE);
      TGMainFrame::Streamer(R__b);
      R__b << timer;
      R__b << sleep_time;
      R__b << last_called;
      R__b << last_ping_time;
      R__b << last_hist_time;
      {
         vector<hid_t> &R__stl =  last_hids;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
         TClass *R__tcl1 = TBuffer::GetClass(typeid(class hid_t));
         if (R__tcl1==0) {
            Error("last_hids streamer","Missing the TClass object for class hid_t!");
            return;
         }
            vector<hid_t>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            R__b.StreamObject((hid_t*)&(*R__k),R__tcl1);
            }
         }
      }
      {
         map<hid_t,TGListTreeItem*> &R__stl =  server_items;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
         TClass *R__tcl1 = TBuffer::GetClass(typeid(class hid_t));
         if (R__tcl1==0) {
            Error("server_items streamer","Missing the TClass object for class hid_t!");
            return;
         }
         TClass *R__tcl2 = TBuffer::GetClass(typeid(class TGListTreeItem *));
         if (R__tcl2==0) {
            Error("server_itemsstreamer","Missing the TClass object for class TGListTreeItem *!");
            return;
         }
            map<hid_t,TGListTreeItem*>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            R__b.StreamObject((hid_t*)&((*R__k).first ),R__tcl1);
            R__b.WriteObjectAny(((*R__k).second),R__tcl2);
            }
         }
      }
      {
         map<hid_t,TGListTreeItem*> &R__stl =  hist_items;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
         TClass *R__tcl1 = TBuffer::GetClass(typeid(class hid_t));
         if (R__tcl1==0) {
            Error("hist_items streamer","Missing the TClass object for class hid_t!");
            return;
         }
         TClass *R__tcl2 = TBuffer::GetClass(typeid(class TGListTreeItem *));
         if (R__tcl2==0) {
            Error("hist_itemsstreamer","Missing the TClass object for class TGListTreeItem *!");
            return;
         }
            map<hid_t,TGListTreeItem*>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            R__b.StreamObject((hid_t*)&((*R__k).first ),R__tcl1);
            R__b.WriteObjectAny(((*R__k).second),R__tcl2);
            }
         }
      }
      {
         map<string,bool> &R__stl =  item_checked;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            map<string,bool>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            {TString R__str(((*R__k).first ).c_str());
             R__str.Streamer(R__b);};
            R__b << ((*R__k).second);
            }
         }
      }
      R__b << last_type_filters;
      R__b << bFilterTH1;
      R__b << bFilterTH2;
      R__b << bFilterTProfile;
      R__b << bFilterMacro;
      R__b << canvas;
      R__b << listTree;
      R__b << viewByObject;
      R__b << viewByServer;
      R__b << filterTextBox;
      R__b << folder_t;
      R__b << ofolder_t;
      R__b << redx_t;
      R__b << package_t;
      R__b << h1_s;
      R__b << h1_t;
      R__b << h2_s;
      R__b << h2_t;
      R__b << h3_s;
      R__b << h3_t;
      R__b << profile_t;
      R__b << pack_t;
      R__b << hdisk_t;
      R__b << checked_t;
      R__b << unchecked_t;
      { TString R__str = filter_str.c_str(); R__str.Streamer(R__b);}
      { TString R__str = last_filter_str.c_str(); R__str.Streamer(R__b);}
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Dialog_SelectHists(void *p) {
      delete ((::Dialog_SelectHists*)p);
   }
   static void deleteArray_Dialog_SelectHists(void *p) {
      delete [] ((::Dialog_SelectHists*)p);
   }
   static void destruct_Dialog_SelectHists(void *p) {
      typedef ::Dialog_SelectHists current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_Dialog_SelectHists(TBuffer &buf, void *obj) {
      ((::Dialog_SelectHists*)obj)->::Dialog_SelectHists::Streamer(buf);
   }
} // end of namespace ROOT for class ::Dialog_SelectHists

namespace ROOT {
   static TClass *vectorlEhid_tgR_Dictionary();
   static void vectorlEhid_tgR_TClassManip(TClass*);
   static void *new_vectorlEhid_tgR(void *p = 0);
   static void *newArray_vectorlEhid_tgR(Long_t size, void *p);
   static void delete_vectorlEhid_tgR(void *p);
   static void deleteArray_vectorlEhid_tgR(void *p);
   static void destruct_vectorlEhid_tgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<hid_t>*)
   {
      vector<hid_t> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<hid_t>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<hid_t>", -2, "vector", 339,
                  typeid(vector<hid_t>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEhid_tgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<hid_t>) );
      instance.SetNew(&new_vectorlEhid_tgR);
      instance.SetNewArray(&newArray_vectorlEhid_tgR);
      instance.SetDelete(&delete_vectorlEhid_tgR);
      instance.SetDeleteArray(&deleteArray_vectorlEhid_tgR);
      instance.SetDestructor(&destruct_vectorlEhid_tgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<hid_t> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<hid_t>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEhid_tgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<hid_t>*)0x0)->GetClass();
      vectorlEhid_tgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEhid_tgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEhid_tgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<hid_t> : new vector<hid_t>;
   }
   static void *newArray_vectorlEhid_tgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<hid_t>[nElements] : new vector<hid_t>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEhid_tgR(void *p) {
      delete ((vector<hid_t>*)p);
   }
   static void deleteArray_vectorlEhid_tgR(void *p) {
      delete [] ((vector<hid_t>*)p);
   }
   static void destruct_vectorlEhid_tgR(void *p) {
      typedef vector<hid_t> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<hid_t>

namespace ROOT {
   static TClass *maplEstringcOboolgR_Dictionary();
   static void maplEstringcOboolgR_TClassManip(TClass*);
   static void *new_maplEstringcOboolgR(void *p = 0);
   static void *newArray_maplEstringcOboolgR(Long_t size, void *p);
   static void delete_maplEstringcOboolgR(void *p);
   static void deleteArray_maplEstringcOboolgR(void *p);
   static void destruct_maplEstringcOboolgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,bool>*)
   {
      map<string,bool> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,bool>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,bool>", -2, "map", 100,
                  typeid(map<string,bool>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOboolgR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,bool>) );
      instance.SetNew(&new_maplEstringcOboolgR);
      instance.SetNewArray(&newArray_maplEstringcOboolgR);
      instance.SetDelete(&delete_maplEstringcOboolgR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOboolgR);
      instance.SetDestructor(&destruct_maplEstringcOboolgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,bool> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<string,bool>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOboolgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<string,bool>*)0x0)->GetClass();
      maplEstringcOboolgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOboolgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOboolgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,bool> : new map<string,bool>;
   }
   static void *newArray_maplEstringcOboolgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,bool>[nElements] : new map<string,bool>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOboolgR(void *p) {
      delete ((map<string,bool>*)p);
   }
   static void deleteArray_maplEstringcOboolgR(void *p) {
      delete [] ((map<string,bool>*)p);
   }
   static void destruct_maplEstringcOboolgR(void *p) {
      typedef map<string,bool> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<string,bool>

namespace ROOT {
   static TClass *maplEhid_tcOTGListTreeItemmUgR_Dictionary();
   static void maplEhid_tcOTGListTreeItemmUgR_TClassManip(TClass*);
   static void *new_maplEhid_tcOTGListTreeItemmUgR(void *p = 0);
   static void *newArray_maplEhid_tcOTGListTreeItemmUgR(Long_t size, void *p);
   static void delete_maplEhid_tcOTGListTreeItemmUgR(void *p);
   static void deleteArray_maplEhid_tcOTGListTreeItemmUgR(void *p);
   static void destruct_maplEhid_tcOTGListTreeItemmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<hid_t,TGListTreeItem*>*)
   {
      map<hid_t,TGListTreeItem*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<hid_t,TGListTreeItem*>));
      static ::ROOT::TGenericClassInfo 
         instance("map<hid_t,TGListTreeItem*>", -2, "map", 100,
                  typeid(map<hid_t,TGListTreeItem*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEhid_tcOTGListTreeItemmUgR_Dictionary, isa_proxy, 0,
                  sizeof(map<hid_t,TGListTreeItem*>) );
      instance.SetNew(&new_maplEhid_tcOTGListTreeItemmUgR);
      instance.SetNewArray(&newArray_maplEhid_tcOTGListTreeItemmUgR);
      instance.SetDelete(&delete_maplEhid_tcOTGListTreeItemmUgR);
      instance.SetDeleteArray(&deleteArray_maplEhid_tcOTGListTreeItemmUgR);
      instance.SetDestructor(&destruct_maplEhid_tcOTGListTreeItemmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<hid_t,TGListTreeItem*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<hid_t,TGListTreeItem*>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEhid_tcOTGListTreeItemmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<hid_t,TGListTreeItem*>*)0x0)->GetClass();
      maplEhid_tcOTGListTreeItemmUgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEhid_tcOTGListTreeItemmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEhid_tcOTGListTreeItemmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<hid_t,TGListTreeItem*> : new map<hid_t,TGListTreeItem*>;
   }
   static void *newArray_maplEhid_tcOTGListTreeItemmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<hid_t,TGListTreeItem*>[nElements] : new map<hid_t,TGListTreeItem*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEhid_tcOTGListTreeItemmUgR(void *p) {
      delete ((map<hid_t,TGListTreeItem*>*)p);
   }
   static void deleteArray_maplEhid_tcOTGListTreeItemmUgR(void *p) {
      delete [] ((map<hid_t,TGListTreeItem*>*)p);
   }
   static void destruct_maplEhid_tcOTGListTreeItemmUgR(void *p) {
      typedef map<hid_t,TGListTreeItem*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<hid_t,TGListTreeItem*>

namespace {
  void TriggerDictionaryInitialization_Dialog_SelectHists_Dict_Impl() {
    static const char* headers[] = {
"src/external/RootSpy/src/RootSpy/Dialog_SelectHists.h",
0
    };
    static const char* includePaths[] = {
"/project/Gruppo3/fiber6/streaming/JANA2/src/lib",
"/project/Gruppo3/fiber6/streaming/boost/include",
"/project/Gruppo3/fiber6/apps/jlab_software_20160107/2.0/Linux_CentOS7.6.1810-x86_64-gcc8.2.0/ccdb/ccdb-1.06.00/include",
"/project/Gruppo3/fiber6/apps/jlab_software_20160107/2.0/Linux_CentOS7.6.1810-x86_64-gcc8.2.0/root/6.14.04/include",
"/auto_data/fiber6/streaming/streamingReco/src/external",
"/auto_data/fiber6/streaming/streamingReco/src/libraries",
"/auto_data/fiber6/streaming/streamingReco/src/plugins",
"/auto_data/fiber6/streaming/streamingReco",
"/auto_data/fiber6/streaming/streamingReco/src/external/cMsg-3.6/src/regexp",
"/auto_data/fiber6/streaming/streamingReco/src/external/cMsg-3.6/src/libsrc",
"/auto_data/fiber6/streaming/streamingReco/src/external/cMsg-3.6/src/libsrc++",
"/auto_data/fiber6/streaming/streamingReco/src/external/RootSpy/src/libRootSpy",
"/auto_data/fiber6/streaming/streamingReco/src/external/RootSpy/src/libRootSpy-client",
"/auto_data/fiber6/apps/jlab_software_20160107/2.0/Linux_CentOS7.3.1611-x86_64-gcc8.2.0/root/6.14.04/include",
"/auto_data/fiber6/streaming/streamingReco/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "Dialog_SelectHists_Dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$src/external/RootSpy/src/RootSpy/Dialog_SelectHists.h")))  Dialog_SelectHists;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "Dialog_SelectHists_Dict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "src/external/RootSpy/src/RootSpy/Dialog_SelectHists.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"Dialog_SelectHists", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("Dialog_SelectHists_Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_Dialog_SelectHists_Dict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_Dialog_SelectHists_Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_Dialog_SelectHists_Dict() {
  TriggerDictionaryInitialization_Dialog_SelectHists_Dict_Impl();
}
