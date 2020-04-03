// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME srcdIexternaldIRootSpydIsrcdIdOdODarwin_x86_64dIRootSpydIrs_mainframe_Dict
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
#include "src/external/RootSpy/src/RootSpy/rs_mainframe.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void delete_rs_mainframe(void *p);
   static void deleteArray_rs_mainframe(void *p);
   static void destruct_rs_mainframe(void *p);
   static void streamer_rs_mainframe(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::rs_mainframe*)
   {
      ::rs_mainframe *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::rs_mainframe >(0);
      static ::ROOT::TGenericClassInfo 
         instance("rs_mainframe", ::rs_mainframe::Class_Version(), "RootSpy/src/RootSpy/rs_mainframe.h", 51,
                  typeid(::rs_mainframe), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::rs_mainframe::Dictionary, isa_proxy, 16,
                  sizeof(::rs_mainframe) );
      instance.SetDelete(&delete_rs_mainframe);
      instance.SetDeleteArray(&deleteArray_rs_mainframe);
      instance.SetDestructor(&destruct_rs_mainframe);
      instance.SetStreamerFunc(&streamer_rs_mainframe);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::rs_mainframe*)
   {
      return GenerateInitInstanceLocal((::rs_mainframe*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::rs_mainframe*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr rs_mainframe::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *rs_mainframe::Class_Name()
{
   return "rs_mainframe";
}

//______________________________________________________________________________
const char *rs_mainframe::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::rs_mainframe*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int rs_mainframe::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::rs_mainframe*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *rs_mainframe::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::rs_mainframe*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *rs_mainframe::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::rs_mainframe*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void rs_mainframe::Streamer(TBuffer &R__b)
{
   // Stream an object of class rs_mainframe.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TGMainFrame::Streamer(R__b);
      R__b >> fMainTab;
      R__b >> lUDL;
      R__b >> lArchiveFile;
      R__b >> bAutoRefresh;
      R__b >> bAutoAdvance;
      R__b >> fDelay;
      R__b >> bShowOverlays;
      R__b >> run_number_label;
      R__b >> dialog_savehists;
      R__b >> dialog_selecttree;
      R__b >> dialog_configmacros;
      R__b >> dialog_scaleopts;
      R__b >> dialog_referenceplot;
      R__b >> dialog_newreference;
      R__b >> fMenuDock;
      R__b >> fMenuBar;
      R__b >> fMenuFile;
      R__b >> fMenuTools;
      R__b >> fMenuView;
      R__b >> fMenuBarLayout;
      R__b >> fMenuBarItemLayout;
      R__b >> fMenuBarHelpLayout;
      R__b >> delete_dialog_selecttree;
      R__b >> delete_dialog_savehists;
      R__b >> delete_dialog_configmacros;
      R__b >> delete_dialog_scaleopts;
      { TString R__str; R__str.Streamer(R__b); config_filename = R__str.Data(); }
      {
         map<string,string> &R__stl =  macro_files;
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
      {
         list<RSTab*> &R__stl =  rstabs;
         R__stl.clear();
         TClass *R__tcl1 = TBuffer::GetClass(typeid(class RSTab *));
         if (R__tcl1==0) {
            Error("rstabs streamer","Missing the TClass object for class RSTab *!");
            return;
         }
         int R__i, R__n;
         R__b >> R__n;
         for (R__i = 0; R__i < R__n; R__i++) {
            RSTab* R__t;
            if (R__b.GetInfo() && R__b.GetInfo()->GetOldVersion()<=3) {
               R__t = new RSTab;
               R__t->Streamer(R__b);
            } else {
               R__t = (RSTab*)R__b.ReadObjectAny(R__tcl1);
            }
            R__stl.push_back(R__t);
         }
      }
      R__b >> current_tab;
      void *ptr_viewStyle_rs = (void*)&viewStyle_rs;
      R__b >> *reinterpret_cast<Int_t*>(ptr_viewStyle_rs);
      R__b >> archive_file;
      R__b >> epics_run_number;
      R__b >> last_epics_run_number_checked;
      R__b >> timer;
      R__b >> sleep_time;
      R__b >> last_called;
      R__b >> last_ping_time;
      R__b >> last_hist_requested;
      R__b >> VBServer;
      R__b >> delay_time;
      R__b.StreamObject(&(last_requested),typeid(last_requested));
      R__b >> last_hist_plotted;
      R__b >> selected_tab_from_prefrences;
      R__b.StreamObject(&(winsize_from_preferences),typeid(winsize_from_preferences));
      R__b >> elog_timer;
      R__b >> Npages_elog;
      R__b >> ipage_elog;
      R__b >> elog_next_action;
      R__b >> elog_tab_restore;
      R__b >> elog_plot_restore;
      R__b >> exec_shell;
      R__b.CheckByteCount(R__s, R__c, rs_mainframe::IsA());
   } else {
      R__c = R__b.WriteVersion(rs_mainframe::IsA(), kTRUE);
      TGMainFrame::Streamer(R__b);
      R__b << fMainTab;
      R__b << lUDL;
      R__b << lArchiveFile;
      R__b << bAutoRefresh;
      R__b << bAutoAdvance;
      R__b << fDelay;
      R__b << bShowOverlays;
      R__b << run_number_label;
      R__b << dialog_savehists;
      R__b << dialog_selecttree;
      R__b << dialog_configmacros;
      R__b << dialog_scaleopts;
      R__b << dialog_referenceplot;
      R__b << dialog_newreference;
      R__b << fMenuDock;
      R__b << fMenuBar;
      R__b << fMenuFile;
      R__b << fMenuTools;
      R__b << fMenuView;
      R__b << fMenuBarLayout;
      R__b << fMenuBarItemLayout;
      R__b << fMenuBarHelpLayout;
      R__b << delete_dialog_selecttree;
      R__b << delete_dialog_savehists;
      R__b << delete_dialog_configmacros;
      R__b << delete_dialog_scaleopts;
      { TString R__str = config_filename.c_str(); R__str.Streamer(R__b);}
      {
         map<string,string> &R__stl =  macro_files;
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
      {
         list<RSTab*> &R__stl =  rstabs;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
         TClass *R__tcl1 = TBuffer::GetClass(typeid(class RSTab *));
         if (R__tcl1==0) {
            Error("rstabs streamer","Missing the TClass object for class RSTab *!");
            return;
         }
            list<RSTab*>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            R__b.WriteObjectAny((*R__k),R__tcl1);
            }
         }
      }
      R__b << current_tab;
      R__b << (Int_t)viewStyle_rs;
      R__b << archive_file;
      R__b << epics_run_number;
      R__b << last_epics_run_number_checked;
      R__b << timer;
      R__b << sleep_time;
      R__b << last_called;
      R__b << last_ping_time;
      R__b << last_hist_requested;
      R__b << VBServer;
      R__b << delay_time;
      R__b.StreamObject(&(last_requested),typeid(last_requested));
      R__b << last_hist_plotted;
      R__b << selected_tab_from_prefrences;
      R__b.StreamObject(&(winsize_from_preferences),typeid(winsize_from_preferences));
      R__b << elog_timer;
      R__b << Npages_elog;
      R__b << ipage_elog;
      R__b << elog_next_action;
      R__b << elog_tab_restore;
      R__b << elog_plot_restore;
      R__b << exec_shell;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_rs_mainframe(void *p) {
      delete ((::rs_mainframe*)p);
   }
   static void deleteArray_rs_mainframe(void *p) {
      delete [] ((::rs_mainframe*)p);
   }
   static void destruct_rs_mainframe(void *p) {
      typedef ::rs_mainframe current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_rs_mainframe(TBuffer &buf, void *obj) {
      ((::rs_mainframe*)obj)->::rs_mainframe::Streamer(buf);
   }
} // end of namespace ROOT for class ::rs_mainframe

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

namespace ROOT {
   static TClass *listlERSTabmUgR_Dictionary();
   static void listlERSTabmUgR_TClassManip(TClass*);
   static void *new_listlERSTabmUgR(void *p = 0);
   static void *newArray_listlERSTabmUgR(Long_t size, void *p);
   static void delete_listlERSTabmUgR(void *p);
   static void deleteArray_listlERSTabmUgR(void *p);
   static void destruct_listlERSTabmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const list<RSTab*>*)
   {
      list<RSTab*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(list<RSTab*>));
      static ::ROOT::TGenericClassInfo 
         instance("list<RSTab*>", -2, "list", 834,
                  typeid(list<RSTab*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &listlERSTabmUgR_Dictionary, isa_proxy, 0,
                  sizeof(list<RSTab*>) );
      instance.SetNew(&new_listlERSTabmUgR);
      instance.SetNewArray(&newArray_listlERSTabmUgR);
      instance.SetDelete(&delete_listlERSTabmUgR);
      instance.SetDeleteArray(&deleteArray_listlERSTabmUgR);
      instance.SetDestructor(&destruct_listlERSTabmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< list<RSTab*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const list<RSTab*>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *listlERSTabmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const list<RSTab*>*)0x0)->GetClass();
      listlERSTabmUgR_TClassManip(theClass);
   return theClass;
   }

   static void listlERSTabmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_listlERSTabmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) list<RSTab*> : new list<RSTab*>;
   }
   static void *newArray_listlERSTabmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) list<RSTab*>[nElements] : new list<RSTab*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_listlERSTabmUgR(void *p) {
      delete ((list<RSTab*>*)p);
   }
   static void deleteArray_listlERSTabmUgR(void *p) {
      delete [] ((list<RSTab*>*)p);
   }
   static void destruct_listlERSTabmUgR(void *p) {
      typedef list<RSTab*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class list<RSTab*>

namespace {
  void TriggerDictionaryInitialization_rs_mainframe_Dict_Impl() {
    static const char* headers[] = {
"src/external/RootSpy/src/RootSpy/rs_mainframe.h",
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
#line 1 "rs_mainframe_Dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$src/external/RootSpy/src/RootSpy/rs_mainframe.h")))  rs_mainframe;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "rs_mainframe_Dict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "src/external/RootSpy/src/RootSpy/rs_mainframe.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"rs_mainframe", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("rs_mainframe_Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_rs_mainframe_Dict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_rs_mainframe_Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_rs_mainframe_Dict() {
  TriggerDictionaryInitialization_rs_mainframe_Dict_Impl();
}
