// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME srcdIexternaldIRootSpydIsrcdIdOdOLinux_x86_64dIRootSpydIDialog_ShowGuidance_Dict

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
#include "src/external/RootSpy/src/RootSpy/Dialog_ShowGuidance.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void delete_Dialog_ShowGuidance(void *p);
   static void deleteArray_Dialog_ShowGuidance(void *p);
   static void destruct_Dialog_ShowGuidance(void *p);
   static void streamer_Dialog_ShowGuidance(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Dialog_ShowGuidance*)
   {
      ::Dialog_ShowGuidance *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Dialog_ShowGuidance >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Dialog_ShowGuidance", ::Dialog_ShowGuidance::Class_Version(), "RootSpy/src/RootSpy/Dialog_ShowGuidance.h", 17,
                  typeid(::Dialog_ShowGuidance), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Dialog_ShowGuidance::Dictionary, isa_proxy, 16,
                  sizeof(::Dialog_ShowGuidance) );
      instance.SetDelete(&delete_Dialog_ShowGuidance);
      instance.SetDeleteArray(&deleteArray_Dialog_ShowGuidance);
      instance.SetDestructor(&destruct_Dialog_ShowGuidance);
      instance.SetStreamerFunc(&streamer_Dialog_ShowGuidance);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Dialog_ShowGuidance*)
   {
      return GenerateInitInstanceLocal((::Dialog_ShowGuidance*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Dialog_ShowGuidance*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr Dialog_ShowGuidance::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Dialog_ShowGuidance::Class_Name()
{
   return "Dialog_ShowGuidance";
}

//______________________________________________________________________________
const char *Dialog_ShowGuidance::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Dialog_ShowGuidance*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Dialog_ShowGuidance::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Dialog_ShowGuidance*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Dialog_ShowGuidance::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Dialog_ShowGuidance*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Dialog_ShowGuidance::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Dialog_ShowGuidance*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void Dialog_ShowGuidance::Streamer(TBuffer &R__b)
{
   // Stream an object of class Dialog_ShowGuidance.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TGMainFrame::Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, Dialog_ShowGuidance::IsA());
   } else {
      R__c = R__b.WriteVersion(Dialog_ShowGuidance::IsA(), kTRUE);
      TGMainFrame::Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Dialog_ShowGuidance(void *p) {
      delete ((::Dialog_ShowGuidance*)p);
   }
   static void deleteArray_Dialog_ShowGuidance(void *p) {
      delete [] ((::Dialog_ShowGuidance*)p);
   }
   static void destruct_Dialog_ShowGuidance(void *p) {
      typedef ::Dialog_ShowGuidance current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_Dialog_ShowGuidance(TBuffer &buf, void *obj) {
      ((::Dialog_ShowGuidance*)obj)->::Dialog_ShowGuidance::Streamer(buf);
   }
} // end of namespace ROOT for class ::Dialog_ShowGuidance

namespace {
  void TriggerDictionaryInitialization_Dialog_ShowGuidance_Dict_Impl() {
    static const char* headers[] = {
"src/external/RootSpy/src/RootSpy/Dialog_ShowGuidance.h",
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
#line 1 "Dialog_ShowGuidance_Dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$src/external/RootSpy/src/RootSpy/Dialog_ShowGuidance.h")))  Dialog_ShowGuidance;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "Dialog_ShowGuidance_Dict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "src/external/RootSpy/src/RootSpy/Dialog_ShowGuidance.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"Dialog_ShowGuidance", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("Dialog_ShowGuidance_Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_Dialog_ShowGuidance_Dict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_Dialog_ShowGuidance_Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_Dialog_ShowGuidance_Dict() {
  TriggerDictionaryInitialization_Dialog_ShowGuidance_Dict_Impl();
}
