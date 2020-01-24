// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME srcdIexternaldIRootSpydIsrcdIdOdOLinux_x86_64dIRootSpydIDialog_IndivHists_Dict

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
#include "src/external/RootSpy/src/RootSpy/Dialog_IndivHists.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void delete_Dialog_IndivHists(void *p);
   static void deleteArray_Dialog_IndivHists(void *p);
   static void destruct_Dialog_IndivHists(void *p);
   static void streamer_Dialog_IndivHists(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Dialog_IndivHists*)
   {
      ::Dialog_IndivHists *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Dialog_IndivHists >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Dialog_IndivHists", ::Dialog_IndivHists::Class_Version(), "RootSpy/src/RootSpy/Dialog_IndivHists.h", 31,
                  typeid(::Dialog_IndivHists), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Dialog_IndivHists::Dictionary, isa_proxy, 16,
                  sizeof(::Dialog_IndivHists) );
      instance.SetDelete(&delete_Dialog_IndivHists);
      instance.SetDeleteArray(&deleteArray_Dialog_IndivHists);
      instance.SetDestructor(&destruct_Dialog_IndivHists);
      instance.SetStreamerFunc(&streamer_Dialog_IndivHists);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Dialog_IndivHists*)
   {
      return GenerateInitInstanceLocal((::Dialog_IndivHists*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Dialog_IndivHists*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr Dialog_IndivHists::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Dialog_IndivHists::Class_Name()
{
   return "Dialog_IndivHists";
}

//______________________________________________________________________________
const char *Dialog_IndivHists::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Dialog_IndivHists*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Dialog_IndivHists::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Dialog_IndivHists*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Dialog_IndivHists::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Dialog_IndivHists*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Dialog_IndivHists::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Dialog_IndivHists*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void Dialog_IndivHists::Streamer(TBuffer &R__b)
{
   // Stream an object of class Dialog_IndivHists.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TGMainFrame::Streamer(R__b);
      { TString R__str; R__str.Streamer(R__b); hnamepath = R__str.Data(); }
      R__b >> last_enable_divided;
      R__b >> timer;
      R__b >> requested;
      R__b >> servers_changed;
      R__b >> num_servers;
      R__b >> canvas;
      R__b >> gridlines;
      R__b >> tickmarks;
      R__b >> plainbut;
      R__b >> combinedbut;
      R__b >> dividedbut;
      R__b >> verticalframe;
      void *ptr_displaystyle = (void*)&displaystyle;
      R__b >> *reinterpret_cast<Int_t*>(ptr_displaystyle);
      R__b >> tickstyle;
      R__b >> gridstyle;
      R__b.CheckByteCount(R__s, R__c, Dialog_IndivHists::IsA());
   } else {
      R__c = R__b.WriteVersion(Dialog_IndivHists::IsA(), kTRUE);
      TGMainFrame::Streamer(R__b);
      { TString R__str = hnamepath.c_str(); R__str.Streamer(R__b);}
      R__b << last_enable_divided;
      R__b << timer;
      R__b << requested;
      R__b << servers_changed;
      R__b << num_servers;
      R__b << canvas;
      R__b << gridlines;
      R__b << tickmarks;
      R__b << plainbut;
      R__b << combinedbut;
      R__b << dividedbut;
      R__b << verticalframe;
      R__b << (Int_t)displaystyle;
      R__b << tickstyle;
      R__b << gridstyle;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Dialog_IndivHists(void *p) {
      delete ((::Dialog_IndivHists*)p);
   }
   static void deleteArray_Dialog_IndivHists(void *p) {
      delete [] ((::Dialog_IndivHists*)p);
   }
   static void destruct_Dialog_IndivHists(void *p) {
      typedef ::Dialog_IndivHists current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_Dialog_IndivHists(TBuffer &buf, void *obj) {
      ((::Dialog_IndivHists*)obj)->::Dialog_IndivHists::Streamer(buf);
   }
} // end of namespace ROOT for class ::Dialog_IndivHists

namespace {
  void TriggerDictionaryInitialization_Dialog_IndivHists_Dict_Impl() {
    static const char* headers[] = {
"src/external/RootSpy/src/RootSpy/Dialog_IndivHists.h",
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
#line 1 "Dialog_IndivHists_Dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$src/external/RootSpy/src/RootSpy/Dialog_IndivHists.h")))  Dialog_IndivHists;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "Dialog_IndivHists_Dict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "src/external/RootSpy/src/RootSpy/Dialog_IndivHists.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"Dialog_IndivHists", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("Dialog_IndivHists_Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_Dialog_IndivHists_Dict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_Dialog_IndivHists_Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_Dialog_IndivHists_Dict() {
  TriggerDictionaryInitialization_Dialog_IndivHists_Dict_Impl();
}
