// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME srcdIexternaldIRootSpydIsrcdIdOdOLinux_x86_64dIRootSpydIDialog_SelectTree_Dict

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
#include "src/external/RootSpy/src/RootSpy/Dialog_SelectTree.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void delete_Dialog_SelectTree(void *p);
   static void deleteArray_Dialog_SelectTree(void *p);
   static void destruct_Dialog_SelectTree(void *p);
   static void streamer_Dialog_SelectTree(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Dialog_SelectTree*)
   {
      ::Dialog_SelectTree *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Dialog_SelectTree >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Dialog_SelectTree", ::Dialog_SelectTree::Class_Version(), "RootSpy/src/RootSpy/Dialog_SelectTree.h", 26,
                  typeid(::Dialog_SelectTree), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Dialog_SelectTree::Dictionary, isa_proxy, 16,
                  sizeof(::Dialog_SelectTree) );
      instance.SetDelete(&delete_Dialog_SelectTree);
      instance.SetDeleteArray(&deleteArray_Dialog_SelectTree);
      instance.SetDestructor(&destruct_Dialog_SelectTree);
      instance.SetStreamerFunc(&streamer_Dialog_SelectTree);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Dialog_SelectTree*)
   {
      return GenerateInitInstanceLocal((::Dialog_SelectTree*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Dialog_SelectTree*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr Dialog_SelectTree::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Dialog_SelectTree::Class_Name()
{
   return "Dialog_SelectTree";
}

//______________________________________________________________________________
const char *Dialog_SelectTree::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Dialog_SelectTree*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Dialog_SelectTree::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Dialog_SelectTree*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Dialog_SelectTree::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Dialog_SelectTree*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Dialog_SelectTree::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Dialog_SelectTree*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void Dialog_SelectTree::Streamer(TBuffer &R__b)
{
   // Stream an object of class Dialog_SelectTree.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TGMainFrame::Streamer(R__b);
      R__b >> sleep_time;
      R__b >> timer;
      R__b >> canvas;
      R__b >> list_tree;
      R__b >> viewByObject;
      R__b >> viewByServer;
      R__b >> cancel;
      R__b >> folder_t;
      R__b >> ofolder_t;
      R__b >> tree_s;
      R__b >> tree_t;
      R__b >> pack_t;
      R__b >> hdisk_t;
      R__b >> checked_t;
      R__b >> unchecked_t;
      {
         map<tree_id_t,TGListTreeItem*> &R__stl =  server_items;
         R__stl.clear();
         TClass *R__tcl1 = TBuffer::GetClass(typeid(class tree_id_t));
         if (R__tcl1==0) {
            Error("server_items streamer","Missing the TClass object for class tree_id_t!");
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
            tree_id_t R__t;
            R__b.StreamObject(&R__t,R__tcl1);
            TGListTreeItem* R__t2;
            if (R__b.GetInfo() && R__b.GetInfo()->GetOldVersion()<=3) {
               R__ASSERT(0);// TGListTreeItem is abstract. We assume that older file could not be produced using this streaming method.
            } else {
               R__t2 = (TGListTreeItem*)R__b.ReadObjectAny(R__tcl2);
            }
            typedef class tree_id_t Value_t;
            std::pair<Value_t const, class TGListTreeItem * > R__t3(R__t,R__t2);
            R__stl.insert(R__t3);
         }
      }
      {
         map<tree_id_t,TGListTreeItem*> &R__stl =  tree_items;
         R__stl.clear();
         TClass *R__tcl1 = TBuffer::GetClass(typeid(class tree_id_t));
         if (R__tcl1==0) {
            Error("tree_items streamer","Missing the TClass object for class tree_id_t!");
            return;
         }
         TClass *R__tcl2 = TBuffer::GetClass(typeid(class TGListTreeItem *));
         if (R__tcl2==0) {
            Error("tree_items streamer","Missing the TClass object for class TGListTreeItem *!");
            return;
         }
         int R__i, R__n;
         R__b >> R__n;
         for (R__i = 0; R__i < R__n; R__i++) {
            tree_id_t R__t;
            R__b.StreamObject(&R__t,R__tcl1);
            TGListTreeItem* R__t2;
            if (R__b.GetInfo() && R__b.GetInfo()->GetOldVersion()<=3) {
               R__ASSERT(0);// TGListTreeItem is abstract. We assume that older file could not be produced using this streaming method.
            } else {
               R__t2 = (TGListTreeItem*)R__b.ReadObjectAny(R__tcl2);
            }
            typedef class tree_id_t Value_t;
            std::pair<Value_t const, class TGListTreeItem * > R__t3(R__t,R__t2);
            R__stl.insert(R__t3);
         }
      }
      R__b >> last_called;
      R__b >> last_ping_time;
      R__b >> last_hist_time;
      R__b >> requested;
      R__b >> lastsize;
      R__b.CheckByteCount(R__s, R__c, Dialog_SelectTree::IsA());
   } else {
      R__c = R__b.WriteVersion(Dialog_SelectTree::IsA(), kTRUE);
      TGMainFrame::Streamer(R__b);
      R__b << sleep_time;
      R__b << timer;
      R__b << canvas;
      R__b << list_tree;
      R__b << viewByObject;
      R__b << viewByServer;
      R__b << cancel;
      R__b << folder_t;
      R__b << ofolder_t;
      R__b << tree_s;
      R__b << tree_t;
      R__b << pack_t;
      R__b << hdisk_t;
      R__b << checked_t;
      R__b << unchecked_t;
      {
         map<tree_id_t,TGListTreeItem*> &R__stl =  server_items;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
         TClass *R__tcl1 = TBuffer::GetClass(typeid(class tree_id_t));
         if (R__tcl1==0) {
            Error("server_items streamer","Missing the TClass object for class tree_id_t!");
            return;
         }
         TClass *R__tcl2 = TBuffer::GetClass(typeid(class TGListTreeItem *));
         if (R__tcl2==0) {
            Error("server_itemsstreamer","Missing the TClass object for class TGListTreeItem *!");
            return;
         }
            map<tree_id_t,TGListTreeItem*>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            R__b.StreamObject((tree_id_t*)&((*R__k).first ),R__tcl1);
            R__b.WriteObjectAny(((*R__k).second),R__tcl2);
            }
         }
      }
      {
         map<tree_id_t,TGListTreeItem*> &R__stl =  tree_items;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
         TClass *R__tcl1 = TBuffer::GetClass(typeid(class tree_id_t));
         if (R__tcl1==0) {
            Error("tree_items streamer","Missing the TClass object for class tree_id_t!");
            return;
         }
         TClass *R__tcl2 = TBuffer::GetClass(typeid(class TGListTreeItem *));
         if (R__tcl2==0) {
            Error("tree_itemsstreamer","Missing the TClass object for class TGListTreeItem *!");
            return;
         }
            map<tree_id_t,TGListTreeItem*>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            R__b.StreamObject((tree_id_t*)&((*R__k).first ),R__tcl1);
            R__b.WriteObjectAny(((*R__k).second),R__tcl2);
            }
         }
      }
      R__b << last_called;
      R__b << last_ping_time;
      R__b << last_hist_time;
      R__b << requested;
      R__b << lastsize;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_Dialog_SelectTree(void *p) {
      delete ((::Dialog_SelectTree*)p);
   }
   static void deleteArray_Dialog_SelectTree(void *p) {
      delete [] ((::Dialog_SelectTree*)p);
   }
   static void destruct_Dialog_SelectTree(void *p) {
      typedef ::Dialog_SelectTree current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_Dialog_SelectTree(TBuffer &buf, void *obj) {
      ((::Dialog_SelectTree*)obj)->::Dialog_SelectTree::Streamer(buf);
   }
} // end of namespace ROOT for class ::Dialog_SelectTree

namespace ROOT {
   static TClass *maplEtree_id_tcOTGListTreeItemmUgR_Dictionary();
   static void maplEtree_id_tcOTGListTreeItemmUgR_TClassManip(TClass*);
   static void *new_maplEtree_id_tcOTGListTreeItemmUgR(void *p = 0);
   static void *newArray_maplEtree_id_tcOTGListTreeItemmUgR(Long_t size, void *p);
   static void delete_maplEtree_id_tcOTGListTreeItemmUgR(void *p);
   static void deleteArray_maplEtree_id_tcOTGListTreeItemmUgR(void *p);
   static void destruct_maplEtree_id_tcOTGListTreeItemmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<tree_id_t,TGListTreeItem*>*)
   {
      map<tree_id_t,TGListTreeItem*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<tree_id_t,TGListTreeItem*>));
      static ::ROOT::TGenericClassInfo 
         instance("map<tree_id_t,TGListTreeItem*>", -2, "map", 100,
                  typeid(map<tree_id_t,TGListTreeItem*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEtree_id_tcOTGListTreeItemmUgR_Dictionary, isa_proxy, 0,
                  sizeof(map<tree_id_t,TGListTreeItem*>) );
      instance.SetNew(&new_maplEtree_id_tcOTGListTreeItemmUgR);
      instance.SetNewArray(&newArray_maplEtree_id_tcOTGListTreeItemmUgR);
      instance.SetDelete(&delete_maplEtree_id_tcOTGListTreeItemmUgR);
      instance.SetDeleteArray(&deleteArray_maplEtree_id_tcOTGListTreeItemmUgR);
      instance.SetDestructor(&destruct_maplEtree_id_tcOTGListTreeItemmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<tree_id_t,TGListTreeItem*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<tree_id_t,TGListTreeItem*>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEtree_id_tcOTGListTreeItemmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<tree_id_t,TGListTreeItem*>*)0x0)->GetClass();
      maplEtree_id_tcOTGListTreeItemmUgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEtree_id_tcOTGListTreeItemmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEtree_id_tcOTGListTreeItemmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<tree_id_t,TGListTreeItem*> : new map<tree_id_t,TGListTreeItem*>;
   }
   static void *newArray_maplEtree_id_tcOTGListTreeItemmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<tree_id_t,TGListTreeItem*>[nElements] : new map<tree_id_t,TGListTreeItem*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEtree_id_tcOTGListTreeItemmUgR(void *p) {
      delete ((map<tree_id_t,TGListTreeItem*>*)p);
   }
   static void deleteArray_maplEtree_id_tcOTGListTreeItemmUgR(void *p) {
      delete [] ((map<tree_id_t,TGListTreeItem*>*)p);
   }
   static void destruct_maplEtree_id_tcOTGListTreeItemmUgR(void *p) {
      typedef map<tree_id_t,TGListTreeItem*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<tree_id_t,TGListTreeItem*>

namespace {
  void TriggerDictionaryInitialization_Dialog_SelectTree_Dict_Impl() {
    static const char* headers[] = {
"src/external/RootSpy/src/RootSpy/Dialog_SelectTree.h",
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
#line 1 "Dialog_SelectTree_Dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$src/external/RootSpy/src/RootSpy/Dialog_SelectTree.h")))  Dialog_SelectTree;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "Dialog_SelectTree_Dict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "src/external/RootSpy/src/RootSpy/Dialog_SelectTree.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"Dialog_SelectTree", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("Dialog_SelectTree_Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_Dialog_SelectTree_Dict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_Dialog_SelectTree_Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_Dialog_SelectTree_Dict() {
  TriggerDictionaryInitialization_Dialog_SelectTree_Dict_Impl();
}
