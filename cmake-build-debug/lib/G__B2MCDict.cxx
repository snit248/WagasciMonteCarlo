// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME G__B2MCDict
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
#include "B2HitSummary.hh"
#include "B2ClusterSummary.hh"
#include "B2TrackSummary.hh"
#include "B2VertexSummary.hh"
#include "B2BeamSummary.hh"
#include "B2Measurement.hh"
#include "B2EventSummary.hh"
#include "B2SpillSummary.hh"
#include "B2EmulsionSummary.hh"
#include "B2HitsSet.hh"
#include "B2Pdg.hh"
#include "B2RefArray.hh"
#include "B2Boundary.hh"
#include "B2Sigma.hh"
#include "B2Dial.hh"
#include "B2DialList.hh"
#include "B2SigmaList.hh"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *__gnu_cxxcLcL__normal_iteratorlEB2DialmUcOvectorlEB2DialgRsPgR_Dictionary();
   static void __gnu_cxxcLcL__normal_iteratorlEB2DialmUcOvectorlEB2DialgRsPgR_TClassManip(TClass*);
   static void *new___gnu_cxxcLcL__normal_iteratorlEB2DialmUcOvectorlEB2DialgRsPgR(void *p = 0);
   static void *newArray___gnu_cxxcLcL__normal_iteratorlEB2DialmUcOvectorlEB2DialgRsPgR(Long_t size, void *p);
   static void delete___gnu_cxxcLcL__normal_iteratorlEB2DialmUcOvectorlEB2DialgRsPgR(void *p);
   static void deleteArray___gnu_cxxcLcL__normal_iteratorlEB2DialmUcOvectorlEB2DialgRsPgR(void *p);
   static void destruct___gnu_cxxcLcL__normal_iteratorlEB2DialmUcOvectorlEB2DialgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::__gnu_cxx::__normal_iterator<B2Dial*,vector<B2Dial> >*)
   {
      ::__gnu_cxx::__normal_iterator<B2Dial*,vector<B2Dial> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::__gnu_cxx::__normal_iterator<B2Dial*,vector<B2Dial> >));
      static ::ROOT::TGenericClassInfo 
         instance("__gnu_cxx::__normal_iterator<B2Dial*,vector<B2Dial> >", "string", 784,
                  typeid(::__gnu_cxx::__normal_iterator<B2Dial*,vector<B2Dial> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &__gnu_cxxcLcL__normal_iteratorlEB2DialmUcOvectorlEB2DialgRsPgR_Dictionary, isa_proxy, 4,
                  sizeof(::__gnu_cxx::__normal_iterator<B2Dial*,vector<B2Dial> >) );
      instance.SetNew(&new___gnu_cxxcLcL__normal_iteratorlEB2DialmUcOvectorlEB2DialgRsPgR);
      instance.SetNewArray(&newArray___gnu_cxxcLcL__normal_iteratorlEB2DialmUcOvectorlEB2DialgRsPgR);
      instance.SetDelete(&delete___gnu_cxxcLcL__normal_iteratorlEB2DialmUcOvectorlEB2DialgRsPgR);
      instance.SetDeleteArray(&deleteArray___gnu_cxxcLcL__normal_iteratorlEB2DialmUcOvectorlEB2DialgRsPgR);
      instance.SetDestructor(&destruct___gnu_cxxcLcL__normal_iteratorlEB2DialmUcOvectorlEB2DialgRsPgR);

      ::ROOT::AddClassAlternate("__gnu_cxx::__normal_iterator<B2Dial*,vector<B2Dial> >","vector<B2Dial>::iterator");

      ::ROOT::AddClassAlternate("__gnu_cxx::__normal_iterator<B2Dial*,vector<B2Dial> >","__gnu_cxx::__normal_iterator<B2Dial*, std::vector<B2Dial, std::allocator<B2Dial> > >");
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::__gnu_cxx::__normal_iterator<B2Dial*,vector<B2Dial> >*)
   {
      return GenerateInitInstanceLocal((::__gnu_cxx::__normal_iterator<B2Dial*,vector<B2Dial> >*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::__gnu_cxx::__normal_iterator<B2Dial*,vector<B2Dial> >*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *__gnu_cxxcLcL__normal_iteratorlEB2DialmUcOvectorlEB2DialgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::__gnu_cxx::__normal_iterator<B2Dial*,vector<B2Dial> >*)0x0)->GetClass();
      __gnu_cxxcLcL__normal_iteratorlEB2DialmUcOvectorlEB2DialgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void __gnu_cxxcLcL__normal_iteratorlEB2DialmUcOvectorlEB2DialgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *__gnu_cxxcLcL__normal_iteratorlEconstsPB2DialmUcOvectorlEB2DialgRsPgR_Dictionary();
   static void __gnu_cxxcLcL__normal_iteratorlEconstsPB2DialmUcOvectorlEB2DialgRsPgR_TClassManip(TClass*);
   static void *new___gnu_cxxcLcL__normal_iteratorlEconstsPB2DialmUcOvectorlEB2DialgRsPgR(void *p = 0);
   static void *newArray___gnu_cxxcLcL__normal_iteratorlEconstsPB2DialmUcOvectorlEB2DialgRsPgR(Long_t size, void *p);
   static void delete___gnu_cxxcLcL__normal_iteratorlEconstsPB2DialmUcOvectorlEB2DialgRsPgR(void *p);
   static void deleteArray___gnu_cxxcLcL__normal_iteratorlEconstsPB2DialmUcOvectorlEB2DialgRsPgR(void *p);
   static void destruct___gnu_cxxcLcL__normal_iteratorlEconstsPB2DialmUcOvectorlEB2DialgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::__gnu_cxx::__normal_iterator<const B2Dial*,vector<B2Dial> >*)
   {
      ::__gnu_cxx::__normal_iterator<const B2Dial*,vector<B2Dial> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::__gnu_cxx::__normal_iterator<const B2Dial*,vector<B2Dial> >));
      static ::ROOT::TGenericClassInfo 
         instance("__gnu_cxx::__normal_iterator<const B2Dial*,vector<B2Dial> >", "string", 784,
                  typeid(::__gnu_cxx::__normal_iterator<const B2Dial*,vector<B2Dial> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &__gnu_cxxcLcL__normal_iteratorlEconstsPB2DialmUcOvectorlEB2DialgRsPgR_Dictionary, isa_proxy, 4,
                  sizeof(::__gnu_cxx::__normal_iterator<const B2Dial*,vector<B2Dial> >) );
      instance.SetNew(&new___gnu_cxxcLcL__normal_iteratorlEconstsPB2DialmUcOvectorlEB2DialgRsPgR);
      instance.SetNewArray(&newArray___gnu_cxxcLcL__normal_iteratorlEconstsPB2DialmUcOvectorlEB2DialgRsPgR);
      instance.SetDelete(&delete___gnu_cxxcLcL__normal_iteratorlEconstsPB2DialmUcOvectorlEB2DialgRsPgR);
      instance.SetDeleteArray(&deleteArray___gnu_cxxcLcL__normal_iteratorlEconstsPB2DialmUcOvectorlEB2DialgRsPgR);
      instance.SetDestructor(&destruct___gnu_cxxcLcL__normal_iteratorlEconstsPB2DialmUcOvectorlEB2DialgRsPgR);

      ::ROOT::AddClassAlternate("__gnu_cxx::__normal_iterator<const B2Dial*,vector<B2Dial> >","vector<B2Dial>::const_iterator");

      ::ROOT::AddClassAlternate("__gnu_cxx::__normal_iterator<const B2Dial*,vector<B2Dial> >","__gnu_cxx::__normal_iterator<B2Dial const*, std::vector<B2Dial, std::allocator<B2Dial> > >");
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::__gnu_cxx::__normal_iterator<const B2Dial*,vector<B2Dial> >*)
   {
      return GenerateInitInstanceLocal((::__gnu_cxx::__normal_iterator<const B2Dial*,vector<B2Dial> >*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::__gnu_cxx::__normal_iterator<const B2Dial*,vector<B2Dial> >*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *__gnu_cxxcLcL__normal_iteratorlEconstsPB2DialmUcOvectorlEB2DialgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::__gnu_cxx::__normal_iterator<const B2Dial*,vector<B2Dial> >*)0x0)->GetClass();
      __gnu_cxxcLcL__normal_iteratorlEconstsPB2DialmUcOvectorlEB2DialgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void __gnu_cxxcLcL__normal_iteratorlEconstsPB2DialmUcOvectorlEB2DialgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static void *new_B2Measurement1D(void *p = 0);
   static void *newArray_B2Measurement1D(Long_t size, void *p);
   static void delete_B2Measurement1D(void *p);
   static void deleteArray_B2Measurement1D(void *p);
   static void destruct_B2Measurement1D(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::B2Measurement1D*)
   {
      ::B2Measurement1D *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::B2Measurement1D >(0);
      static ::ROOT::TGenericClassInfo 
         instance("B2Measurement1D", ::B2Measurement1D::Class_Version(), "B2Measurement.hh", 22,
                  typeid(::B2Measurement1D), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::B2Measurement1D::Dictionary, isa_proxy, 4,
                  sizeof(::B2Measurement1D) );
      instance.SetNew(&new_B2Measurement1D);
      instance.SetNewArray(&newArray_B2Measurement1D);
      instance.SetDelete(&delete_B2Measurement1D);
      instance.SetDeleteArray(&deleteArray_B2Measurement1D);
      instance.SetDestructor(&destruct_B2Measurement1D);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::B2Measurement1D*)
   {
      return GenerateInitInstanceLocal((::B2Measurement1D*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::B2Measurement1D*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_B2Measurement2D(void *p = 0);
   static void *newArray_B2Measurement2D(Long_t size, void *p);
   static void delete_B2Measurement2D(void *p);
   static void deleteArray_B2Measurement2D(void *p);
   static void destruct_B2Measurement2D(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::B2Measurement2D*)
   {
      ::B2Measurement2D *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::B2Measurement2D >(0);
      static ::ROOT::TGenericClassInfo 
         instance("B2Measurement2D", ::B2Measurement2D::Class_Version(), "B2Measurement.hh", 80,
                  typeid(::B2Measurement2D), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::B2Measurement2D::Dictionary, isa_proxy, 4,
                  sizeof(::B2Measurement2D) );
      instance.SetNew(&new_B2Measurement2D);
      instance.SetNewArray(&newArray_B2Measurement2D);
      instance.SetDelete(&delete_B2Measurement2D);
      instance.SetDeleteArray(&deleteArray_B2Measurement2D);
      instance.SetDestructor(&destruct_B2Measurement2D);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::B2Measurement2D*)
   {
      return GenerateInitInstanceLocal((::B2Measurement2D*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::B2Measurement2D*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_B2Measurement3D(void *p = 0);
   static void *newArray_B2Measurement3D(Long_t size, void *p);
   static void delete_B2Measurement3D(void *p);
   static void deleteArray_B2Measurement3D(void *p);
   static void destruct_B2Measurement3D(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::B2Measurement3D*)
   {
      ::B2Measurement3D *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::B2Measurement3D >(0);
      static ::ROOT::TGenericClassInfo 
         instance("B2Measurement3D", ::B2Measurement3D::Class_Version(), "B2Measurement.hh", 153,
                  typeid(::B2Measurement3D), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::B2Measurement3D::Dictionary, isa_proxy, 4,
                  sizeof(::B2Measurement3D) );
      instance.SetNew(&new_B2Measurement3D);
      instance.SetNewArray(&newArray_B2Measurement3D);
      instance.SetDelete(&delete_B2Measurement3D);
      instance.SetDeleteArray(&deleteArray_B2Measurement3D);
      instance.SetDestructor(&destruct_B2Measurement3D);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::B2Measurement3D*)
   {
      return GenerateInitInstanceLocal((::B2Measurement3D*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::B2Measurement3D*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *B2VectorDoubleReadoutlEintgR_Dictionary();
   static void B2VectorDoubleReadoutlEintgR_TClassManip(TClass*);
   static void *new_B2VectorDoubleReadoutlEintgR(void *p = 0);
   static void *newArray_B2VectorDoubleReadoutlEintgR(Long_t size, void *p);
   static void delete_B2VectorDoubleReadoutlEintgR(void *p);
   static void deleteArray_B2VectorDoubleReadoutlEintgR(void *p);
   static void destruct_B2VectorDoubleReadoutlEintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::B2VectorDoubleReadout<int>*)
   {
      ::B2VectorDoubleReadout<int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::B2VectorDoubleReadout<int> >(0);
      static ::ROOT::TGenericClassInfo 
         instance("B2VectorDoubleReadout<int>", ::B2VectorDoubleReadout<int>::Class_Version(), "B2Measurement.hh", 223,
                  typeid(::B2VectorDoubleReadout<int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &B2VectorDoubleReadoutlEintgR_Dictionary, isa_proxy, 4,
                  sizeof(::B2VectorDoubleReadout<int>) );
      instance.SetNew(&new_B2VectorDoubleReadoutlEintgR);
      instance.SetNewArray(&newArray_B2VectorDoubleReadoutlEintgR);
      instance.SetDelete(&delete_B2VectorDoubleReadoutlEintgR);
      instance.SetDeleteArray(&deleteArray_B2VectorDoubleReadoutlEintgR);
      instance.SetDestructor(&destruct_B2VectorDoubleReadoutlEintgR);

      ::ROOT::AddClassAlternate("B2VectorDoubleReadout<int>","B2VectorDoubleReadout<Int_t>");
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::B2VectorDoubleReadout<int>*)
   {
      return GenerateInitInstanceLocal((::B2VectorDoubleReadout<int>*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::B2VectorDoubleReadout<int>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *B2VectorDoubleReadoutlEintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::B2VectorDoubleReadout<int>*)0x0)->GetClass();
      B2VectorDoubleReadoutlEintgR_TClassManip(theClass);
   return theClass;
   }

   static void B2VectorDoubleReadoutlEintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *B2VectorDoubleReadoutlEdoublegR_Dictionary();
   static void B2VectorDoubleReadoutlEdoublegR_TClassManip(TClass*);
   static void *new_B2VectorDoubleReadoutlEdoublegR(void *p = 0);
   static void *newArray_B2VectorDoubleReadoutlEdoublegR(Long_t size, void *p);
   static void delete_B2VectorDoubleReadoutlEdoublegR(void *p);
   static void deleteArray_B2VectorDoubleReadoutlEdoublegR(void *p);
   static void destruct_B2VectorDoubleReadoutlEdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::B2VectorDoubleReadout<double>*)
   {
      ::B2VectorDoubleReadout<double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::B2VectorDoubleReadout<double> >(0);
      static ::ROOT::TGenericClassInfo 
         instance("B2VectorDoubleReadout<double>", ::B2VectorDoubleReadout<double>::Class_Version(), "B2Measurement.hh", 223,
                  typeid(::B2VectorDoubleReadout<double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &B2VectorDoubleReadoutlEdoublegR_Dictionary, isa_proxy, 4,
                  sizeof(::B2VectorDoubleReadout<double>) );
      instance.SetNew(&new_B2VectorDoubleReadoutlEdoublegR);
      instance.SetNewArray(&newArray_B2VectorDoubleReadoutlEdoublegR);
      instance.SetDelete(&delete_B2VectorDoubleReadoutlEdoublegR);
      instance.SetDeleteArray(&deleteArray_B2VectorDoubleReadoutlEdoublegR);
      instance.SetDestructor(&destruct_B2VectorDoubleReadoutlEdoublegR);

      ::ROOT::AddClassAlternate("B2VectorDoubleReadout<double>","B2VectorDoubleReadout<Double_t>");
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::B2VectorDoubleReadout<double>*)
   {
      return GenerateInitInstanceLocal((::B2VectorDoubleReadout<double>*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::B2VectorDoubleReadout<double>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *B2VectorDoubleReadoutlEdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::B2VectorDoubleReadout<double>*)0x0)->GetClass();
      B2VectorDoubleReadoutlEdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void B2VectorDoubleReadoutlEdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *B2VectorDoubleReadoutlEB2Vector3gR_Dictionary();
   static void B2VectorDoubleReadoutlEB2Vector3gR_TClassManip(TClass*);
   static void *new_B2VectorDoubleReadoutlEB2Vector3gR(void *p = 0);
   static void *newArray_B2VectorDoubleReadoutlEB2Vector3gR(Long_t size, void *p);
   static void delete_B2VectorDoubleReadoutlEB2Vector3gR(void *p);
   static void deleteArray_B2VectorDoubleReadoutlEB2Vector3gR(void *p);
   static void destruct_B2VectorDoubleReadoutlEB2Vector3gR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::B2VectorDoubleReadout<B2Vector3>*)
   {
      ::B2VectorDoubleReadout<B2Vector3> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::B2VectorDoubleReadout<B2Vector3> >(0);
      static ::ROOT::TGenericClassInfo 
         instance("B2VectorDoubleReadout<B2Vector3>", ::B2VectorDoubleReadout<B2Vector3>::Class_Version(), "B2Measurement.hh", 223,
                  typeid(::B2VectorDoubleReadout<B2Vector3>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &B2VectorDoubleReadoutlEB2Vector3gR_Dictionary, isa_proxy, 4,
                  sizeof(::B2VectorDoubleReadout<B2Vector3>) );
      instance.SetNew(&new_B2VectorDoubleReadoutlEB2Vector3gR);
      instance.SetNewArray(&newArray_B2VectorDoubleReadoutlEB2Vector3gR);
      instance.SetDelete(&delete_B2VectorDoubleReadoutlEB2Vector3gR);
      instance.SetDeleteArray(&deleteArray_B2VectorDoubleReadoutlEB2Vector3gR);
      instance.SetDestructor(&destruct_B2VectorDoubleReadoutlEB2Vector3gR);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::B2VectorDoubleReadout<B2Vector3>*)
   {
      return GenerateInitInstanceLocal((::B2VectorDoubleReadout<B2Vector3>*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::B2VectorDoubleReadout<B2Vector3>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *B2VectorDoubleReadoutlEB2Vector3gR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::B2VectorDoubleReadout<B2Vector3>*)0x0)->GetClass();
      B2VectorDoubleReadoutlEB2Vector3gR_TClassManip(theClass);
   return theClass;
   }

   static void B2VectorDoubleReadoutlEB2Vector3gR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static void *new_B2Energy(void *p = 0);
   static void *newArray_B2Energy(Long_t size, void *p);
   static void delete_B2Energy(void *p);
   static void deleteArray_B2Energy(void *p);
   static void destruct_B2Energy(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::B2Energy*)
   {
      ::B2Energy *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::B2Energy >(0);
      static ::ROOT::TGenericClassInfo 
         instance("B2Energy", ::B2Energy::Class_Version(), "B2Measurement.hh", 276,
                  typeid(::B2Energy), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::B2Energy::Dictionary, isa_proxy, 4,
                  sizeof(::B2Energy) );
      instance.SetNew(&new_B2Energy);
      instance.SetNewArray(&newArray_B2Energy);
      instance.SetDelete(&delete_B2Energy);
      instance.SetDeleteArray(&deleteArray_B2Energy);
      instance.SetDestructor(&destruct_B2Energy);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::B2Energy*)
   {
      return GenerateInitInstanceLocal((::B2Energy*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::B2Energy*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_B2Momentum(void *p = 0);
   static void *newArray_B2Momentum(Long_t size, void *p);
   static void delete_B2Momentum(void *p);
   static void deleteArray_B2Momentum(void *p);
   static void destruct_B2Momentum(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::B2Momentum*)
   {
      ::B2Momentum *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::B2Momentum >(0);
      static ::ROOT::TGenericClassInfo 
         instance("B2Momentum", ::B2Momentum::Class_Version(), "B2Measurement.hh", 294,
                  typeid(::B2Momentum), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::B2Momentum::Dictionary, isa_proxy, 4,
                  sizeof(::B2Momentum) );
      instance.SetNew(&new_B2Momentum);
      instance.SetNewArray(&newArray_B2Momentum);
      instance.SetDelete(&delete_B2Momentum);
      instance.SetDeleteArray(&deleteArray_B2Momentum);
      instance.SetDestructor(&destruct_B2Momentum);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::B2Momentum*)
   {
      return GenerateInitInstanceLocal((::B2Momentum*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::B2Momentum*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_B2Angle(void *p = 0);
   static void *newArray_B2Angle(Long_t size, void *p);
   static void delete_B2Angle(void *p);
   static void deleteArray_B2Angle(void *p);
   static void destruct_B2Angle(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::B2Angle*)
   {
      ::B2Angle *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::B2Angle >(0);
      static ::ROOT::TGenericClassInfo 
         instance("B2Angle", ::B2Angle::Class_Version(), "B2Measurement.hh", 314,
                  typeid(::B2Angle), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::B2Angle::Dictionary, isa_proxy, 4,
                  sizeof(::B2Angle) );
      instance.SetNew(&new_B2Angle);
      instance.SetNewArray(&newArray_B2Angle);
      instance.SetDelete(&delete_B2Angle);
      instance.SetDeleteArray(&deleteArray_B2Angle);
      instance.SetDestructor(&destruct_B2Angle);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::B2Angle*)
   {
      return GenerateInitInstanceLocal((::B2Angle*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::B2Angle*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_B2Time(void *p = 0);
   static void *newArray_B2Time(Long_t size, void *p);
   static void delete_B2Time(void *p);
   static void deleteArray_B2Time(void *p);
   static void destruct_B2Time(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::B2Time*)
   {
      ::B2Time *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::B2Time >(0);
      static ::ROOT::TGenericClassInfo 
         instance("B2Time", ::B2Time::Class_Version(), "B2Measurement.hh", 332,
                  typeid(::B2Time), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::B2Time::Dictionary, isa_proxy, 4,
                  sizeof(::B2Time) );
      instance.SetNew(&new_B2Time);
      instance.SetNewArray(&newArray_B2Time);
      instance.SetDelete(&delete_B2Time);
      instance.SetDeleteArray(&deleteArray_B2Time);
      instance.SetDestructor(&destruct_B2Time);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::B2Time*)
   {
      return GenerateInitInstanceLocal((::B2Time*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::B2Time*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_B2Distance(void *p = 0);
   static void *newArray_B2Distance(Long_t size, void *p);
   static void delete_B2Distance(void *p);
   static void deleteArray_B2Distance(void *p);
   static void destruct_B2Distance(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::B2Distance*)
   {
      ::B2Distance *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::B2Distance >(0);
      static ::ROOT::TGenericClassInfo 
         instance("B2Distance", ::B2Distance::Class_Version(), "B2Measurement.hh", 350,
                  typeid(::B2Distance), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::B2Distance::Dictionary, isa_proxy, 4,
                  sizeof(::B2Distance) );
      instance.SetNew(&new_B2Distance);
      instance.SetNewArray(&newArray_B2Distance);
      instance.SetDelete(&delete_B2Distance);
      instance.SetDeleteArray(&deleteArray_B2Distance);
      instance.SetDestructor(&destruct_B2Distance);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::B2Distance*)
   {
      return GenerateInitInstanceLocal((::B2Distance*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::B2Distance*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_B2Position(void *p = 0);
   static void *newArray_B2Position(Long_t size, void *p);
   static void delete_B2Position(void *p);
   static void deleteArray_B2Position(void *p);
   static void destruct_B2Position(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::B2Position*)
   {
      ::B2Position *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::B2Position >(0);
      static ::ROOT::TGenericClassInfo 
         instance("B2Position", ::B2Position::Class_Version(), "B2Measurement.hh", 370,
                  typeid(::B2Position), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::B2Position::Dictionary, isa_proxy, 4,
                  sizeof(::B2Position) );
      instance.SetNew(&new_B2Position);
      instance.SetNewArray(&newArray_B2Position);
      instance.SetDelete(&delete_B2Position);
      instance.SetDeleteArray(&deleteArray_B2Position);
      instance.SetDestructor(&destruct_B2Position);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::B2Position*)
   {
      return GenerateInitInstanceLocal((::B2Position*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::B2Position*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_B2ViewAngle(void *p = 0);
   static void *newArray_B2ViewAngle(Long_t size, void *p);
   static void delete_B2ViewAngle(void *p);
   static void deleteArray_B2ViewAngle(void *p);
   static void destruct_B2ViewAngle(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::B2ViewAngle*)
   {
      ::B2ViewAngle *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::B2ViewAngle >(0);
      static ::ROOT::TGenericClassInfo 
         instance("B2ViewAngle", ::B2ViewAngle::Class_Version(), "B2Measurement.hh", 404,
                  typeid(::B2ViewAngle), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::B2ViewAngle::Dictionary, isa_proxy, 4,
                  sizeof(::B2ViewAngle) );
      instance.SetNew(&new_B2ViewAngle);
      instance.SetNewArray(&newArray_B2ViewAngle);
      instance.SetDelete(&delete_B2ViewAngle);
      instance.SetDeleteArray(&deleteArray_B2ViewAngle);
      instance.SetDestructor(&destruct_B2ViewAngle);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::B2ViewAngle*)
   {
      return GenerateInitInstanceLocal((::B2ViewAngle*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::B2ViewAngle*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_B2Direction(void *p = 0);
   static void *newArray_B2Direction(Long_t size, void *p);
   static void delete_B2Direction(void *p);
   static void deleteArray_B2Direction(void *p);
   static void destruct_B2Direction(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::B2Direction*)
   {
      ::B2Direction *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::B2Direction >(0);
      static ::ROOT::TGenericClassInfo 
         instance("B2Direction", ::B2Direction::Class_Version(), "B2Measurement.hh", 440,
                  typeid(::B2Direction), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::B2Direction::Dictionary, isa_proxy, 4,
                  sizeof(::B2Direction) );
      instance.SetNew(&new_B2Direction);
      instance.SetNewArray(&newArray_B2Direction);
      instance.SetDelete(&delete_B2Direction);
      instance.SetDeleteArray(&deleteArray_B2Direction);
      instance.SetDestructor(&destruct_B2Direction);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::B2Direction*)
   {
      return GenerateInitInstanceLocal((::B2Direction*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::B2Direction*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_B2Vector3(void *p = 0);
   static void *newArray_B2Vector3(Long_t size, void *p);
   static void delete_B2Vector3(void *p);
   static void deleteArray_B2Vector3(void *p);
   static void destruct_B2Vector3(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::B2Vector3*)
   {
      ::B2Vector3 *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::B2Vector3 >(0);
      static ::ROOT::TGenericClassInfo 
         instance("B2Vector3", ::B2Vector3::Class_Version(), "B2Measurement.hh", 471,
                  typeid(::B2Vector3), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::B2Vector3::Dictionary, isa_proxy, 4,
                  sizeof(::B2Vector3) );
      instance.SetNew(&new_B2Vector3);
      instance.SetNewArray(&newArray_B2Vector3);
      instance.SetDelete(&delete_B2Vector3);
      instance.SetDeleteArray(&deleteArray_B2Vector3);
      instance.SetDestructor(&destruct_B2Vector3);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::B2Vector3*)
   {
      return GenerateInitInstanceLocal((::B2Vector3*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::B2Vector3*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *_Rb_tree_const_iteratorlEB2SigmagR_Dictionary();
   static void _Rb_tree_const_iteratorlEB2SigmagR_TClassManip(TClass*);
   static void *new__Rb_tree_const_iteratorlEB2SigmagR(void *p = 0);
   static void *newArray__Rb_tree_const_iteratorlEB2SigmagR(Long_t size, void *p);
   static void delete__Rb_tree_const_iteratorlEB2SigmagR(void *p);
   static void deleteArray__Rb_tree_const_iteratorlEB2SigmagR(void *p);
   static void destruct__Rb_tree_const_iteratorlEB2SigmagR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::_Rb_tree_const_iterator<B2Sigma>*)
   {
      ::_Rb_tree_const_iterator<B2Sigma> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::_Rb_tree_const_iterator<B2Sigma>));
      static ::ROOT::TGenericClassInfo 
         instance("_Rb_tree_const_iterator<B2Sigma>", "map", 326,
                  typeid(::_Rb_tree_const_iterator<B2Sigma>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &_Rb_tree_const_iteratorlEB2SigmagR_Dictionary, isa_proxy, 4,
                  sizeof(::_Rb_tree_const_iterator<B2Sigma>) );
      instance.SetNew(&new__Rb_tree_const_iteratorlEB2SigmagR);
      instance.SetNewArray(&newArray__Rb_tree_const_iteratorlEB2SigmagR);
      instance.SetDelete(&delete__Rb_tree_const_iteratorlEB2SigmagR);
      instance.SetDeleteArray(&deleteArray__Rb_tree_const_iteratorlEB2SigmagR);
      instance.SetDestructor(&destruct__Rb_tree_const_iteratorlEB2SigmagR);

      ::ROOT::AddClassAlternate("_Rb_tree_const_iterator<B2Sigma>","set<B2Sigma>::iterator");

      ::ROOT::AddClassAlternate("_Rb_tree_const_iterator<B2Sigma>","std::_Rb_tree_const_iterator<B2Sigma>");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::_Rb_tree_const_iterator<B2Sigma>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *_Rb_tree_const_iteratorlEB2SigmagR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::_Rb_tree_const_iterator<B2Sigma>*)0x0)->GetClass();
      _Rb_tree_const_iteratorlEB2SigmagR_TClassManip(theClass);
   return theClass;
   }

   static void _Rb_tree_const_iteratorlEB2SigmagR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static void *new_B2HitSummary(void *p = 0);
   static void *newArray_B2HitSummary(Long_t size, void *p);
   static void delete_B2HitSummary(void *p);
   static void deleteArray_B2HitSummary(void *p);
   static void destruct_B2HitSummary(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::B2HitSummary*)
   {
      ::B2HitSummary *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::B2HitSummary >(0);
      static ::ROOT::TGenericClassInfo 
         instance("B2HitSummary", ::B2HitSummary::Class_Version(), "B2HitSummary.hh", 26,
                  typeid(::B2HitSummary), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::B2HitSummary::Dictionary, isa_proxy, 4,
                  sizeof(::B2HitSummary) );
      instance.SetNew(&new_B2HitSummary);
      instance.SetNewArray(&newArray_B2HitSummary);
      instance.SetDelete(&delete_B2HitSummary);
      instance.SetDeleteArray(&deleteArray_B2HitSummary);
      instance.SetDestructor(&destruct_B2HitSummary);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::B2HitSummary*)
   {
      return GenerateInitInstanceLocal((::B2HitSummary*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::B2HitSummary*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_B2RefArray(void *p = 0);
   static void *newArray_B2RefArray(Long_t size, void *p);
   static void delete_B2RefArray(void *p);
   static void deleteArray_B2RefArray(void *p);
   static void destruct_B2RefArray(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::B2RefArray*)
   {
      ::B2RefArray *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::B2RefArray >(0);
      static ::ROOT::TGenericClassInfo 
         instance("B2RefArray", ::B2RefArray::Class_Version(), "B2RefArray.hh", 16,
                  typeid(::B2RefArray), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::B2RefArray::Dictionary, isa_proxy, 4,
                  sizeof(::B2RefArray) );
      instance.SetNew(&new_B2RefArray);
      instance.SetNewArray(&newArray_B2RefArray);
      instance.SetDelete(&delete_B2RefArray);
      instance.SetDeleteArray(&deleteArray_B2RefArray);
      instance.SetDestructor(&destruct_B2RefArray);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::B2RefArray*)
   {
      return GenerateInitInstanceLocal((::B2RefArray*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::B2RefArray*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_B2HitsSet(void *p = 0);
   static void *newArray_B2HitsSet(Long_t size, void *p);
   static void delete_B2HitsSet(void *p);
   static void deleteArray_B2HitsSet(void *p);
   static void destruct_B2HitsSet(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::B2HitsSet*)
   {
      ::B2HitsSet *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::B2HitsSet >(0);
      static ::ROOT::TGenericClassInfo 
         instance("B2HitsSet", ::B2HitsSet::Class_Version(), "B2HitsSet.hh", 33,
                  typeid(::B2HitsSet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::B2HitsSet::Dictionary, isa_proxy, 4,
                  sizeof(::B2HitsSet) );
      instance.SetNew(&new_B2HitsSet);
      instance.SetNewArray(&newArray_B2HitsSet);
      instance.SetDelete(&delete_B2HitsSet);
      instance.SetDeleteArray(&deleteArray_B2HitsSet);
      instance.SetDestructor(&destruct_B2HitsSet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::B2HitsSet*)
   {
      return GenerateInitInstanceLocal((::B2HitsSet*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::B2HitsSet*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_B2ClusterSummary(void *p = 0);
   static void *newArray_B2ClusterSummary(Long_t size, void *p);
   static void delete_B2ClusterSummary(void *p);
   static void deleteArray_B2ClusterSummary(void *p);
   static void destruct_B2ClusterSummary(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::B2ClusterSummary*)
   {
      ::B2ClusterSummary *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::B2ClusterSummary >(0);
      static ::ROOT::TGenericClassInfo 
         instance("B2ClusterSummary", ::B2ClusterSummary::Class_Version(), "B2ClusterSummary.hh", 32,
                  typeid(::B2ClusterSummary), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::B2ClusterSummary::Dictionary, isa_proxy, 4,
                  sizeof(::B2ClusterSummary) );
      instance.SetNew(&new_B2ClusterSummary);
      instance.SetNewArray(&newArray_B2ClusterSummary);
      instance.SetDelete(&delete_B2ClusterSummary);
      instance.SetDeleteArray(&deleteArray_B2ClusterSummary);
      instance.SetDestructor(&destruct_B2ClusterSummary);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::B2ClusterSummary*)
   {
      return GenerateInitInstanceLocal((::B2ClusterSummary*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::B2ClusterSummary*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_B2TrackSummary(void *p = 0);
   static void *newArray_B2TrackSummary(Long_t size, void *p);
   static void delete_B2TrackSummary(void *p);
   static void deleteArray_B2TrackSummary(void *p);
   static void destruct_B2TrackSummary(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::B2TrackSummary*)
   {
      ::B2TrackSummary *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::B2TrackSummary >(0);
      static ::ROOT::TGenericClassInfo 
         instance("B2TrackSummary", ::B2TrackSummary::Class_Version(), "B2TrackSummary.hh", 37,
                  typeid(::B2TrackSummary), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::B2TrackSummary::Dictionary, isa_proxy, 4,
                  sizeof(::B2TrackSummary) );
      instance.SetNew(&new_B2TrackSummary);
      instance.SetNewArray(&newArray_B2TrackSummary);
      instance.SetDelete(&delete_B2TrackSummary);
      instance.SetDeleteArray(&deleteArray_B2TrackSummary);
      instance.SetDestructor(&destruct_B2TrackSummary);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::B2TrackSummary*)
   {
      return GenerateInitInstanceLocal((::B2TrackSummary*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::B2TrackSummary*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_B2VertexSummary(void *p = 0);
   static void *newArray_B2VertexSummary(Long_t size, void *p);
   static void delete_B2VertexSummary(void *p);
   static void deleteArray_B2VertexSummary(void *p);
   static void destruct_B2VertexSummary(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::B2VertexSummary*)
   {
      ::B2VertexSummary *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::B2VertexSummary >(0);
      static ::ROOT::TGenericClassInfo 
         instance("B2VertexSummary", ::B2VertexSummary::Class_Version(), "B2VertexSummary.hh", 27,
                  typeid(::B2VertexSummary), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::B2VertexSummary::Dictionary, isa_proxy, 4,
                  sizeof(::B2VertexSummary) );
      instance.SetNew(&new_B2VertexSummary);
      instance.SetNewArray(&newArray_B2VertexSummary);
      instance.SetDelete(&delete_B2VertexSummary);
      instance.SetDeleteArray(&deleteArray_B2VertexSummary);
      instance.SetDestructor(&destruct_B2VertexSummary);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::B2VertexSummary*)
   {
      return GenerateInitInstanceLocal((::B2VertexSummary*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::B2VertexSummary*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_B2BeamSummary(void *p = 0);
   static void *newArray_B2BeamSummary(Long_t size, void *p);
   static void delete_B2BeamSummary(void *p);
   static void deleteArray_B2BeamSummary(void *p);
   static void destruct_B2BeamSummary(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::B2BeamSummary*)
   {
      ::B2BeamSummary *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::B2BeamSummary >(0);
      static ::ROOT::TGenericClassInfo 
         instance("B2BeamSummary", ::B2BeamSummary::Class_Version(), "B2BeamSummary.hh", 12,
                  typeid(::B2BeamSummary), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::B2BeamSummary::Dictionary, isa_proxy, 4,
                  sizeof(::B2BeamSummary) );
      instance.SetNew(&new_B2BeamSummary);
      instance.SetNewArray(&newArray_B2BeamSummary);
      instance.SetDelete(&delete_B2BeamSummary);
      instance.SetDeleteArray(&deleteArray_B2BeamSummary);
      instance.SetDestructor(&destruct_B2BeamSummary);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::B2BeamSummary*)
   {
      return GenerateInitInstanceLocal((::B2BeamSummary*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::B2BeamSummary*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_B2EventSummary(void *p = 0);
   static void *newArray_B2EventSummary(Long_t size, void *p);
   static void delete_B2EventSummary(void *p);
   static void deleteArray_B2EventSummary(void *p);
   static void destruct_B2EventSummary(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::B2EventSummary*)
   {
      ::B2EventSummary *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::B2EventSummary >(0);
      static ::ROOT::TGenericClassInfo 
         instance("B2EventSummary", ::B2EventSummary::Class_Version(), "B2EventSummary.hh", 18,
                  typeid(::B2EventSummary), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::B2EventSummary::Dictionary, isa_proxy, 4,
                  sizeof(::B2EventSummary) );
      instance.SetNew(&new_B2EventSummary);
      instance.SetNewArray(&newArray_B2EventSummary);
      instance.SetDelete(&delete_B2EventSummary);
      instance.SetDeleteArray(&deleteArray_B2EventSummary);
      instance.SetDestructor(&destruct_B2EventSummary);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::B2EventSummary*)
   {
      return GenerateInitInstanceLocal((::B2EventSummary*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::B2EventSummary*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_B2SpillSummary(void *p = 0);
   static void *newArray_B2SpillSummary(Long_t size, void *p);
   static void delete_B2SpillSummary(void *p);
   static void deleteArray_B2SpillSummary(void *p);
   static void destruct_B2SpillSummary(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::B2SpillSummary*)
   {
      ::B2SpillSummary *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::B2SpillSummary >(0);
      static ::ROOT::TGenericClassInfo 
         instance("B2SpillSummary", ::B2SpillSummary::Class_Version(), "B2SpillSummary.hh", 42,
                  typeid(::B2SpillSummary), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::B2SpillSummary::Dictionary, isa_proxy, 4,
                  sizeof(::B2SpillSummary) );
      instance.SetNew(&new_B2SpillSummary);
      instance.SetNewArray(&newArray_B2SpillSummary);
      instance.SetDelete(&delete_B2SpillSummary);
      instance.SetDeleteArray(&deleteArray_B2SpillSummary);
      instance.SetDestructor(&destruct_B2SpillSummary);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::B2SpillSummary*)
   {
      return GenerateInitInstanceLocal((::B2SpillSummary*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::B2SpillSummary*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_B2EmulsionSummary(void *p = 0);
   static void *newArray_B2EmulsionSummary(Long_t size, void *p);
   static void delete_B2EmulsionSummary(void *p);
   static void deleteArray_B2EmulsionSummary(void *p);
   static void destruct_B2EmulsionSummary(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::B2EmulsionSummary*)
   {
      ::B2EmulsionSummary *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::B2EmulsionSummary >(0);
      static ::ROOT::TGenericClassInfo 
         instance("B2EmulsionSummary", ::B2EmulsionSummary::Class_Version(), "B2EmulsionSummary.hh", 31,
                  typeid(::B2EmulsionSummary), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::B2EmulsionSummary::Dictionary, isa_proxy, 4,
                  sizeof(::B2EmulsionSummary) );
      instance.SetNew(&new_B2EmulsionSummary);
      instance.SetNewArray(&newArray_B2EmulsionSummary);
      instance.SetDelete(&delete_B2EmulsionSummary);
      instance.SetDeleteArray(&deleteArray_B2EmulsionSummary);
      instance.SetDestructor(&destruct_B2EmulsionSummary);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::B2EmulsionSummary*)
   {
      return GenerateInitInstanceLocal((::B2EmulsionSummary*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::B2EmulsionSummary*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_B2Boundary(void *p = 0);
   static void *newArray_B2Boundary(Long_t size, void *p);
   static void delete_B2Boundary(void *p);
   static void deleteArray_B2Boundary(void *p);
   static void destruct_B2Boundary(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::B2Boundary*)
   {
      ::B2Boundary *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::B2Boundary >(0);
      static ::ROOT::TGenericClassInfo 
         instance("B2Boundary", ::B2Boundary::Class_Version(), "B2Boundary.hh", 13,
                  typeid(::B2Boundary), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::B2Boundary::Dictionary, isa_proxy, 4,
                  sizeof(::B2Boundary) );
      instance.SetNew(&new_B2Boundary);
      instance.SetNewArray(&newArray_B2Boundary);
      instance.SetDelete(&delete_B2Boundary);
      instance.SetDeleteArray(&deleteArray_B2Boundary);
      instance.SetDestructor(&destruct_B2Boundary);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::B2Boundary*)
   {
      return GenerateInitInstanceLocal((::B2Boundary*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::B2Boundary*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *B2SingleBoundarylEdoublegR_Dictionary();
   static void B2SingleBoundarylEdoublegR_TClassManip(TClass*);
   static void delete_B2SingleBoundarylEdoublegR(void *p);
   static void deleteArray_B2SingleBoundarylEdoublegR(void *p);
   static void destruct_B2SingleBoundarylEdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::B2SingleBoundary<double>*)
   {
      ::B2SingleBoundary<double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::B2SingleBoundary<double> >(0);
      static ::ROOT::TGenericClassInfo 
         instance("B2SingleBoundary<double>", ::B2SingleBoundary<double>::Class_Version(), "B2Boundary.hh", 29,
                  typeid(::B2SingleBoundary<double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &B2SingleBoundarylEdoublegR_Dictionary, isa_proxy, 4,
                  sizeof(::B2SingleBoundary<double>) );
      instance.SetDelete(&delete_B2SingleBoundarylEdoublegR);
      instance.SetDeleteArray(&deleteArray_B2SingleBoundarylEdoublegR);
      instance.SetDestructor(&destruct_B2SingleBoundarylEdoublegR);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::B2SingleBoundary<double>*)
   {
      return GenerateInitInstanceLocal((::B2SingleBoundary<double>*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::B2SingleBoundary<double>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *B2SingleBoundarylEdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::B2SingleBoundary<double>*)0x0)->GetClass();
      B2SingleBoundarylEdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void B2SingleBoundarylEdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *B2SingleBoundarylEintgR_Dictionary();
   static void B2SingleBoundarylEintgR_TClassManip(TClass*);
   static void delete_B2SingleBoundarylEintgR(void *p);
   static void deleteArray_B2SingleBoundarylEintgR(void *p);
   static void destruct_B2SingleBoundarylEintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::B2SingleBoundary<int>*)
   {
      ::B2SingleBoundary<int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::B2SingleBoundary<int> >(0);
      static ::ROOT::TGenericClassInfo 
         instance("B2SingleBoundary<int>", ::B2SingleBoundary<int>::Class_Version(), "B2Boundary.hh", 29,
                  typeid(::B2SingleBoundary<int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &B2SingleBoundarylEintgR_Dictionary, isa_proxy, 4,
                  sizeof(::B2SingleBoundary<int>) );
      instance.SetDelete(&delete_B2SingleBoundarylEintgR);
      instance.SetDeleteArray(&deleteArray_B2SingleBoundarylEintgR);
      instance.SetDestructor(&destruct_B2SingleBoundarylEintgR);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::B2SingleBoundary<int>*)
   {
      return GenerateInitInstanceLocal((::B2SingleBoundary<int>*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::B2SingleBoundary<int>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *B2SingleBoundarylEintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::B2SingleBoundary<int>*)0x0)->GetClass();
      B2SingleBoundarylEintgR_TClassManip(theClass);
   return theClass;
   }

   static void B2SingleBoundarylEintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *B2DoubleBoundarylEvectorlEdoublegRsPgR_Dictionary();
   static void B2DoubleBoundarylEvectorlEdoublegRsPgR_TClassManip(TClass*);
   static void delete_B2DoubleBoundarylEvectorlEdoublegRsPgR(void *p);
   static void deleteArray_B2DoubleBoundarylEvectorlEdoublegRsPgR(void *p);
   static void destruct_B2DoubleBoundarylEvectorlEdoublegRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::B2DoubleBoundary<vector<double> >*)
   {
      ::B2DoubleBoundary<vector<double> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::B2DoubleBoundary<vector<double> > >(0);
      static ::ROOT::TGenericClassInfo 
         instance("B2DoubleBoundary<vector<double> >", ::B2DoubleBoundary<vector<double> >::Class_Version(), "B2Boundary.hh", 49,
                  typeid(::B2DoubleBoundary<vector<double> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &B2DoubleBoundarylEvectorlEdoublegRsPgR_Dictionary, isa_proxy, 4,
                  sizeof(::B2DoubleBoundary<vector<double> >) );
      instance.SetDelete(&delete_B2DoubleBoundarylEvectorlEdoublegRsPgR);
      instance.SetDeleteArray(&deleteArray_B2DoubleBoundarylEvectorlEdoublegRsPgR);
      instance.SetDestructor(&destruct_B2DoubleBoundarylEvectorlEdoublegRsPgR);

      ::ROOT::AddClassAlternate("B2DoubleBoundary<vector<double> >","B2DoubleBoundary<std::vector<double> >");

      ::ROOT::AddClassAlternate("B2DoubleBoundary<vector<double> >","B2DoubleBoundary<std::vector<double, std::allocator<double> > >");
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::B2DoubleBoundary<vector<double> >*)
   {
      return GenerateInitInstanceLocal((::B2DoubleBoundary<vector<double> >*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::B2DoubleBoundary<vector<double> >*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *B2DoubleBoundarylEvectorlEdoublegRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::B2DoubleBoundary<vector<double> >*)0x0)->GetClass();
      B2DoubleBoundarylEvectorlEdoublegRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void B2DoubleBoundarylEvectorlEdoublegRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *B2DoubleBoundarylEvectorlEintgRsPgR_Dictionary();
   static void B2DoubleBoundarylEvectorlEintgRsPgR_TClassManip(TClass*);
   static void delete_B2DoubleBoundarylEvectorlEintgRsPgR(void *p);
   static void deleteArray_B2DoubleBoundarylEvectorlEintgRsPgR(void *p);
   static void destruct_B2DoubleBoundarylEvectorlEintgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::B2DoubleBoundary<vector<int> >*)
   {
      ::B2DoubleBoundary<vector<int> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::B2DoubleBoundary<vector<int> > >(0);
      static ::ROOT::TGenericClassInfo 
         instance("B2DoubleBoundary<vector<int> >", ::B2DoubleBoundary<vector<int> >::Class_Version(), "B2Boundary.hh", 49,
                  typeid(::B2DoubleBoundary<vector<int> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &B2DoubleBoundarylEvectorlEintgRsPgR_Dictionary, isa_proxy, 4,
                  sizeof(::B2DoubleBoundary<vector<int> >) );
      instance.SetDelete(&delete_B2DoubleBoundarylEvectorlEintgRsPgR);
      instance.SetDeleteArray(&deleteArray_B2DoubleBoundarylEvectorlEintgRsPgR);
      instance.SetDestructor(&destruct_B2DoubleBoundarylEvectorlEintgRsPgR);

      ::ROOT::AddClassAlternate("B2DoubleBoundary<vector<int> >","B2DoubleBoundary<std::vector<int> >");

      ::ROOT::AddClassAlternate("B2DoubleBoundary<vector<int> >","B2DoubleBoundary<std::vector<int, std::allocator<int> > >");
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::B2DoubleBoundary<vector<int> >*)
   {
      return GenerateInitInstanceLocal((::B2DoubleBoundary<vector<int> >*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::B2DoubleBoundary<vector<int> >*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *B2DoubleBoundarylEvectorlEintgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::B2DoubleBoundary<vector<int> >*)0x0)->GetClass();
      B2DoubleBoundarylEvectorlEintgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void B2DoubleBoundarylEvectorlEintgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *B2PointLikeBoundarylEvectorlEdoublegRsPgR_Dictionary();
   static void B2PointLikeBoundarylEvectorlEdoublegRsPgR_TClassManip(TClass*);
   static void delete_B2PointLikeBoundarylEvectorlEdoublegRsPgR(void *p);
   static void deleteArray_B2PointLikeBoundarylEvectorlEdoublegRsPgR(void *p);
   static void destruct_B2PointLikeBoundarylEvectorlEdoublegRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::B2PointLikeBoundary<vector<double> >*)
   {
      ::B2PointLikeBoundary<vector<double> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::B2PointLikeBoundary<vector<double> > >(0);
      static ::ROOT::TGenericClassInfo 
         instance("B2PointLikeBoundary<vector<double> >", ::B2PointLikeBoundary<vector<double> >::Class_Version(), "B2Boundary.hh", 69,
                  typeid(::B2PointLikeBoundary<vector<double> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &B2PointLikeBoundarylEvectorlEdoublegRsPgR_Dictionary, isa_proxy, 4,
                  sizeof(::B2PointLikeBoundary<vector<double> >) );
      instance.SetDelete(&delete_B2PointLikeBoundarylEvectorlEdoublegRsPgR);
      instance.SetDeleteArray(&deleteArray_B2PointLikeBoundarylEvectorlEdoublegRsPgR);
      instance.SetDestructor(&destruct_B2PointLikeBoundarylEvectorlEdoublegRsPgR);

      ::ROOT::AddClassAlternate("B2PointLikeBoundary<vector<double> >","B2PointLikeBoundary<std::vector<double> >");

      ::ROOT::AddClassAlternate("B2PointLikeBoundary<vector<double> >","B2PointLikeBoundary<std::vector<double, std::allocator<double> > >");
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::B2PointLikeBoundary<vector<double> >*)
   {
      return GenerateInitInstanceLocal((::B2PointLikeBoundary<vector<double> >*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::B2PointLikeBoundary<vector<double> >*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *B2PointLikeBoundarylEvectorlEdoublegRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::B2PointLikeBoundary<vector<double> >*)0x0)->GetClass();
      B2PointLikeBoundarylEvectorlEdoublegRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void B2PointLikeBoundarylEvectorlEdoublegRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *B2PointLikeBoundarylEvectorlEintgRsPgR_Dictionary();
   static void B2PointLikeBoundarylEvectorlEintgRsPgR_TClassManip(TClass*);
   static void delete_B2PointLikeBoundarylEvectorlEintgRsPgR(void *p);
   static void deleteArray_B2PointLikeBoundarylEvectorlEintgRsPgR(void *p);
   static void destruct_B2PointLikeBoundarylEvectorlEintgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::B2PointLikeBoundary<vector<int> >*)
   {
      ::B2PointLikeBoundary<vector<int> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::B2PointLikeBoundary<vector<int> > >(0);
      static ::ROOT::TGenericClassInfo 
         instance("B2PointLikeBoundary<vector<int> >", ::B2PointLikeBoundary<vector<int> >::Class_Version(), "B2Boundary.hh", 69,
                  typeid(::B2PointLikeBoundary<vector<int> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &B2PointLikeBoundarylEvectorlEintgRsPgR_Dictionary, isa_proxy, 4,
                  sizeof(::B2PointLikeBoundary<vector<int> >) );
      instance.SetDelete(&delete_B2PointLikeBoundarylEvectorlEintgRsPgR);
      instance.SetDeleteArray(&deleteArray_B2PointLikeBoundarylEvectorlEintgRsPgR);
      instance.SetDestructor(&destruct_B2PointLikeBoundarylEvectorlEintgRsPgR);

      ::ROOT::AddClassAlternate("B2PointLikeBoundary<vector<int> >","B2PointLikeBoundary<std::vector<int> >");

      ::ROOT::AddClassAlternate("B2PointLikeBoundary<vector<int> >","B2PointLikeBoundary<std::vector<int, std::allocator<int> > >");
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::B2PointLikeBoundary<vector<int> >*)
   {
      return GenerateInitInstanceLocal((::B2PointLikeBoundary<vector<int> >*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::B2PointLikeBoundary<vector<int> >*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *B2PointLikeBoundarylEvectorlEintgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::B2PointLikeBoundary<vector<int> >*)0x0)->GetClass();
      B2PointLikeBoundarylEvectorlEintgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void B2PointLikeBoundarylEvectorlEintgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static void delete_B2DoubleBoundarySet(void *p);
   static void deleteArray_B2DoubleBoundarySet(void *p);
   static void destruct_B2DoubleBoundarySet(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::B2DoubleBoundarySet*)
   {
      ::B2DoubleBoundarySet *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::B2DoubleBoundarySet >(0);
      static ::ROOT::TGenericClassInfo 
         instance("B2DoubleBoundarySet", ::B2DoubleBoundarySet::Class_Version(), "B2Boundary.hh", 88,
                  typeid(::B2DoubleBoundarySet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::B2DoubleBoundarySet::Dictionary, isa_proxy, 4,
                  sizeof(::B2DoubleBoundarySet) );
      instance.SetDelete(&delete_B2DoubleBoundarySet);
      instance.SetDeleteArray(&deleteArray_B2DoubleBoundarySet);
      instance.SetDestructor(&destruct_B2DoubleBoundarySet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::B2DoubleBoundarySet*)
   {
      return GenerateInitInstanceLocal((::B2DoubleBoundarySet*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::B2DoubleBoundarySet*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_B2SigmaList(void *p = 0);
   static void *newArray_B2SigmaList(Long_t size, void *p);
   static void delete_B2SigmaList(void *p);
   static void deleteArray_B2SigmaList(void *p);
   static void destruct_B2SigmaList(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::B2SigmaList*)
   {
      ::B2SigmaList *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::B2SigmaList >(0);
      static ::ROOT::TGenericClassInfo 
         instance("B2SigmaList", ::B2SigmaList::Class_Version(), "B2SigmaList.hh", 27,
                  typeid(::B2SigmaList), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::B2SigmaList::Dictionary, isa_proxy, 4,
                  sizeof(::B2SigmaList) );
      instance.SetNew(&new_B2SigmaList);
      instance.SetNewArray(&newArray_B2SigmaList);
      instance.SetDelete(&delete_B2SigmaList);
      instance.SetDeleteArray(&deleteArray_B2SigmaList);
      instance.SetDestructor(&destruct_B2SigmaList);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::B2SigmaList*)
   {
      return GenerateInitInstanceLocal((::B2SigmaList*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::B2SigmaList*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_B2Dial(void *p = 0);
   static void *newArray_B2Dial(Long_t size, void *p);
   static void delete_B2Dial(void *p);
   static void deleteArray_B2Dial(void *p);
   static void destruct_B2Dial(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::B2Dial*)
   {
      ::B2Dial *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::B2Dial >(0);
      static ::ROOT::TGenericClassInfo 
         instance("B2Dial", ::B2Dial::Class_Version(), "B2Dial.hh", 76,
                  typeid(::B2Dial), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::B2Dial::Dictionary, isa_proxy, 4,
                  sizeof(::B2Dial) );
      instance.SetNew(&new_B2Dial);
      instance.SetNewArray(&newArray_B2Dial);
      instance.SetDelete(&delete_B2Dial);
      instance.SetDeleteArray(&deleteArray_B2Dial);
      instance.SetDestructor(&destruct_B2Dial);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::B2Dial*)
   {
      return GenerateInitInstanceLocal((::B2Dial*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::B2Dial*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_B2DialList(void *p = 0);
   static void *newArray_B2DialList(Long_t size, void *p);
   static void delete_B2DialList(void *p);
   static void deleteArray_B2DialList(void *p);
   static void destruct_B2DialList(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::B2DialList*)
   {
      ::B2DialList *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::B2DialList >(0);
      static ::ROOT::TGenericClassInfo 
         instance("B2DialList", ::B2DialList::Class_Version(), "B2DialList.hh", 38,
                  typeid(::B2DialList), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::B2DialList::Dictionary, isa_proxy, 4,
                  sizeof(::B2DialList) );
      instance.SetNew(&new_B2DialList);
      instance.SetNewArray(&newArray_B2DialList);
      instance.SetDelete(&delete_B2DialList);
      instance.SetDeleteArray(&deleteArray_B2DialList);
      instance.SetDestructor(&destruct_B2DialList);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::B2DialList*)
   {
      return GenerateInitInstanceLocal((::B2DialList*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::B2DialList*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr B2Measurement1D::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *B2Measurement1D::Class_Name()
{
   return "B2Measurement1D";
}

//______________________________________________________________________________
const char *B2Measurement1D::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2Measurement1D*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int B2Measurement1D::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2Measurement1D*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *B2Measurement1D::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2Measurement1D*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *B2Measurement1D::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2Measurement1D*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr B2Measurement2D::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *B2Measurement2D::Class_Name()
{
   return "B2Measurement2D";
}

//______________________________________________________________________________
const char *B2Measurement2D::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2Measurement2D*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int B2Measurement2D::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2Measurement2D*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *B2Measurement2D::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2Measurement2D*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *B2Measurement2D::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2Measurement2D*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr B2Measurement3D::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *B2Measurement3D::Class_Name()
{
   return "B2Measurement3D";
}

//______________________________________________________________________________
const char *B2Measurement3D::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2Measurement3D*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int B2Measurement3D::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2Measurement3D*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *B2Measurement3D::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2Measurement3D*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *B2Measurement3D::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2Measurement3D*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
template <> atomic_TClass_ptr B2VectorDoubleReadout<int>::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *B2VectorDoubleReadout<int>::Class_Name()
{
   return "B2VectorDoubleReadout<int>";
}

//______________________________________________________________________________
template <> const char *B2VectorDoubleReadout<int>::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2VectorDoubleReadout<int>*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
template <> int B2VectorDoubleReadout<int>::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2VectorDoubleReadout<int>*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *B2VectorDoubleReadout<int>::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2VectorDoubleReadout<int>*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *B2VectorDoubleReadout<int>::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2VectorDoubleReadout<int>*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
template <> atomic_TClass_ptr B2VectorDoubleReadout<double>::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *B2VectorDoubleReadout<double>::Class_Name()
{
   return "B2VectorDoubleReadout<double>";
}

//______________________________________________________________________________
template <> const char *B2VectorDoubleReadout<double>::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2VectorDoubleReadout<double>*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
template <> int B2VectorDoubleReadout<double>::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2VectorDoubleReadout<double>*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *B2VectorDoubleReadout<double>::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2VectorDoubleReadout<double>*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *B2VectorDoubleReadout<double>::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2VectorDoubleReadout<double>*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
template <> atomic_TClass_ptr B2VectorDoubleReadout<B2Vector3>::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *B2VectorDoubleReadout<B2Vector3>::Class_Name()
{
   return "B2VectorDoubleReadout<B2Vector3>";
}

//______________________________________________________________________________
template <> const char *B2VectorDoubleReadout<B2Vector3>::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2VectorDoubleReadout<B2Vector3>*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
template <> int B2VectorDoubleReadout<B2Vector3>::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2VectorDoubleReadout<B2Vector3>*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *B2VectorDoubleReadout<B2Vector3>::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2VectorDoubleReadout<B2Vector3>*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *B2VectorDoubleReadout<B2Vector3>::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2VectorDoubleReadout<B2Vector3>*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr B2Energy::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *B2Energy::Class_Name()
{
   return "B2Energy";
}

//______________________________________________________________________________
const char *B2Energy::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2Energy*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int B2Energy::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2Energy*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *B2Energy::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2Energy*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *B2Energy::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2Energy*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr B2Momentum::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *B2Momentum::Class_Name()
{
   return "B2Momentum";
}

//______________________________________________________________________________
const char *B2Momentum::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2Momentum*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int B2Momentum::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2Momentum*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *B2Momentum::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2Momentum*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *B2Momentum::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2Momentum*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr B2Angle::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *B2Angle::Class_Name()
{
   return "B2Angle";
}

//______________________________________________________________________________
const char *B2Angle::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2Angle*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int B2Angle::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2Angle*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *B2Angle::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2Angle*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *B2Angle::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2Angle*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr B2Time::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *B2Time::Class_Name()
{
   return "B2Time";
}

//______________________________________________________________________________
const char *B2Time::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2Time*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int B2Time::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2Time*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *B2Time::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2Time*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *B2Time::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2Time*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr B2Distance::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *B2Distance::Class_Name()
{
   return "B2Distance";
}

//______________________________________________________________________________
const char *B2Distance::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2Distance*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int B2Distance::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2Distance*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *B2Distance::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2Distance*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *B2Distance::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2Distance*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr B2Position::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *B2Position::Class_Name()
{
   return "B2Position";
}

//______________________________________________________________________________
const char *B2Position::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2Position*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int B2Position::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2Position*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *B2Position::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2Position*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *B2Position::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2Position*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr B2ViewAngle::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *B2ViewAngle::Class_Name()
{
   return "B2ViewAngle";
}

//______________________________________________________________________________
const char *B2ViewAngle::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2ViewAngle*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int B2ViewAngle::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2ViewAngle*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *B2ViewAngle::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2ViewAngle*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *B2ViewAngle::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2ViewAngle*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr B2Direction::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *B2Direction::Class_Name()
{
   return "B2Direction";
}

//______________________________________________________________________________
const char *B2Direction::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2Direction*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int B2Direction::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2Direction*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *B2Direction::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2Direction*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *B2Direction::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2Direction*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr B2Vector3::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *B2Vector3::Class_Name()
{
   return "B2Vector3";
}

//______________________________________________________________________________
const char *B2Vector3::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2Vector3*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int B2Vector3::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2Vector3*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *B2Vector3::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2Vector3*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *B2Vector3::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2Vector3*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr B2HitSummary::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *B2HitSummary::Class_Name()
{
   return "B2HitSummary";
}

//______________________________________________________________________________
const char *B2HitSummary::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2HitSummary*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int B2HitSummary::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2HitSummary*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *B2HitSummary::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2HitSummary*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *B2HitSummary::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2HitSummary*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr B2RefArray::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *B2RefArray::Class_Name()
{
   return "B2RefArray";
}

//______________________________________________________________________________
const char *B2RefArray::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2RefArray*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int B2RefArray::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2RefArray*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *B2RefArray::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2RefArray*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *B2RefArray::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2RefArray*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr B2HitsSet::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *B2HitsSet::Class_Name()
{
   return "B2HitsSet";
}

//______________________________________________________________________________
const char *B2HitsSet::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2HitsSet*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int B2HitsSet::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2HitsSet*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *B2HitsSet::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2HitsSet*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *B2HitsSet::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2HitsSet*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr B2ClusterSummary::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *B2ClusterSummary::Class_Name()
{
   return "B2ClusterSummary";
}

//______________________________________________________________________________
const char *B2ClusterSummary::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2ClusterSummary*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int B2ClusterSummary::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2ClusterSummary*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *B2ClusterSummary::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2ClusterSummary*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *B2ClusterSummary::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2ClusterSummary*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr B2TrackSummary::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *B2TrackSummary::Class_Name()
{
   return "B2TrackSummary";
}

//______________________________________________________________________________
const char *B2TrackSummary::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2TrackSummary*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int B2TrackSummary::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2TrackSummary*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *B2TrackSummary::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2TrackSummary*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *B2TrackSummary::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2TrackSummary*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr B2VertexSummary::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *B2VertexSummary::Class_Name()
{
   return "B2VertexSummary";
}

//______________________________________________________________________________
const char *B2VertexSummary::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2VertexSummary*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int B2VertexSummary::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2VertexSummary*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *B2VertexSummary::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2VertexSummary*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *B2VertexSummary::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2VertexSummary*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr B2BeamSummary::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *B2BeamSummary::Class_Name()
{
   return "B2BeamSummary";
}

//______________________________________________________________________________
const char *B2BeamSummary::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2BeamSummary*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int B2BeamSummary::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2BeamSummary*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *B2BeamSummary::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2BeamSummary*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *B2BeamSummary::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2BeamSummary*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr B2EventSummary::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *B2EventSummary::Class_Name()
{
   return "B2EventSummary";
}

//______________________________________________________________________________
const char *B2EventSummary::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2EventSummary*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int B2EventSummary::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2EventSummary*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *B2EventSummary::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2EventSummary*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *B2EventSummary::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2EventSummary*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr B2SpillSummary::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *B2SpillSummary::Class_Name()
{
   return "B2SpillSummary";
}

//______________________________________________________________________________
const char *B2SpillSummary::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2SpillSummary*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int B2SpillSummary::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2SpillSummary*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *B2SpillSummary::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2SpillSummary*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *B2SpillSummary::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2SpillSummary*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr B2EmulsionSummary::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *B2EmulsionSummary::Class_Name()
{
   return "B2EmulsionSummary";
}

//______________________________________________________________________________
const char *B2EmulsionSummary::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2EmulsionSummary*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int B2EmulsionSummary::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2EmulsionSummary*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *B2EmulsionSummary::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2EmulsionSummary*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *B2EmulsionSummary::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2EmulsionSummary*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr B2Boundary::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *B2Boundary::Class_Name()
{
   return "B2Boundary";
}

//______________________________________________________________________________
const char *B2Boundary::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2Boundary*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int B2Boundary::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2Boundary*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *B2Boundary::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2Boundary*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *B2Boundary::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2Boundary*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
template <> atomic_TClass_ptr B2SingleBoundary<double>::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *B2SingleBoundary<double>::Class_Name()
{
   return "B2SingleBoundary<double>";
}

//______________________________________________________________________________
template <> const char *B2SingleBoundary<double>::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2SingleBoundary<double>*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
template <> int B2SingleBoundary<double>::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2SingleBoundary<double>*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *B2SingleBoundary<double>::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2SingleBoundary<double>*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *B2SingleBoundary<double>::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2SingleBoundary<double>*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
template <> atomic_TClass_ptr B2SingleBoundary<int>::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *B2SingleBoundary<int>::Class_Name()
{
   return "B2SingleBoundary<int>";
}

//______________________________________________________________________________
template <> const char *B2SingleBoundary<int>::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2SingleBoundary<int>*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
template <> int B2SingleBoundary<int>::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2SingleBoundary<int>*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *B2SingleBoundary<int>::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2SingleBoundary<int>*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *B2SingleBoundary<int>::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2SingleBoundary<int>*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
template <> atomic_TClass_ptr B2DoubleBoundary<vector<double> >::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *B2DoubleBoundary<vector<double> >::Class_Name()
{
   return "B2DoubleBoundary<vector<double> >";
}

//______________________________________________________________________________
template <> const char *B2DoubleBoundary<vector<double> >::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2DoubleBoundary<vector<double> >*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
template <> int B2DoubleBoundary<vector<double> >::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2DoubleBoundary<vector<double> >*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *B2DoubleBoundary<vector<double> >::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2DoubleBoundary<vector<double> >*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *B2DoubleBoundary<vector<double> >::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2DoubleBoundary<vector<double> >*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
template <> atomic_TClass_ptr B2DoubleBoundary<vector<int> >::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *B2DoubleBoundary<vector<int> >::Class_Name()
{
   return "B2DoubleBoundary<vector<int> >";
}

//______________________________________________________________________________
template <> const char *B2DoubleBoundary<vector<int> >::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2DoubleBoundary<vector<int> >*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
template <> int B2DoubleBoundary<vector<int> >::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2DoubleBoundary<vector<int> >*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *B2DoubleBoundary<vector<int> >::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2DoubleBoundary<vector<int> >*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *B2DoubleBoundary<vector<int> >::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2DoubleBoundary<vector<int> >*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
template <> atomic_TClass_ptr B2PointLikeBoundary<vector<double> >::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *B2PointLikeBoundary<vector<double> >::Class_Name()
{
   return "B2PointLikeBoundary<vector<double> >";
}

//______________________________________________________________________________
template <> const char *B2PointLikeBoundary<vector<double> >::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2PointLikeBoundary<vector<double> >*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
template <> int B2PointLikeBoundary<vector<double> >::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2PointLikeBoundary<vector<double> >*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *B2PointLikeBoundary<vector<double> >::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2PointLikeBoundary<vector<double> >*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *B2PointLikeBoundary<vector<double> >::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2PointLikeBoundary<vector<double> >*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
template <> atomic_TClass_ptr B2PointLikeBoundary<vector<int> >::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *B2PointLikeBoundary<vector<int> >::Class_Name()
{
   return "B2PointLikeBoundary<vector<int> >";
}

//______________________________________________________________________________
template <> const char *B2PointLikeBoundary<vector<int> >::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2PointLikeBoundary<vector<int> >*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
template <> int B2PointLikeBoundary<vector<int> >::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2PointLikeBoundary<vector<int> >*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *B2PointLikeBoundary<vector<int> >::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2PointLikeBoundary<vector<int> >*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *B2PointLikeBoundary<vector<int> >::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2PointLikeBoundary<vector<int> >*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr B2DoubleBoundarySet::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *B2DoubleBoundarySet::Class_Name()
{
   return "B2DoubleBoundarySet";
}

//______________________________________________________________________________
const char *B2DoubleBoundarySet::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2DoubleBoundarySet*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int B2DoubleBoundarySet::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2DoubleBoundarySet*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *B2DoubleBoundarySet::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2DoubleBoundarySet*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *B2DoubleBoundarySet::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2DoubleBoundarySet*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr B2SigmaList::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *B2SigmaList::Class_Name()
{
   return "B2SigmaList";
}

//______________________________________________________________________________
const char *B2SigmaList::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2SigmaList*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int B2SigmaList::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2SigmaList*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *B2SigmaList::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2SigmaList*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *B2SigmaList::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2SigmaList*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr B2Dial::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *B2Dial::Class_Name()
{
   return "B2Dial";
}

//______________________________________________________________________________
const char *B2Dial::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2Dial*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int B2Dial::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2Dial*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *B2Dial::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2Dial*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *B2Dial::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2Dial*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr B2DialList::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *B2DialList::Class_Name()
{
   return "B2DialList";
}

//______________________________________________________________________________
const char *B2DialList::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2DialList*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int B2DialList::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::B2DialList*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *B2DialList::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2DialList*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *B2DialList::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::B2DialList*)0x0)->GetClass(); }
   return fgIsA;
}

namespace ROOT {
   // Wrappers around operator new
   static void *new___gnu_cxxcLcL__normal_iteratorlEB2DialmUcOvectorlEB2DialgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::__gnu_cxx::__normal_iterator<B2Dial*,vector<B2Dial> > : new ::__gnu_cxx::__normal_iterator<B2Dial*,vector<B2Dial> >;
   }
   static void *newArray___gnu_cxxcLcL__normal_iteratorlEB2DialmUcOvectorlEB2DialgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::__gnu_cxx::__normal_iterator<B2Dial*,vector<B2Dial> >[nElements] : new ::__gnu_cxx::__normal_iterator<B2Dial*,vector<B2Dial> >[nElements];
   }
   // Wrapper around operator delete
   static void delete___gnu_cxxcLcL__normal_iteratorlEB2DialmUcOvectorlEB2DialgRsPgR(void *p) {
      delete ((::__gnu_cxx::__normal_iterator<B2Dial*,vector<B2Dial> >*)p);
   }
   static void deleteArray___gnu_cxxcLcL__normal_iteratorlEB2DialmUcOvectorlEB2DialgRsPgR(void *p) {
      delete [] ((::__gnu_cxx::__normal_iterator<B2Dial*,vector<B2Dial> >*)p);
   }
   static void destruct___gnu_cxxcLcL__normal_iteratorlEB2DialmUcOvectorlEB2DialgRsPgR(void *p) {
      typedef ::__gnu_cxx::__normal_iterator<B2Dial*,vector<B2Dial> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::__gnu_cxx::__normal_iterator<B2Dial*,vector<B2Dial> >

namespace ROOT {
   // Wrappers around operator new
   static void *new___gnu_cxxcLcL__normal_iteratorlEconstsPB2DialmUcOvectorlEB2DialgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::__gnu_cxx::__normal_iterator<const B2Dial*,vector<B2Dial> > : new ::__gnu_cxx::__normal_iterator<const B2Dial*,vector<B2Dial> >;
   }
   static void *newArray___gnu_cxxcLcL__normal_iteratorlEconstsPB2DialmUcOvectorlEB2DialgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::__gnu_cxx::__normal_iterator<const B2Dial*,vector<B2Dial> >[nElements] : new ::__gnu_cxx::__normal_iterator<const B2Dial*,vector<B2Dial> >[nElements];
   }
   // Wrapper around operator delete
   static void delete___gnu_cxxcLcL__normal_iteratorlEconstsPB2DialmUcOvectorlEB2DialgRsPgR(void *p) {
      delete ((::__gnu_cxx::__normal_iterator<const B2Dial*,vector<B2Dial> >*)p);
   }
   static void deleteArray___gnu_cxxcLcL__normal_iteratorlEconstsPB2DialmUcOvectorlEB2DialgRsPgR(void *p) {
      delete [] ((::__gnu_cxx::__normal_iterator<const B2Dial*,vector<B2Dial> >*)p);
   }
   static void destruct___gnu_cxxcLcL__normal_iteratorlEconstsPB2DialmUcOvectorlEB2DialgRsPgR(void *p) {
      typedef ::__gnu_cxx::__normal_iterator<const B2Dial*,vector<B2Dial> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::__gnu_cxx::__normal_iterator<const B2Dial*,vector<B2Dial> >

//______________________________________________________________________________
void B2Measurement1D::Streamer(TBuffer &R__b)
{
   // Stream an object of class B2Measurement1D.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(B2Measurement1D::Class(),this);
   } else {
      R__b.WriteClassBuffer(B2Measurement1D::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_B2Measurement1D(void *p) {
      return  p ? new(p) ::B2Measurement1D : new ::B2Measurement1D;
   }
   static void *newArray_B2Measurement1D(Long_t nElements, void *p) {
      return p ? new(p) ::B2Measurement1D[nElements] : new ::B2Measurement1D[nElements];
   }
   // Wrapper around operator delete
   static void delete_B2Measurement1D(void *p) {
      delete ((::B2Measurement1D*)p);
   }
   static void deleteArray_B2Measurement1D(void *p) {
      delete [] ((::B2Measurement1D*)p);
   }
   static void destruct_B2Measurement1D(void *p) {
      typedef ::B2Measurement1D current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::B2Measurement1D

//______________________________________________________________________________
void B2Measurement2D::Streamer(TBuffer &R__b)
{
   // Stream an object of class B2Measurement2D.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(B2Measurement2D::Class(),this);
   } else {
      R__b.WriteClassBuffer(B2Measurement2D::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_B2Measurement2D(void *p) {
      return  p ? new(p) ::B2Measurement2D : new ::B2Measurement2D;
   }
   static void *newArray_B2Measurement2D(Long_t nElements, void *p) {
      return p ? new(p) ::B2Measurement2D[nElements] : new ::B2Measurement2D[nElements];
   }
   // Wrapper around operator delete
   static void delete_B2Measurement2D(void *p) {
      delete ((::B2Measurement2D*)p);
   }
   static void deleteArray_B2Measurement2D(void *p) {
      delete [] ((::B2Measurement2D*)p);
   }
   static void destruct_B2Measurement2D(void *p) {
      typedef ::B2Measurement2D current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::B2Measurement2D

//______________________________________________________________________________
void B2Measurement3D::Streamer(TBuffer &R__b)
{
   // Stream an object of class B2Measurement3D.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(B2Measurement3D::Class(),this);
   } else {
      R__b.WriteClassBuffer(B2Measurement3D::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_B2Measurement3D(void *p) {
      return  p ? new(p) ::B2Measurement3D : new ::B2Measurement3D;
   }
   static void *newArray_B2Measurement3D(Long_t nElements, void *p) {
      return p ? new(p) ::B2Measurement3D[nElements] : new ::B2Measurement3D[nElements];
   }
   // Wrapper around operator delete
   static void delete_B2Measurement3D(void *p) {
      delete ((::B2Measurement3D*)p);
   }
   static void deleteArray_B2Measurement3D(void *p) {
      delete [] ((::B2Measurement3D*)p);
   }
   static void destruct_B2Measurement3D(void *p) {
      typedef ::B2Measurement3D current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::B2Measurement3D

//______________________________________________________________________________
template <> void B2VectorDoubleReadout<int>::Streamer(TBuffer &R__b)
{
   // Stream an object of class B2VectorDoubleReadout<int>.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(B2VectorDoubleReadout<int>::Class(),this);
   } else {
      R__b.WriteClassBuffer(B2VectorDoubleReadout<int>::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_B2VectorDoubleReadoutlEintgR(void *p) {
      return  p ? new(p) ::B2VectorDoubleReadout<int> : new ::B2VectorDoubleReadout<int>;
   }
   static void *newArray_B2VectorDoubleReadoutlEintgR(Long_t nElements, void *p) {
      return p ? new(p) ::B2VectorDoubleReadout<int>[nElements] : new ::B2VectorDoubleReadout<int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_B2VectorDoubleReadoutlEintgR(void *p) {
      delete ((::B2VectorDoubleReadout<int>*)p);
   }
   static void deleteArray_B2VectorDoubleReadoutlEintgR(void *p) {
      delete [] ((::B2VectorDoubleReadout<int>*)p);
   }
   static void destruct_B2VectorDoubleReadoutlEintgR(void *p) {
      typedef ::B2VectorDoubleReadout<int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::B2VectorDoubleReadout<int>

//______________________________________________________________________________
template <> void B2VectorDoubleReadout<double>::Streamer(TBuffer &R__b)
{
   // Stream an object of class B2VectorDoubleReadout<double>.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(B2VectorDoubleReadout<double>::Class(),this);
   } else {
      R__b.WriteClassBuffer(B2VectorDoubleReadout<double>::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_B2VectorDoubleReadoutlEdoublegR(void *p) {
      return  p ? new(p) ::B2VectorDoubleReadout<double> : new ::B2VectorDoubleReadout<double>;
   }
   static void *newArray_B2VectorDoubleReadoutlEdoublegR(Long_t nElements, void *p) {
      return p ? new(p) ::B2VectorDoubleReadout<double>[nElements] : new ::B2VectorDoubleReadout<double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_B2VectorDoubleReadoutlEdoublegR(void *p) {
      delete ((::B2VectorDoubleReadout<double>*)p);
   }
   static void deleteArray_B2VectorDoubleReadoutlEdoublegR(void *p) {
      delete [] ((::B2VectorDoubleReadout<double>*)p);
   }
   static void destruct_B2VectorDoubleReadoutlEdoublegR(void *p) {
      typedef ::B2VectorDoubleReadout<double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::B2VectorDoubleReadout<double>

//______________________________________________________________________________
template <> void B2VectorDoubleReadout<B2Vector3>::Streamer(TBuffer &R__b)
{
   // Stream an object of class B2VectorDoubleReadout<B2Vector3>.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(B2VectorDoubleReadout<B2Vector3>::Class(),this);
   } else {
      R__b.WriteClassBuffer(B2VectorDoubleReadout<B2Vector3>::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_B2VectorDoubleReadoutlEB2Vector3gR(void *p) {
      return  p ? new(p) ::B2VectorDoubleReadout<B2Vector3> : new ::B2VectorDoubleReadout<B2Vector3>;
   }
   static void *newArray_B2VectorDoubleReadoutlEB2Vector3gR(Long_t nElements, void *p) {
      return p ? new(p) ::B2VectorDoubleReadout<B2Vector3>[nElements] : new ::B2VectorDoubleReadout<B2Vector3>[nElements];
   }
   // Wrapper around operator delete
   static void delete_B2VectorDoubleReadoutlEB2Vector3gR(void *p) {
      delete ((::B2VectorDoubleReadout<B2Vector3>*)p);
   }
   static void deleteArray_B2VectorDoubleReadoutlEB2Vector3gR(void *p) {
      delete [] ((::B2VectorDoubleReadout<B2Vector3>*)p);
   }
   static void destruct_B2VectorDoubleReadoutlEB2Vector3gR(void *p) {
      typedef ::B2VectorDoubleReadout<B2Vector3> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::B2VectorDoubleReadout<B2Vector3>

//______________________________________________________________________________
void B2Energy::Streamer(TBuffer &R__b)
{
   // Stream an object of class B2Energy.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(B2Energy::Class(),this);
   } else {
      R__b.WriteClassBuffer(B2Energy::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_B2Energy(void *p) {
      return  p ? new(p) ::B2Energy : new ::B2Energy;
   }
   static void *newArray_B2Energy(Long_t nElements, void *p) {
      return p ? new(p) ::B2Energy[nElements] : new ::B2Energy[nElements];
   }
   // Wrapper around operator delete
   static void delete_B2Energy(void *p) {
      delete ((::B2Energy*)p);
   }
   static void deleteArray_B2Energy(void *p) {
      delete [] ((::B2Energy*)p);
   }
   static void destruct_B2Energy(void *p) {
      typedef ::B2Energy current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::B2Energy

//______________________________________________________________________________
void B2Momentum::Streamer(TBuffer &R__b)
{
   // Stream an object of class B2Momentum.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(B2Momentum::Class(),this);
   } else {
      R__b.WriteClassBuffer(B2Momentum::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_B2Momentum(void *p) {
      return  p ? new(p) ::B2Momentum : new ::B2Momentum;
   }
   static void *newArray_B2Momentum(Long_t nElements, void *p) {
      return p ? new(p) ::B2Momentum[nElements] : new ::B2Momentum[nElements];
   }
   // Wrapper around operator delete
   static void delete_B2Momentum(void *p) {
      delete ((::B2Momentum*)p);
   }
   static void deleteArray_B2Momentum(void *p) {
      delete [] ((::B2Momentum*)p);
   }
   static void destruct_B2Momentum(void *p) {
      typedef ::B2Momentum current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::B2Momentum

//______________________________________________________________________________
void B2Angle::Streamer(TBuffer &R__b)
{
   // Stream an object of class B2Angle.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(B2Angle::Class(),this);
   } else {
      R__b.WriteClassBuffer(B2Angle::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_B2Angle(void *p) {
      return  p ? new(p) ::B2Angle : new ::B2Angle;
   }
   static void *newArray_B2Angle(Long_t nElements, void *p) {
      return p ? new(p) ::B2Angle[nElements] : new ::B2Angle[nElements];
   }
   // Wrapper around operator delete
   static void delete_B2Angle(void *p) {
      delete ((::B2Angle*)p);
   }
   static void deleteArray_B2Angle(void *p) {
      delete [] ((::B2Angle*)p);
   }
   static void destruct_B2Angle(void *p) {
      typedef ::B2Angle current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::B2Angle

//______________________________________________________________________________
void B2Time::Streamer(TBuffer &R__b)
{
   // Stream an object of class B2Time.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(B2Time::Class(),this);
   } else {
      R__b.WriteClassBuffer(B2Time::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_B2Time(void *p) {
      return  p ? new(p) ::B2Time : new ::B2Time;
   }
   static void *newArray_B2Time(Long_t nElements, void *p) {
      return p ? new(p) ::B2Time[nElements] : new ::B2Time[nElements];
   }
   // Wrapper around operator delete
   static void delete_B2Time(void *p) {
      delete ((::B2Time*)p);
   }
   static void deleteArray_B2Time(void *p) {
      delete [] ((::B2Time*)p);
   }
   static void destruct_B2Time(void *p) {
      typedef ::B2Time current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::B2Time

//______________________________________________________________________________
void B2Distance::Streamer(TBuffer &R__b)
{
   // Stream an object of class B2Distance.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(B2Distance::Class(),this);
   } else {
      R__b.WriteClassBuffer(B2Distance::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_B2Distance(void *p) {
      return  p ? new(p) ::B2Distance : new ::B2Distance;
   }
   static void *newArray_B2Distance(Long_t nElements, void *p) {
      return p ? new(p) ::B2Distance[nElements] : new ::B2Distance[nElements];
   }
   // Wrapper around operator delete
   static void delete_B2Distance(void *p) {
      delete ((::B2Distance*)p);
   }
   static void deleteArray_B2Distance(void *p) {
      delete [] ((::B2Distance*)p);
   }
   static void destruct_B2Distance(void *p) {
      typedef ::B2Distance current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::B2Distance

//______________________________________________________________________________
void B2Position::Streamer(TBuffer &R__b)
{
   // Stream an object of class B2Position.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(B2Position::Class(),this);
   } else {
      R__b.WriteClassBuffer(B2Position::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_B2Position(void *p) {
      return  p ? new(p) ::B2Position : new ::B2Position;
   }
   static void *newArray_B2Position(Long_t nElements, void *p) {
      return p ? new(p) ::B2Position[nElements] : new ::B2Position[nElements];
   }
   // Wrapper around operator delete
   static void delete_B2Position(void *p) {
      delete ((::B2Position*)p);
   }
   static void deleteArray_B2Position(void *p) {
      delete [] ((::B2Position*)p);
   }
   static void destruct_B2Position(void *p) {
      typedef ::B2Position current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::B2Position

//______________________________________________________________________________
void B2ViewAngle::Streamer(TBuffer &R__b)
{
   // Stream an object of class B2ViewAngle.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(B2ViewAngle::Class(),this);
   } else {
      R__b.WriteClassBuffer(B2ViewAngle::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_B2ViewAngle(void *p) {
      return  p ? new(p) ::B2ViewAngle : new ::B2ViewAngle;
   }
   static void *newArray_B2ViewAngle(Long_t nElements, void *p) {
      return p ? new(p) ::B2ViewAngle[nElements] : new ::B2ViewAngle[nElements];
   }
   // Wrapper around operator delete
   static void delete_B2ViewAngle(void *p) {
      delete ((::B2ViewAngle*)p);
   }
   static void deleteArray_B2ViewAngle(void *p) {
      delete [] ((::B2ViewAngle*)p);
   }
   static void destruct_B2ViewAngle(void *p) {
      typedef ::B2ViewAngle current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::B2ViewAngle

//______________________________________________________________________________
void B2Direction::Streamer(TBuffer &R__b)
{
   // Stream an object of class B2Direction.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(B2Direction::Class(),this);
   } else {
      R__b.WriteClassBuffer(B2Direction::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_B2Direction(void *p) {
      return  p ? new(p) ::B2Direction : new ::B2Direction;
   }
   static void *newArray_B2Direction(Long_t nElements, void *p) {
      return p ? new(p) ::B2Direction[nElements] : new ::B2Direction[nElements];
   }
   // Wrapper around operator delete
   static void delete_B2Direction(void *p) {
      delete ((::B2Direction*)p);
   }
   static void deleteArray_B2Direction(void *p) {
      delete [] ((::B2Direction*)p);
   }
   static void destruct_B2Direction(void *p) {
      typedef ::B2Direction current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::B2Direction

//______________________________________________________________________________
void B2Vector3::Streamer(TBuffer &R__b)
{
   // Stream an object of class B2Vector3.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(B2Vector3::Class(),this);
   } else {
      R__b.WriteClassBuffer(B2Vector3::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_B2Vector3(void *p) {
      return  p ? new(p) ::B2Vector3 : new ::B2Vector3;
   }
   static void *newArray_B2Vector3(Long_t nElements, void *p) {
      return p ? new(p) ::B2Vector3[nElements] : new ::B2Vector3[nElements];
   }
   // Wrapper around operator delete
   static void delete_B2Vector3(void *p) {
      delete ((::B2Vector3*)p);
   }
   static void deleteArray_B2Vector3(void *p) {
      delete [] ((::B2Vector3*)p);
   }
   static void destruct_B2Vector3(void *p) {
      typedef ::B2Vector3 current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::B2Vector3

namespace ROOT {
   // Wrappers around operator new
   static void *new__Rb_tree_const_iteratorlEB2SigmagR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::_Rb_tree_const_iterator<B2Sigma> : new ::_Rb_tree_const_iterator<B2Sigma>;
   }
   static void *newArray__Rb_tree_const_iteratorlEB2SigmagR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::_Rb_tree_const_iterator<B2Sigma>[nElements] : new ::_Rb_tree_const_iterator<B2Sigma>[nElements];
   }
   // Wrapper around operator delete
   static void delete__Rb_tree_const_iteratorlEB2SigmagR(void *p) {
      delete ((::_Rb_tree_const_iterator<B2Sigma>*)p);
   }
   static void deleteArray__Rb_tree_const_iteratorlEB2SigmagR(void *p) {
      delete [] ((::_Rb_tree_const_iterator<B2Sigma>*)p);
   }
   static void destruct__Rb_tree_const_iteratorlEB2SigmagR(void *p) {
      typedef ::_Rb_tree_const_iterator<B2Sigma> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::_Rb_tree_const_iterator<B2Sigma>

//______________________________________________________________________________
void B2HitSummary::Streamer(TBuffer &R__b)
{
   // Stream an object of class B2HitSummary.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(B2HitSummary::Class(),this);
   } else {
      R__b.WriteClassBuffer(B2HitSummary::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_B2HitSummary(void *p) {
      return  p ? new(p) ::B2HitSummary : new ::B2HitSummary;
   }
   static void *newArray_B2HitSummary(Long_t nElements, void *p) {
      return p ? new(p) ::B2HitSummary[nElements] : new ::B2HitSummary[nElements];
   }
   // Wrapper around operator delete
   static void delete_B2HitSummary(void *p) {
      delete ((::B2HitSummary*)p);
   }
   static void deleteArray_B2HitSummary(void *p) {
      delete [] ((::B2HitSummary*)p);
   }
   static void destruct_B2HitSummary(void *p) {
      typedef ::B2HitSummary current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::B2HitSummary

//______________________________________________________________________________
void B2RefArray::Streamer(TBuffer &R__b)
{
   // Stream an object of class B2RefArray.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(B2RefArray::Class(),this);
   } else {
      R__b.WriteClassBuffer(B2RefArray::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_B2RefArray(void *p) {
      return  p ? new(p) ::B2RefArray : new ::B2RefArray;
   }
   static void *newArray_B2RefArray(Long_t nElements, void *p) {
      return p ? new(p) ::B2RefArray[nElements] : new ::B2RefArray[nElements];
   }
   // Wrapper around operator delete
   static void delete_B2RefArray(void *p) {
      delete ((::B2RefArray*)p);
   }
   static void deleteArray_B2RefArray(void *p) {
      delete [] ((::B2RefArray*)p);
   }
   static void destruct_B2RefArray(void *p) {
      typedef ::B2RefArray current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::B2RefArray

//______________________________________________________________________________
void B2HitsSet::Streamer(TBuffer &R__b)
{
   // Stream an object of class B2HitsSet.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(B2HitsSet::Class(),this);
   } else {
      R__b.WriteClassBuffer(B2HitsSet::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_B2HitsSet(void *p) {
      return  p ? new(p) ::B2HitsSet : new ::B2HitsSet;
   }
   static void *newArray_B2HitsSet(Long_t nElements, void *p) {
      return p ? new(p) ::B2HitsSet[nElements] : new ::B2HitsSet[nElements];
   }
   // Wrapper around operator delete
   static void delete_B2HitsSet(void *p) {
      delete ((::B2HitsSet*)p);
   }
   static void deleteArray_B2HitsSet(void *p) {
      delete [] ((::B2HitsSet*)p);
   }
   static void destruct_B2HitsSet(void *p) {
      typedef ::B2HitsSet current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::B2HitsSet

//______________________________________________________________________________
void B2ClusterSummary::Streamer(TBuffer &R__b)
{
   // Stream an object of class B2ClusterSummary.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(B2ClusterSummary::Class(),this);
   } else {
      R__b.WriteClassBuffer(B2ClusterSummary::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_B2ClusterSummary(void *p) {
      return  p ? new(p) ::B2ClusterSummary : new ::B2ClusterSummary;
   }
   static void *newArray_B2ClusterSummary(Long_t nElements, void *p) {
      return p ? new(p) ::B2ClusterSummary[nElements] : new ::B2ClusterSummary[nElements];
   }
   // Wrapper around operator delete
   static void delete_B2ClusterSummary(void *p) {
      delete ((::B2ClusterSummary*)p);
   }
   static void deleteArray_B2ClusterSummary(void *p) {
      delete [] ((::B2ClusterSummary*)p);
   }
   static void destruct_B2ClusterSummary(void *p) {
      typedef ::B2ClusterSummary current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::B2ClusterSummary

//______________________________________________________________________________
void B2TrackSummary::Streamer(TBuffer &R__b)
{
   // Stream an object of class B2TrackSummary.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(B2TrackSummary::Class(),this);
   } else {
      R__b.WriteClassBuffer(B2TrackSummary::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_B2TrackSummary(void *p) {
      return  p ? new(p) ::B2TrackSummary : new ::B2TrackSummary;
   }
   static void *newArray_B2TrackSummary(Long_t nElements, void *p) {
      return p ? new(p) ::B2TrackSummary[nElements] : new ::B2TrackSummary[nElements];
   }
   // Wrapper around operator delete
   static void delete_B2TrackSummary(void *p) {
      delete ((::B2TrackSummary*)p);
   }
   static void deleteArray_B2TrackSummary(void *p) {
      delete [] ((::B2TrackSummary*)p);
   }
   static void destruct_B2TrackSummary(void *p) {
      typedef ::B2TrackSummary current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::B2TrackSummary

//______________________________________________________________________________
void B2VertexSummary::Streamer(TBuffer &R__b)
{
   // Stream an object of class B2VertexSummary.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(B2VertexSummary::Class(),this);
   } else {
      R__b.WriteClassBuffer(B2VertexSummary::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_B2VertexSummary(void *p) {
      return  p ? new(p) ::B2VertexSummary : new ::B2VertexSummary;
   }
   static void *newArray_B2VertexSummary(Long_t nElements, void *p) {
      return p ? new(p) ::B2VertexSummary[nElements] : new ::B2VertexSummary[nElements];
   }
   // Wrapper around operator delete
   static void delete_B2VertexSummary(void *p) {
      delete ((::B2VertexSummary*)p);
   }
   static void deleteArray_B2VertexSummary(void *p) {
      delete [] ((::B2VertexSummary*)p);
   }
   static void destruct_B2VertexSummary(void *p) {
      typedef ::B2VertexSummary current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::B2VertexSummary

//______________________________________________________________________________
void B2BeamSummary::Streamer(TBuffer &R__b)
{
   // Stream an object of class B2BeamSummary.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(B2BeamSummary::Class(),this);
   } else {
      R__b.WriteClassBuffer(B2BeamSummary::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_B2BeamSummary(void *p) {
      return  p ? new(p) ::B2BeamSummary : new ::B2BeamSummary;
   }
   static void *newArray_B2BeamSummary(Long_t nElements, void *p) {
      return p ? new(p) ::B2BeamSummary[nElements] : new ::B2BeamSummary[nElements];
   }
   // Wrapper around operator delete
   static void delete_B2BeamSummary(void *p) {
      delete ((::B2BeamSummary*)p);
   }
   static void deleteArray_B2BeamSummary(void *p) {
      delete [] ((::B2BeamSummary*)p);
   }
   static void destruct_B2BeamSummary(void *p) {
      typedef ::B2BeamSummary current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::B2BeamSummary

//______________________________________________________________________________
void B2EventSummary::Streamer(TBuffer &R__b)
{
   // Stream an object of class B2EventSummary.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(B2EventSummary::Class(),this);
   } else {
      R__b.WriteClassBuffer(B2EventSummary::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_B2EventSummary(void *p) {
      return  p ? new(p) ::B2EventSummary : new ::B2EventSummary;
   }
   static void *newArray_B2EventSummary(Long_t nElements, void *p) {
      return p ? new(p) ::B2EventSummary[nElements] : new ::B2EventSummary[nElements];
   }
   // Wrapper around operator delete
   static void delete_B2EventSummary(void *p) {
      delete ((::B2EventSummary*)p);
   }
   static void deleteArray_B2EventSummary(void *p) {
      delete [] ((::B2EventSummary*)p);
   }
   static void destruct_B2EventSummary(void *p) {
      typedef ::B2EventSummary current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::B2EventSummary

//______________________________________________________________________________
void B2SpillSummary::Streamer(TBuffer &R__b)
{
   // Stream an object of class B2SpillSummary.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(B2SpillSummary::Class(),this);
   } else {
      R__b.WriteClassBuffer(B2SpillSummary::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_B2SpillSummary(void *p) {
      return  p ? new(p) ::B2SpillSummary : new ::B2SpillSummary;
   }
   static void *newArray_B2SpillSummary(Long_t nElements, void *p) {
      return p ? new(p) ::B2SpillSummary[nElements] : new ::B2SpillSummary[nElements];
   }
   // Wrapper around operator delete
   static void delete_B2SpillSummary(void *p) {
      delete ((::B2SpillSummary*)p);
   }
   static void deleteArray_B2SpillSummary(void *p) {
      delete [] ((::B2SpillSummary*)p);
   }
   static void destruct_B2SpillSummary(void *p) {
      typedef ::B2SpillSummary current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::B2SpillSummary

//______________________________________________________________________________
void B2EmulsionSummary::Streamer(TBuffer &R__b)
{
   // Stream an object of class B2EmulsionSummary.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(B2EmulsionSummary::Class(),this);
   } else {
      R__b.WriteClassBuffer(B2EmulsionSummary::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_B2EmulsionSummary(void *p) {
      return  p ? new(p) ::B2EmulsionSummary : new ::B2EmulsionSummary;
   }
   static void *newArray_B2EmulsionSummary(Long_t nElements, void *p) {
      return p ? new(p) ::B2EmulsionSummary[nElements] : new ::B2EmulsionSummary[nElements];
   }
   // Wrapper around operator delete
   static void delete_B2EmulsionSummary(void *p) {
      delete ((::B2EmulsionSummary*)p);
   }
   static void deleteArray_B2EmulsionSummary(void *p) {
      delete [] ((::B2EmulsionSummary*)p);
   }
   static void destruct_B2EmulsionSummary(void *p) {
      typedef ::B2EmulsionSummary current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::B2EmulsionSummary

//______________________________________________________________________________
void B2Boundary::Streamer(TBuffer &R__b)
{
   // Stream an object of class B2Boundary.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(B2Boundary::Class(),this);
   } else {
      R__b.WriteClassBuffer(B2Boundary::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_B2Boundary(void *p) {
      return  p ? new(p) ::B2Boundary : new ::B2Boundary;
   }
   static void *newArray_B2Boundary(Long_t nElements, void *p) {
      return p ? new(p) ::B2Boundary[nElements] : new ::B2Boundary[nElements];
   }
   // Wrapper around operator delete
   static void delete_B2Boundary(void *p) {
      delete ((::B2Boundary*)p);
   }
   static void deleteArray_B2Boundary(void *p) {
      delete [] ((::B2Boundary*)p);
   }
   static void destruct_B2Boundary(void *p) {
      typedef ::B2Boundary current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::B2Boundary

//______________________________________________________________________________
template <> void B2SingleBoundary<double>::Streamer(TBuffer &R__b)
{
   // Stream an object of class B2SingleBoundary<double>.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(B2SingleBoundary<double>::Class(),this);
   } else {
      R__b.WriteClassBuffer(B2SingleBoundary<double>::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_B2SingleBoundarylEdoublegR(void *p) {
      delete ((::B2SingleBoundary<double>*)p);
   }
   static void deleteArray_B2SingleBoundarylEdoublegR(void *p) {
      delete [] ((::B2SingleBoundary<double>*)p);
   }
   static void destruct_B2SingleBoundarylEdoublegR(void *p) {
      typedef ::B2SingleBoundary<double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::B2SingleBoundary<double>

//______________________________________________________________________________
template <> void B2SingleBoundary<int>::Streamer(TBuffer &R__b)
{
   // Stream an object of class B2SingleBoundary<int>.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(B2SingleBoundary<int>::Class(),this);
   } else {
      R__b.WriteClassBuffer(B2SingleBoundary<int>::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_B2SingleBoundarylEintgR(void *p) {
      delete ((::B2SingleBoundary<int>*)p);
   }
   static void deleteArray_B2SingleBoundarylEintgR(void *p) {
      delete [] ((::B2SingleBoundary<int>*)p);
   }
   static void destruct_B2SingleBoundarylEintgR(void *p) {
      typedef ::B2SingleBoundary<int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::B2SingleBoundary<int>

//______________________________________________________________________________
template <> void B2DoubleBoundary<vector<double> >::Streamer(TBuffer &R__b)
{
   // Stream an object of class B2DoubleBoundary<vector<double> >.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(B2DoubleBoundary<vector<double> >::Class(),this);
   } else {
      R__b.WriteClassBuffer(B2DoubleBoundary<vector<double> >::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_B2DoubleBoundarylEvectorlEdoublegRsPgR(void *p) {
      delete ((::B2DoubleBoundary<vector<double> >*)p);
   }
   static void deleteArray_B2DoubleBoundarylEvectorlEdoublegRsPgR(void *p) {
      delete [] ((::B2DoubleBoundary<vector<double> >*)p);
   }
   static void destruct_B2DoubleBoundarylEvectorlEdoublegRsPgR(void *p) {
      typedef ::B2DoubleBoundary<vector<double> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::B2DoubleBoundary<vector<double> >

//______________________________________________________________________________
template <> void B2DoubleBoundary<vector<int> >::Streamer(TBuffer &R__b)
{
   // Stream an object of class B2DoubleBoundary<vector<int> >.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(B2DoubleBoundary<vector<int> >::Class(),this);
   } else {
      R__b.WriteClassBuffer(B2DoubleBoundary<vector<int> >::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_B2DoubleBoundarylEvectorlEintgRsPgR(void *p) {
      delete ((::B2DoubleBoundary<vector<int> >*)p);
   }
   static void deleteArray_B2DoubleBoundarylEvectorlEintgRsPgR(void *p) {
      delete [] ((::B2DoubleBoundary<vector<int> >*)p);
   }
   static void destruct_B2DoubleBoundarylEvectorlEintgRsPgR(void *p) {
      typedef ::B2DoubleBoundary<vector<int> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::B2DoubleBoundary<vector<int> >

//______________________________________________________________________________
template <> void B2PointLikeBoundary<vector<double> >::Streamer(TBuffer &R__b)
{
   // Stream an object of class B2PointLikeBoundary<vector<double> >.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(B2PointLikeBoundary<vector<double> >::Class(),this);
   } else {
      R__b.WriteClassBuffer(B2PointLikeBoundary<vector<double> >::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_B2PointLikeBoundarylEvectorlEdoublegRsPgR(void *p) {
      delete ((::B2PointLikeBoundary<vector<double> >*)p);
   }
   static void deleteArray_B2PointLikeBoundarylEvectorlEdoublegRsPgR(void *p) {
      delete [] ((::B2PointLikeBoundary<vector<double> >*)p);
   }
   static void destruct_B2PointLikeBoundarylEvectorlEdoublegRsPgR(void *p) {
      typedef ::B2PointLikeBoundary<vector<double> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::B2PointLikeBoundary<vector<double> >

//______________________________________________________________________________
template <> void B2PointLikeBoundary<vector<int> >::Streamer(TBuffer &R__b)
{
   // Stream an object of class B2PointLikeBoundary<vector<int> >.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(B2PointLikeBoundary<vector<int> >::Class(),this);
   } else {
      R__b.WriteClassBuffer(B2PointLikeBoundary<vector<int> >::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_B2PointLikeBoundarylEvectorlEintgRsPgR(void *p) {
      delete ((::B2PointLikeBoundary<vector<int> >*)p);
   }
   static void deleteArray_B2PointLikeBoundarylEvectorlEintgRsPgR(void *p) {
      delete [] ((::B2PointLikeBoundary<vector<int> >*)p);
   }
   static void destruct_B2PointLikeBoundarylEvectorlEintgRsPgR(void *p) {
      typedef ::B2PointLikeBoundary<vector<int> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::B2PointLikeBoundary<vector<int> >

//______________________________________________________________________________
void B2DoubleBoundarySet::Streamer(TBuffer &R__b)
{
   // Stream an object of class B2DoubleBoundarySet.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(B2DoubleBoundarySet::Class(),this);
   } else {
      R__b.WriteClassBuffer(B2DoubleBoundarySet::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_B2DoubleBoundarySet(void *p) {
      delete ((::B2DoubleBoundarySet*)p);
   }
   static void deleteArray_B2DoubleBoundarySet(void *p) {
      delete [] ((::B2DoubleBoundarySet*)p);
   }
   static void destruct_B2DoubleBoundarySet(void *p) {
      typedef ::B2DoubleBoundarySet current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::B2DoubleBoundarySet

//______________________________________________________________________________
void B2SigmaList::Streamer(TBuffer &R__b)
{
   // Stream an object of class B2SigmaList.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(B2SigmaList::Class(),this);
   } else {
      R__b.WriteClassBuffer(B2SigmaList::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_B2SigmaList(void *p) {
      return  p ? new(p) ::B2SigmaList : new ::B2SigmaList;
   }
   static void *newArray_B2SigmaList(Long_t nElements, void *p) {
      return p ? new(p) ::B2SigmaList[nElements] : new ::B2SigmaList[nElements];
   }
   // Wrapper around operator delete
   static void delete_B2SigmaList(void *p) {
      delete ((::B2SigmaList*)p);
   }
   static void deleteArray_B2SigmaList(void *p) {
      delete [] ((::B2SigmaList*)p);
   }
   static void destruct_B2SigmaList(void *p) {
      typedef ::B2SigmaList current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::B2SigmaList

//______________________________________________________________________________
void B2Dial::Streamer(TBuffer &R__b)
{
   // Stream an object of class B2Dial.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(B2Dial::Class(),this);
   } else {
      R__b.WriteClassBuffer(B2Dial::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_B2Dial(void *p) {
      return  p ? new(p) ::B2Dial : new ::B2Dial;
   }
   static void *newArray_B2Dial(Long_t nElements, void *p) {
      return p ? new(p) ::B2Dial[nElements] : new ::B2Dial[nElements];
   }
   // Wrapper around operator delete
   static void delete_B2Dial(void *p) {
      delete ((::B2Dial*)p);
   }
   static void deleteArray_B2Dial(void *p) {
      delete [] ((::B2Dial*)p);
   }
   static void destruct_B2Dial(void *p) {
      typedef ::B2Dial current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::B2Dial

//______________________________________________________________________________
void B2DialList::Streamer(TBuffer &R__b)
{
   // Stream an object of class B2DialList.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(B2DialList::Class(),this);
   } else {
      R__b.WriteClassBuffer(B2DialList::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_B2DialList(void *p) {
      return  p ? new(p) ::B2DialList : new ::B2DialList;
   }
   static void *newArray_B2DialList(Long_t nElements, void *p) {
      return p ? new(p) ::B2DialList[nElements] : new ::B2DialList[nElements];
   }
   // Wrapper around operator delete
   static void delete_B2DialList(void *p) {
      delete ((::B2DialList*)p);
   }
   static void deleteArray_B2DialList(void *p) {
      delete [] ((::B2DialList*)p);
   }
   static void destruct_B2DialList(void *p) {
      typedef ::B2DialList current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::B2DialList

namespace ROOT {
   static TClass *vectorlEintgR_Dictionary();
   static void vectorlEintgR_TClassManip(TClass*);
   static void *new_vectorlEintgR(void *p = 0);
   static void *newArray_vectorlEintgR(Long_t size, void *p);
   static void delete_vectorlEintgR(void *p);
   static void deleteArray_vectorlEintgR(void *p);
   static void destruct_vectorlEintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<int>*)
   {
      vector<int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<int>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<int>", -2, "vector", 386,
                  typeid(vector<int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEintgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<int>) );
      instance.SetNew(&new_vectorlEintgR);
      instance.SetNewArray(&newArray_vectorlEintgR);
      instance.SetDelete(&delete_vectorlEintgR);
      instance.SetDeleteArray(&deleteArray_vectorlEintgR);
      instance.SetDestructor(&destruct_vectorlEintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<int> >()));

      ::ROOT::AddClassAlternate("vector<int>","std::vector<int, std::allocator<int> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<int>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<int>*)0x0)->GetClass();
      vectorlEintgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int> : new vector<int>;
   }
   static void *newArray_vectorlEintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int>[nElements] : new vector<int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEintgR(void *p) {
      delete ((vector<int>*)p);
   }
   static void deleteArray_vectorlEintgR(void *p) {
      delete [] ((vector<int>*)p);
   }
   static void destruct_vectorlEintgR(void *p) {
      typedef vector<int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<int>

namespace ROOT {
   static TClass *vectorlEdoublegR_Dictionary();
   static void vectorlEdoublegR_TClassManip(TClass*);
   static void *new_vectorlEdoublegR(void *p = 0);
   static void *newArray_vectorlEdoublegR(Long_t size, void *p);
   static void delete_vectorlEdoublegR(void *p);
   static void deleteArray_vectorlEdoublegR(void *p);
   static void destruct_vectorlEdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<double>*)
   {
      vector<double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<double>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<double>", -2, "vector", 386,
                  typeid(vector<double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(vector<double>) );
      instance.SetNew(&new_vectorlEdoublegR);
      instance.SetNewArray(&newArray_vectorlEdoublegR);
      instance.SetDelete(&delete_vectorlEdoublegR);
      instance.SetDeleteArray(&deleteArray_vectorlEdoublegR);
      instance.SetDestructor(&destruct_vectorlEdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<double> >()));

      ::ROOT::AddClassAlternate("vector<double>","std::vector<double, std::allocator<double> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<double>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<double>*)0x0)->GetClass();
      vectorlEdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEdoublegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double> : new vector<double>;
   }
   static void *newArray_vectorlEdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double>[nElements] : new vector<double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEdoublegR(void *p) {
      delete ((vector<double>*)p);
   }
   static void deleteArray_vectorlEdoublegR(void *p) {
      delete [] ((vector<double>*)p);
   }
   static void destruct_vectorlEdoublegR(void *p) {
      typedef vector<double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<double>

namespace ROOT {
   static TClass *vectorlETRefgR_Dictionary();
   static void vectorlETRefgR_TClassManip(TClass*);
   static void *new_vectorlETRefgR(void *p = 0);
   static void *newArray_vectorlETRefgR(Long_t size, void *p);
   static void delete_vectorlETRefgR(void *p);
   static void deleteArray_vectorlETRefgR(void *p);
   static void destruct_vectorlETRefgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TRef>*)
   {
      vector<TRef> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TRef>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TRef>", -2, "vector", 386,
                  typeid(vector<TRef>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETRefgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<TRef>) );
      instance.SetNew(&new_vectorlETRefgR);
      instance.SetNewArray(&newArray_vectorlETRefgR);
      instance.SetDelete(&delete_vectorlETRefgR);
      instance.SetDeleteArray(&deleteArray_vectorlETRefgR);
      instance.SetDestructor(&destruct_vectorlETRefgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TRef> >()));

      ::ROOT::AddClassAlternate("vector<TRef>","std::vector<TRef, std::allocator<TRef> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<TRef>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETRefgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TRef>*)0x0)->GetClass();
      vectorlETRefgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETRefgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETRefgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TRef> : new vector<TRef>;
   }
   static void *newArray_vectorlETRefgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TRef>[nElements] : new vector<TRef>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETRefgR(void *p) {
      delete ((vector<TRef>*)p);
   }
   static void deleteArray_vectorlETRefgR(void *p) {
      delete [] ((vector<TRef>*)p);
   }
   static void destruct_vectorlETRefgR(void *p) {
      typedef vector<TRef> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TRef>

namespace ROOT {
   static TClass *vectorlEB2DialgR_Dictionary();
   static void vectorlEB2DialgR_TClassManip(TClass*);
   static void *new_vectorlEB2DialgR(void *p = 0);
   static void *newArray_vectorlEB2DialgR(Long_t size, void *p);
   static void delete_vectorlEB2DialgR(void *p);
   static void deleteArray_vectorlEB2DialgR(void *p);
   static void destruct_vectorlEB2DialgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<B2Dial>*)
   {
      vector<B2Dial> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<B2Dial>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<B2Dial>", -2, "vector", 386,
                  typeid(vector<B2Dial>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEB2DialgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<B2Dial>) );
      instance.SetNew(&new_vectorlEB2DialgR);
      instance.SetNewArray(&newArray_vectorlEB2DialgR);
      instance.SetDelete(&delete_vectorlEB2DialgR);
      instance.SetDeleteArray(&deleteArray_vectorlEB2DialgR);
      instance.SetDestructor(&destruct_vectorlEB2DialgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<B2Dial> >()));

      ::ROOT::AddClassAlternate("vector<B2Dial>","std::vector<B2Dial, std::allocator<B2Dial> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<B2Dial>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEB2DialgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<B2Dial>*)0x0)->GetClass();
      vectorlEB2DialgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEB2DialgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEB2DialgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<B2Dial> : new vector<B2Dial>;
   }
   static void *newArray_vectorlEB2DialgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<B2Dial>[nElements] : new vector<B2Dial>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEB2DialgR(void *p) {
      delete ((vector<B2Dial>*)p);
   }
   static void deleteArray_vectorlEB2DialgR(void *p) {
      delete [] ((vector<B2Dial>*)p);
   }
   static void destruct_vectorlEB2DialgR(void *p) {
      typedef vector<B2Dial> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<B2Dial>

namespace ROOT {
   static TClass *setlEB2SigmagR_Dictionary();
   static void setlEB2SigmagR_TClassManip(TClass*);
   static void *new_setlEB2SigmagR(void *p = 0);
   static void *newArray_setlEB2SigmagR(Long_t size, void *p);
   static void delete_setlEB2SigmagR(void *p);
   static void deleteArray_setlEB2SigmagR(void *p);
   static void destruct_setlEB2SigmagR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const set<B2Sigma>*)
   {
      set<B2Sigma> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(set<B2Sigma>));
      static ::ROOT::TGenericClassInfo 
         instance("set<B2Sigma>", -2, "set", 94,
                  typeid(set<B2Sigma>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &setlEB2SigmagR_Dictionary, isa_proxy, 4,
                  sizeof(set<B2Sigma>) );
      instance.SetNew(&new_setlEB2SigmagR);
      instance.SetNewArray(&newArray_setlEB2SigmagR);
      instance.SetDelete(&delete_setlEB2SigmagR);
      instance.SetDeleteArray(&deleteArray_setlEB2SigmagR);
      instance.SetDestructor(&destruct_setlEB2SigmagR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Insert< set<B2Sigma> >()));

      ::ROOT::AddClassAlternate("set<B2Sigma>","std::set<B2Sigma, std::less<B2Sigma>, std::allocator<B2Sigma> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const set<B2Sigma>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *setlEB2SigmagR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const set<B2Sigma>*)0x0)->GetClass();
      setlEB2SigmagR_TClassManip(theClass);
   return theClass;
   }

   static void setlEB2SigmagR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_setlEB2SigmagR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) set<B2Sigma> : new set<B2Sigma>;
   }
   static void *newArray_setlEB2SigmagR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) set<B2Sigma>[nElements] : new set<B2Sigma>[nElements];
   }
   // Wrapper around operator delete
   static void delete_setlEB2SigmagR(void *p) {
      delete ((set<B2Sigma>*)p);
   }
   static void deleteArray_setlEB2SigmagR(void *p) {
      delete [] ((set<B2Sigma>*)p);
   }
   static void destruct_setlEB2SigmagR(void *p) {
      typedef set<B2Sigma> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class set<B2Sigma>

namespace {
  void TriggerDictionaryInitialization_libB2MCDict_Impl() {
    static const char* headers[] = {
"B2HitSummary.hh",
"B2ClusterSummary.hh",
"B2TrackSummary.hh",
"B2VertexSummary.hh",
"B2BeamSummary.hh",
"B2Measurement.hh",
"B2EventSummary.hh",
"B2SpillSummary.hh",
"B2EmulsionSummary.hh",
"B2HitsSet.hh",
"B2Pdg.hh",
"B2RefArray.hh",
"B2Boundary.hh",
"B2Sigma.hh",
"B2Dial.hh",
"B2DialList.hh",
"B2SigmaList.hh",
0
    };
    static const char* includePaths[] = {
"/opt/geant4/include/Geant4",
"/home/neo/Programs/ROOT/v6-22-02/include",
"/usr/include",
"/home/neo/Code/WAGASCI/WagasciMonteCarlo/include",
"/home/neo/Code/WAGASCI/WagasciMonteCarlo/lib",
"/home/neo/Programs/ROOT/v6-22-02/include/",
"/home/neo/Code/WAGASCI/WagasciMonteCarlo/cmake-build-debug/lib/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libB2MCDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$B2Dial.hh")))  B2Dial;
namespace std{template <typename _Tp> class __attribute__((annotate("$clingAutoload$bits/allocator.h")))  __attribute__((annotate("$clingAutoload$string")))  allocator;
}
class __attribute__((annotate("$clingAutoload$B2Measurement.hh")))  __attribute__((annotate("$clingAutoload$B2HitSummary.hh")))  B2Measurement1D;
class __attribute__((annotate("$clingAutoload$B2Measurement.hh")))  __attribute__((annotate("$clingAutoload$B2HitSummary.hh")))  B2Measurement2D;
class __attribute__((annotate("$clingAutoload$B2Measurement.hh")))  __attribute__((annotate("$clingAutoload$B2HitSummary.hh")))  B2Measurement3D;
template <typename T> class __attribute__((annotate("$clingAutoload$B2Measurement.hh")))  __attribute__((annotate("$clingAutoload$B2HitSummary.hh")))  B2VectorDoubleReadout;

class __attribute__((annotate("$clingAutoload$B2Measurement.hh")))  __attribute__((annotate("$clingAutoload$B2HitSummary.hh")))  B2Vector3;
class __attribute__((annotate("$clingAutoload$B2Measurement.hh")))  __attribute__((annotate("$clingAutoload$B2HitSummary.hh")))  B2Energy;
class __attribute__((annotate("$clingAutoload$B2Measurement.hh")))  __attribute__((annotate("$clingAutoload$B2HitSummary.hh")))  B2Momentum;
class __attribute__((annotate("$clingAutoload$B2Measurement.hh")))  __attribute__((annotate("$clingAutoload$B2HitSummary.hh")))  B2Angle;
class __attribute__((annotate("$clingAutoload$B2Measurement.hh")))  __attribute__((annotate("$clingAutoload$B2HitSummary.hh")))  B2Time;
class __attribute__((annotate("$clingAutoload$B2Measurement.hh")))  __attribute__((annotate("$clingAutoload$B2HitSummary.hh")))  B2Distance;
class __attribute__((annotate("$clingAutoload$B2Measurement.hh")))  __attribute__((annotate("$clingAutoload$B2HitSummary.hh")))  B2Position;
class __attribute__((annotate("$clingAutoload$B2Measurement.hh")))  __attribute__((annotate("$clingAutoload$B2HitSummary.hh")))  B2ViewAngle;
class __attribute__((annotate("$clingAutoload$B2Measurement.hh")))  __attribute__((annotate("$clingAutoload$B2HitSummary.hh")))  B2Direction;
enum  __attribute__((annotate("$clingAutoload$B2Sigma.hh"))) B2Sigma : int;
namespace std{template <typename _Tp> struct __attribute__((annotate("$clingAutoload$bits/stl_tree.h")))  __attribute__((annotate("$clingAutoload$B2HitSummary.hh")))  _Rb_tree_const_iterator;
}
class __attribute__((annotate("$clingAutoload$B2HitSummary.hh")))  B2HitSummary;
class __attribute__((annotate("$clingAutoload$B2RefArray.hh")))  __attribute__((annotate("$clingAutoload$B2ClusterSummary.hh")))  B2RefArray;
class __attribute__((annotate("$clingAutoload$B2HitsSet.hh")))  __attribute__((annotate("$clingAutoload$B2ClusterSummary.hh")))  B2HitsSet;
class __attribute__((annotate("$clingAutoload$B2ClusterSummary.hh")))  B2ClusterSummary;
class __attribute__((annotate("$clingAutoload$B2TrackSummary.hh")))  B2TrackSummary;
class __attribute__((annotate("$clingAutoload$B2VertexSummary.hh")))  B2VertexSummary;
class __attribute__((annotate("$clingAutoload$B2BeamSummary.hh")))  B2BeamSummary;
class __attribute__((annotate("$clingAutoload$B2EventSummary.hh")))  B2EventSummary;
class __attribute__((annotate("$clingAutoload$B2SpillSummary.hh")))  B2SpillSummary;
class __attribute__((annotate("$clingAutoload$B2EmulsionSummary.hh")))  B2EmulsionSummary;
class __attribute__((annotate("$clingAutoload$B2Boundary.hh")))  B2Boundary;
template <typename T> class __attribute__((annotate("$clingAutoload$B2Boundary.hh")))  B2SingleBoundary;

class __attribute__((annotate("$clingAutoload$B2Boundary.hh")))  B2DoubleBoundarySet;
namespace std{template <typename _Tp> struct __attribute__((annotate("$clingAutoload$bits/stl_function.h")))  __attribute__((annotate("$clingAutoload$string")))  less;
}
class __attribute__((annotate("$clingAutoload$B2SigmaList.hh")))  __attribute__((annotate("$clingAutoload$B2Dial.hh")))  B2SigmaList;
class __attribute__((annotate("$clingAutoload$B2DialList.hh")))  B2DialList;
typedef int Int_t __attribute__((annotate("$clingAutoload$RtypesCore.h"))) ;
typedef B2VectorDoubleReadout<Int_t> B2DoubleReadoutI __attribute__((annotate("$clingAutoload$B2Measurement.hh")))  __attribute__((annotate("$clingAutoload$B2HitSummary.hh"))) ;
typedef double Double_t __attribute__((annotate("$clingAutoload$RtypesCore.h"))) ;
typedef B2VectorDoubleReadout<Double_t> B2DoubleReadoutD __attribute__((annotate("$clingAutoload$B2Measurement.hh")))  __attribute__((annotate("$clingAutoload$B2HitSummary.hh"))) ;
typedef B2VectorDoubleReadout<B2Vector3> B2DoubleReadout3 __attribute__((annotate("$clingAutoload$B2Measurement.hh")))  __attribute__((annotate("$clingAutoload$B2HitSummary.hh"))) ;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libB2MCDict dictionary payload"

#ifndef G4UI_USE_TCSH
  #define G4UI_USE_TCSH 1
#endif
#ifndef BOOST_TEST_DYN_LINK
  #define BOOST_TEST_DYN_LINK 1
#endif
#ifndef BOOST_LOG_DYN_LINK
  #define BOOST_LOG_DYN_LINK 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "B2HitSummary.hh"
#include "B2ClusterSummary.hh"
#include "B2TrackSummary.hh"
#include "B2VertexSummary.hh"
#include "B2BeamSummary.hh"
#include "B2Measurement.hh"
#include "B2EventSummary.hh"
#include "B2SpillSummary.hh"
#include "B2EmulsionSummary.hh"
#include "B2HitsSet.hh"
#include "B2Pdg.hh"
#include "B2RefArray.hh"
#include "B2Boundary.hh"
#include "B2Sigma.hh"
#include "B2Dial.hh"
#include "B2DialList.hh"
#include "B2SigmaList.hh"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"B2Angle", payloadCode, "@",
"B2BeamSummary", payloadCode, "@",
"B2Boundary", payloadCode, "@",
"B2ClusterSummary", payloadCode, "@",
"B2Dial", payloadCode, "@",
"B2DialList", payloadCode, "@",
"B2Direction", payloadCode, "@",
"B2Distance", payloadCode, "@",
"B2DoubleBoundary<std::vector<double> >", payloadCode, "@",
"B2DoubleBoundary<std::vector<int> >", payloadCode, "@",
"B2DoubleBoundary<vector<double> >", payloadCode, "@",
"B2DoubleBoundary<vector<int> >", payloadCode, "@",
"B2DoubleBoundarySet", payloadCode, "@",
"B2DoubleReadout3", payloadCode, "@",
"B2DoubleReadoutD", payloadCode, "@",
"B2DoubleReadoutI", payloadCode, "@",
"B2EmulsionSummary", payloadCode, "@",
"B2Energy", payloadCode, "@",
"B2EventSummary", payloadCode, "@",
"B2HitSummary", payloadCode, "@",
"B2HitsSet", payloadCode, "@",
"B2Measurement1D", payloadCode, "@",
"B2Measurement2D", payloadCode, "@",
"B2Measurement3D", payloadCode, "@",
"B2Momentum", payloadCode, "@",
"B2PointLikeBoundary<std::vector<double> >", payloadCode, "@",
"B2PointLikeBoundary<std::vector<int> >", payloadCode, "@",
"B2PointLikeBoundary<vector<double> >", payloadCode, "@",
"B2PointLikeBoundary<vector<int> >", payloadCode, "@",
"B2Position", payloadCode, "@",
"B2RefArray", payloadCode, "@",
"B2SigmaList", payloadCode, "@",
"B2SingleBoundary<double>", payloadCode, "@",
"B2SingleBoundary<int>", payloadCode, "@",
"B2SpillSummary", payloadCode, "@",
"B2Time", payloadCode, "@",
"B2TrackSummary", payloadCode, "@",
"B2Vector3", payloadCode, "@",
"B2VectorDoubleReadout<B2Vector3>", payloadCode, "@",
"B2VectorDoubleReadout<Double_t>", payloadCode, "@",
"B2VectorDoubleReadout<Int_t>", payloadCode, "@",
"B2VectorDoubleReadout<double>", payloadCode, "@",
"B2VectorDoubleReadout<int>", payloadCode, "@",
"B2VertexSummary", payloadCode, "@",
"B2ViewAngle", payloadCode, "@",
"__gnu_cxx::__normal_iterator<B2Dial*,vector<B2Dial> >", payloadCode, "@",
"__gnu_cxx::__normal_iterator<const B2Dial*,vector<B2Dial> >", payloadCode, "@",
"vector<B2Dial>::const_iterator", payloadCode, "@",
"vector<B2Dial>::iterator", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libB2MCDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libB2MCDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libB2MCDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libB2MCDict() {
  TriggerDictionaryInitialization_libB2MCDict_Impl();
}
