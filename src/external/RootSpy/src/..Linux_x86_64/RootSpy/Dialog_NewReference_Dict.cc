// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME srcdIexternaldIRootSpydIsrcdIdOdOLinux_x86_64dIRootSpydIDialog_NewReference_Dict

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
#include "src/external/RootSpy/src/RootSpy/Dialog_NewReference.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void delete_Dialog_NewReference(void *p);
   static void deleteArray_Dialog_NewReference(void *p);
   static void destruct_Dialog_NewReference(void *p);
   static void streamer_Dialog_NewReference(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Dialog_NewReference*)
   {
      ::Dialog_NewReference *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Dialog_NewReference >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Dialog_NewReference", ::Dialog_NewReference::Class_Version(), "RootSpy/src/RootSpy/Dialog_NewReference.h", 34,
                  typeid(::Dialog_NewReference), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Dialog_NewReference::Dictionary, isa_proxy, 16,
                  sizeof(::Dialog_NewReference) );
      instance.SetDelete(&delete_Dialog_NewReference);
      instance.SetDeleteArray(&deleteArray_Dialog_NewReference);
      instance.SetDestructor(&destruct_Dialog_NewReference);
      instance.SetStreamerFunc(&streamer_Dialog_NewReference);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Dialog_NewReference*)
   {
      return GenerateInitInstanceLocal((::Dialog_NewReference*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Dialog_NewReference*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr Dialog_NewReference::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Dialog_NewReference::Class_Name()
{
   return "Dialog_NewReference";
}

//______________________________________________________________________________
const char *Dialog_NewReference::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Dialog_NewReference*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Dialog_NewReference::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Dialog_NewReference*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Dialog_NewReference::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Dialog_NewReference*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Dialog_NewReference::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Dialog_NewReference*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void Dialog_NewReference::Streamer(TBuffer &R__b)
{
   // Stream an object of class Dialog_NewReference.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TGMainFrame::Streamer(R__b);
      { TString R__str; R__str.Streamer(R__b); hnamepath = R__str.Data(); }
      { TString R__str; R__str.Streamer(R__b); image_filename_new = R__str.Data(); }
      { TString R__str; R__str.Streamer(R__b); image_filename_old = R__str.Data(); }
      {
         set<string> &R__stl =  emails;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         for (R__i = 0; R__i < R__n; R__i++) {
            string R__t;
            {TString R__str;
             R__str.Streamer(R__b);
             R__t = R__str.Data();}
            R__stl.insert(R__t);
         }
      }
      { TString R__str; R__str.Streamer(R__b); fname = R__str.Data(); }
      { TString R__str; R__str.Streamer(R__b); tmp_fname = R__str.Data(); }
      { TString R__str; R__str.Streamer(R__b); image_mod_time = R__str.Data(); }
      R__b >> cbagree;
      R__b.CheckByteCount(R__s, R__c, Dialog_NewReference::IsA());
   } else {
      R__c = R__b.WriteVersion(Dialog_NewReference::IsA(), kTRUE);
      TGMainFrame::Streamer(R__b);
      { TString R__str = hnamepath.c_str(); R__str.Streamer(R__b);}
      { TString R__str = image_filename_new.c_str(); R__str.Streamer(R__b);}
      { TString R__str = image_filename_old.c_str(); R__str.Streamer(R__b);}
      {
         set<string> &R__stl =  emails;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            set<string>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            {TString R__str((*R__k).c_str());
             R__str.Streamer(R__b);};
            }
         }
      }
      { TString R__str = fname.c_str(); R__str.Streamer(R__b);}
      { TString R__str = tmp_fname.c_str(); R__str.Streamer(R__b);}
      { TString R__str = image_mod_time.c_str(); R__str.Streamer(R__b);}
      R__b << cbagree;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Dialog_NewReference(void *p) {
      delete ((::Dialog_NewReference*)p);
   }
   static void deleteArray_Dialog_NewReference(void *p) {
      delete [] ((::Dialog_NewReference*)p);
   }
   static void destruct_Dialog_NewReference(void *p) {
      typedef ::Dialog_NewReference current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_Dialog_NewReference(TBuffer &buf, void *obj) {
      ((::Dialog_NewReference*)obj)->::Dialog_NewReference::Streamer(buf);
   }
} // end of namespace ROOT for class ::Dialog_NewReference

namespace ROOT {
   static TClass *setlEstringgR_Dictionary();
   static void setlEstringgR_TClassManip(TClass*);
   static void *new_setlEstringgR(void *p = 0);
   static void *newArray_setlEstringgR(Long_t size, void *p);
   static void delete_setlEstringgR(void *p);
   static void deleteArray_setlEstringgR(void *p);
   static void destruct_setlEstringgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const set<string>*)
   {
      set<string> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(set<string>));
      static ::ROOT::TGenericClassInfo 
         instance("set<string>", -2, "set", 94,
                  typeid(set<string>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &setlEstringgR_Dictionary, isa_proxy, 0,
                  sizeof(set<string>) );
      instance.SetNew(&new_setlEstringgR);
      instance.SetNewArray(&newArray_setlEstringgR);
      instance.SetDelete(&delete_setlEstringgR);
      instance.SetDeleteArray(&deleteArray_setlEstringgR);
      instance.SetDestructor(&destruct_setlEstringgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Insert< set<string> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const set<string>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *setlEstringgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const set<string>*)0x0)->GetClass();
      setlEstringgR_TClassManip(theClass);
   return theClass;
   }

   static void setlEstringgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_setlEstringgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) set<string> : new set<string>;
   }
   static void *newArray_setlEstringgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) set<string>[nElements] : new set<string>[nElements];
   }
   // Wrapper around operator delete
   static void delete_setlEstringgR(void *p) {
      delete ((set<string>*)p);
   }
   static void deleteArray_setlEstringgR(void *p) {
      delete [] ((set<string>*)p);
   }
   static void destruct_setlEstringgR(void *p) {
      typedef set<string> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class set<string>

namespace {
  void TriggerDictionaryInitialization_Dialog_NewReference_Dict_Impl() {
    static const char* headers[] = {
"src/external/RootSpy/src/RootSpy/Dialog_NewReference.h",
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
#line 1 "Dialog_NewReference_Dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$src/external/RootSpy/src/RootSpy/Dialog_NewReference.h")))  Dialog_NewReference;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "Dialog_NewReference_Dict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "src/external/RootSpy/src/RootSpy/Dialog_NewReference.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"Dialog_NewReference", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("Dialog_NewReference_Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_Dialog_NewReference_Dict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_Dialog_NewReference_Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_Dialog_NewReference_Dict() {
  TriggerDictionaryInitialization_Dialog_NewReference_Dict_Impl();
}
