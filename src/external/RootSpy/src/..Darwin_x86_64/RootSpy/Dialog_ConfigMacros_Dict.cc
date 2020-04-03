// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME srcdIexternaldIRootSpydIsrcdIdOdODarwin_x86_64dIRootSpydIDialog_ConfigMacros_Dict
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
#include "src/external/RootSpy/src/RootSpy/Dialog_ConfigMacros.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void delete_Dialog_ConfigMacros(void *p);
   static void deleteArray_Dialog_ConfigMacros(void *p);
   static void destruct_Dialog_ConfigMacros(void *p);
   static void streamer_Dialog_ConfigMacros(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Dialog_ConfigMacros*)
   {
      ::Dialog_ConfigMacros *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Dialog_ConfigMacros >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Dialog_ConfigMacros", ::Dialog_ConfigMacros::Class_Version(), "RootSpy/src/RootSpy/Dialog_ConfigMacros.h", 30,
                  typeid(::Dialog_ConfigMacros), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Dialog_ConfigMacros::Dictionary, isa_proxy, 16,
                  sizeof(::Dialog_ConfigMacros) );
      instance.SetDelete(&delete_Dialog_ConfigMacros);
      instance.SetDeleteArray(&deleteArray_Dialog_ConfigMacros);
      instance.SetDestructor(&destruct_Dialog_ConfigMacros);
      instance.SetStreamerFunc(&streamer_Dialog_ConfigMacros);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Dialog_ConfigMacros*)
   {
      return GenerateInitInstanceLocal((::Dialog_ConfigMacros*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Dialog_ConfigMacros*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr Dialog_ConfigMacros::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Dialog_ConfigMacros::Class_Name()
{
   return "Dialog_ConfigMacros";
}

//______________________________________________________________________________
const char *Dialog_ConfigMacros::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Dialog_ConfigMacros*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Dialog_ConfigMacros::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Dialog_ConfigMacros*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Dialog_ConfigMacros::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Dialog_ConfigMacros*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Dialog_ConfigMacros::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Dialog_ConfigMacros*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void Dialog_ConfigMacros::Streamer(TBuffer &R__b)
{
   // Stream an object of class Dialog_ConfigMacros.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TGMainFrame::Streamer(R__b);
      R__b >> listBox;
      R__b >> hnamepathBox;
      R__b >> macroBox;
      {
         map<string,string> &R__stl =  new_macro_files;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         for (R__i = 0; R__i < R__n; R__i++) {
            string R__t;
            {TString R__str;
             R__str.Streamer(R__b);
             R__t = R__str.Data();}
            string R__t2;
            {TString R__str;
             R__str.Streamer(R__b);
             R__t2 = R__str.Data();}
            typedef class std::__1::basic_string<char> Value_t;
            std::pair<Value_t const, class std::__1::basic_string<char> > R__t3(R__t,R__t2);
            R__stl.insert(R__t3);
         }
      }
      R__b.CheckByteCount(R__s, R__c, Dialog_ConfigMacros::IsA());
   } else {
      R__c = R__b.WriteVersion(Dialog_ConfigMacros::IsA(), kTRUE);
      TGMainFrame::Streamer(R__b);
      R__b << listBox;
      R__b << hnamepathBox;
      R__b << macroBox;
      {
         map<string,string> &R__stl =  new_macro_files;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            map<string,string>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            {TString R__str(((*R__k).first ).c_str());
             R__str.Streamer(R__b);};
            {TString R__str(((*R__k).second).c_str());
             R__str.Streamer(R__b);};
            }
         }
      }
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Dialog_ConfigMacros(void *p) {
      delete ((::Dialog_ConfigMacros*)p);
   }
   static void deleteArray_Dialog_ConfigMacros(void *p) {
      delete [] ((::Dialog_ConfigMacros*)p);
   }
   static void destruct_Dialog_ConfigMacros(void *p) {
      typedef ::Dialog_ConfigMacros current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_Dialog_ConfigMacros(TBuffer &buf, void *obj) {
      ((::Dialog_ConfigMacros*)obj)->::Dialog_ConfigMacros::Streamer(buf);
   }
} // end of namespace ROOT for class ::Dialog_ConfigMacros

namespace ROOT {
   static TClass *maplEstringcOstringgR_Dictionary();
   static void maplEstringcOstringgR_TClassManip(TClass*);
   static void *new_maplEstringcOstringgR(void *p = 0);
   static void *newArray_maplEstringcOstringgR(Long_t size, void *p);
   static void delete_maplEstringcOstringgR(void *p);
   static void deleteArray_maplEstringcOstringgR(void *p);
   static void destruct_maplEstringcOstringgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,string>*)
   {
      map<string,string> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,string>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,string>", -2, "map", 899,
                  typeid(map<string,string>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOstringgR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,string>) );
      instance.SetNew(&new_maplEstringcOstringgR);
      instance.SetNewArray(&newArray_maplEstringcOstringgR);
      instance.SetDelete(&delete_maplEstringcOstringgR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOstringgR);
      instance.SetDestructor(&destruct_maplEstringcOstringgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,string> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<string,string>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOstringgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<string,string>*)0x0)->GetClass();
      maplEstringcOstringgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOstringgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOstringgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,string> : new map<string,string>;
   }
   static void *newArray_maplEstringcOstringgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,string>[nElements] : new map<string,string>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOstringgR(void *p) {
      delete ((map<string,string>*)p);
   }
   static void deleteArray_maplEstringcOstringgR(void *p) {
      delete [] ((map<string,string>*)p);
   }
   static void destruct_maplEstringcOstringgR(void *p) {
      typedef map<string,string> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<string,string>

namespace {
  void TriggerDictionaryInitialization_Dialog_ConfigMacros_Dict_Impl() {
    static const char* headers[] = {
"src/external/RootSpy/src/RootSpy/Dialog_ConfigMacros.h",
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
#line 1 "Dialog_ConfigMacros_Dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$src/external/RootSpy/src/RootSpy/Dialog_ConfigMacros.h")))  Dialog_ConfigMacros;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "Dialog_ConfigMacros_Dict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "src/external/RootSpy/src/RootSpy/Dialog_ConfigMacros.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"Dialog_ConfigMacros", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("Dialog_ConfigMacros_Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_Dialog_ConfigMacros_Dict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_Dialog_ConfigMacros_Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_Dialog_ConfigMacros_Dict() {
  TriggerDictionaryInitialization_Dialog_ConfigMacros_Dict_Impl();
}
