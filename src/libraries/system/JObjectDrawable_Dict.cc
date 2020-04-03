// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME srcdIlibrariesdIsystemdIJObjectDrawable_Dict
#define R__NO_DEPRECATION

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

// The generated code does not explicitly qualifies STL entities
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "src/libraries/system/JObjectDrawable.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_JObjectDrawable(void *p = 0);
   static void *newArray_JObjectDrawable(Long_t size, void *p);
   static void delete_JObjectDrawable(void *p);
   static void deleteArray_JObjectDrawable(void *p);
   static void destruct_JObjectDrawable(void *p);
   static void streamer_JObjectDrawable(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::JObjectDrawable*)
   {
      ::JObjectDrawable *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::JObjectDrawable >(0);
      static ::ROOT::TGenericClassInfo 
         instance("JObjectDrawable", ::JObjectDrawable::Class_Version(), "system/JObjectDrawable.h", 20,
                  typeid(::JObjectDrawable), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::JObjectDrawable::Dictionary, isa_proxy, 16,
                  sizeof(::JObjectDrawable) );
      instance.SetNew(&new_JObjectDrawable);
      instance.SetNewArray(&newArray_JObjectDrawable);
      instance.SetDelete(&delete_JObjectDrawable);
      instance.SetDeleteArray(&deleteArray_JObjectDrawable);
      instance.SetDestructor(&destruct_JObjectDrawable);
      instance.SetStreamerFunc(&streamer_JObjectDrawable);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::JObjectDrawable*)
   {
      return GenerateInitInstanceLocal((::JObjectDrawable*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::JObjectDrawable*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr JObjectDrawable::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *JObjectDrawable::Class_Name()
{
   return "JObjectDrawable";
}

//______________________________________________________________________________
const char *JObjectDrawable::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::JObjectDrawable*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int JObjectDrawable::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::JObjectDrawable*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *JObjectDrawable::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::JObjectDrawable*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *JObjectDrawable::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::JObjectDrawable*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void JObjectDrawable::Streamer(TBuffer &R__b)
{
   // Stream an object of class JObjectDrawable.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      R__b.CheckByteCount(R__s, R__c, JObjectDrawable::IsA());
   } else {
      R__c = R__b.WriteVersion(JObjectDrawable::IsA(), kTRUE);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_JObjectDrawable(void *p) {
      return  p ? new(p) ::JObjectDrawable : new ::JObjectDrawable;
   }
   static void *newArray_JObjectDrawable(Long_t nElements, void *p) {
      return p ? new(p) ::JObjectDrawable[nElements] : new ::JObjectDrawable[nElements];
   }
   // Wrapper around operator delete
   static void delete_JObjectDrawable(void *p) {
      delete ((::JObjectDrawable*)p);
   }
   static void deleteArray_JObjectDrawable(void *p) {
      delete [] ((::JObjectDrawable*)p);
   }
   static void destruct_JObjectDrawable(void *p) {
      typedef ::JObjectDrawable current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_JObjectDrawable(TBuffer &buf, void *obj) {
      ((::JObjectDrawable*)obj)->::JObjectDrawable::Streamer(buf);
   }
} // end of namespace ROOT for class ::JObjectDrawable

namespace {
  void TriggerDictionaryInitialization_JObjectDrawable_Dict_Impl() {
    static const char* headers[] = {
"src/libraries/system/JObjectDrawable.h",
0
    };
    static const char* includePaths[] = {
"/Users/celentan/work/streaming/JANA2//src/libraries",
"/System/Volumes/Data/work/jlab_software/2.0/Darwin_macosx10.15-x86_64-clang11.0.0/ccdb/ccdb-1.06.00/include",
"/System/Volumes/Data/work/jlab_software/2.0/Darwin_macosx10.15-x86_64-clang11.0.0/root/6.18.04/include",
"/System/Volumes/Data/work/streaming/streamingReco/src/external",
"/System/Volumes/Data/work/streaming/streamingReco/src/libraries",
"/System/Volumes/Data/work/streaming/streamingReco/src/plugins",
"/System/Volumes/Data/work/streaming/streamingReco",
"/System/Volumes/Data/work/streaming/streamingReco/src/external/cMsg-3.6/src/regexp",
"/System/Volumes/Data/work/streaming/streamingReco/src/external/cMsg-3.6/src/libsrc",
"/System/Volumes/Data/work/streaming/streamingReco/src/external/cMsg-3.6/src/libsrc++",
"/System/Volumes/Data/work/streaming/streamingReco/src/external/RootSpy/src/libRootSpy",
"/System/Volumes/Data/work/streaming/streamingReco/src/external/RootSpy/src/libRootSpy-client",
"/System/Volumes/Data/work/jlab_software/2.0/Darwin_macosx10.14-x86_64-clang10.0.0/root/6.18.04/include",
"/System/Volumes/Data/work/streaming/streamingReco/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "JObjectDrawable_Dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$src/libraries/system/JObjectDrawable.h")))  JObjectDrawable;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "JObjectDrawable_Dict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "src/libraries/system/JObjectDrawable.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"JObjectDrawable", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("JObjectDrawable_Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_JObjectDrawable_Dict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_JObjectDrawable_Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_JObjectDrawable_Dict() {
  TriggerDictionaryInitialization_JObjectDrawable_Dict_Impl();
}
