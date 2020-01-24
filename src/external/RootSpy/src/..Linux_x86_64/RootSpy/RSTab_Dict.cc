// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME srcdIexternaldIRootSpydIsrcdIdOdOLinux_x86_64dIRootSpydIRSTab_Dict

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
#include "src/external/RootSpy/src/RootSpy/RSTab.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_RSTab(void *p = 0);
   static void *newArray_RSTab(Long_t size, void *p);
   static void delete_RSTab(void *p);
   static void deleteArray_RSTab(void *p);
   static void destruct_RSTab(void *p);
   static void streamer_RSTab(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RSTab*)
   {
      ::RSTab *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RSTab >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RSTab", ::RSTab::Class_Version(), "RootSpy/src/RootSpy/RSTab.h", 35,
                  typeid(::RSTab), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::RSTab::Dictionary, isa_proxy, 16,
                  sizeof(::RSTab) );
      instance.SetNew(&new_RSTab);
      instance.SetNewArray(&newArray_RSTab);
      instance.SetDelete(&delete_RSTab);
      instance.SetDeleteArray(&deleteArray_RSTab);
      instance.SetDestructor(&destruct_RSTab);
      instance.SetStreamerFunc(&streamer_RSTab);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RSTab*)
   {
      return GenerateInitInstanceLocal((::RSTab*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::RSTab*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr RSTab::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RSTab::Class_Name()
{
   return "RSTab";
}

//______________________________________________________________________________
const char *RSTab::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RSTab*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RSTab::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RSTab*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RSTab::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RSTab*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RSTab::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RSTab*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void RSTab::Streamer(TBuffer &R__b)
{
   // Stream an object of class RSTab.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      R__b >> fTab;
      R__b >> fTabMain;
      R__b >> fTabMainLeft;
      R__b >> lServer;
      R__b >> lType;
      R__b >> lHistogram;
      R__b >> lReceived;
      R__b >> bViewMacro;
      R__b >> bViewGuidance;
      R__b >> canvas;
      { TString R__str; R__str.Streamer(R__b); title = R__str.Data(); }
      { TString R__str; R__str.Streamer(R__b); config = R__str.Data(); }
      {
         list<string> &R__stl =  hnamepaths;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         for (R__i = 0; R__i < R__n; R__i++) {
            string R__t;
            {TString R__str;
             R__str.Streamer(R__b);
             R__t = R__str.Data();}
            R__stl.push_back(R__t);
         }
      }
      R__b >> currently_displayed;
      R__b >> currently_displayed_modified;
      { TString R__str; R__str.Streamer(R__b); currently_displayed_hnamepath = R__str.Data(); }
      R__b >> last_update;
      R__b >> last_request_sent;
      { TString R__str; R__str.Streamer(R__b); last_request_hnamepath = R__str.Data(); }
      R__b.CheckByteCount(R__s, R__c, RSTab::IsA());
   } else {
      R__c = R__b.WriteVersion(RSTab::IsA(), kTRUE);
      R__b << fTab;
      R__b << fTabMain;
      R__b << fTabMainLeft;
      R__b << lServer;
      R__b << lType;
      R__b << lHistogram;
      R__b << lReceived;
      R__b << bViewMacro;
      R__b << bViewGuidance;
      R__b << canvas;
      { TString R__str = title.c_str(); R__str.Streamer(R__b);}
      { TString R__str = config.c_str(); R__str.Streamer(R__b);}
      {
         list<string> &R__stl =  hnamepaths;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            list<string>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            {TString R__str((*R__k).c_str());
             R__str.Streamer(R__b);};
            }
         }
      }
      R__b << currently_displayed;
      R__b << currently_displayed_modified;
      { TString R__str = currently_displayed_hnamepath.c_str(); R__str.Streamer(R__b);}
      R__b << last_update;
      R__b << last_request_sent;
      { TString R__str = last_request_hnamepath.c_str(); R__str.Streamer(R__b);}
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RSTab(void *p) {
      return  p ? new(p) ::RSTab : new ::RSTab;
   }
   static void *newArray_RSTab(Long_t nElements, void *p) {
      return p ? new(p) ::RSTab[nElements] : new ::RSTab[nElements];
   }
   // Wrapper around operator delete
   static void delete_RSTab(void *p) {
      delete ((::RSTab*)p);
   }
   static void deleteArray_RSTab(void *p) {
      delete [] ((::RSTab*)p);
   }
   static void destruct_RSTab(void *p) {
      typedef ::RSTab current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_RSTab(TBuffer &buf, void *obj) {
      ((::RSTab*)obj)->::RSTab::Streamer(buf);
   }
} // end of namespace ROOT for class ::RSTab

namespace ROOT {
   static TClass *listlEstringgR_Dictionary();
   static void listlEstringgR_TClassManip(TClass*);
   static void *new_listlEstringgR(void *p = 0);
   static void *newArray_listlEstringgR(Long_t size, void *p);
   static void delete_listlEstringgR(void *p);
   static void deleteArray_listlEstringgR(void *p);
   static void destruct_listlEstringgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const list<string>*)
   {
      list<string> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(list<string>));
      static ::ROOT::TGenericClassInfo 
         instance("list<string>", -2, "list", 563,
                  typeid(list<string>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &listlEstringgR_Dictionary, isa_proxy, 0,
                  sizeof(list<string>) );
      instance.SetNew(&new_listlEstringgR);
      instance.SetNewArray(&newArray_listlEstringgR);
      instance.SetDelete(&delete_listlEstringgR);
      instance.SetDeleteArray(&deleteArray_listlEstringgR);
      instance.SetDestructor(&destruct_listlEstringgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< list<string> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const list<string>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *listlEstringgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const list<string>*)0x0)->GetClass();
      listlEstringgR_TClassManip(theClass);
   return theClass;
   }

   static void listlEstringgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_listlEstringgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) list<string> : new list<string>;
   }
   static void *newArray_listlEstringgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) list<string>[nElements] : new list<string>[nElements];
   }
   // Wrapper around operator delete
   static void delete_listlEstringgR(void *p) {
      delete ((list<string>*)p);
   }
   static void deleteArray_listlEstringgR(void *p) {
      delete [] ((list<string>*)p);
   }
   static void destruct_listlEstringgR(void *p) {
      typedef list<string> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class list<string>

namespace {
  void TriggerDictionaryInitialization_RSTab_Dict_Impl() {
    static const char* headers[] = {
"src/external/RootSpy/src/RootSpy/RSTab.h",
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
#line 1 "RSTab_Dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$src/external/RootSpy/src/RootSpy/RSTab.h")))  RSTab;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "RSTab_Dict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "src/external/RootSpy/src/RootSpy/RSTab.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"RSTab", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("RSTab_Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_RSTab_Dict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_RSTab_Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_RSTab_Dict() {
  TriggerDictionaryInitialization_RSTab_Dict_Impl();
}
