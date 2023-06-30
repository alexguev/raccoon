//* This file is part of the RACCOON application
//* being developed at Dolbow lab at Duke University
//* http://dolbow.pratt.duke.edu

#include "ADComputePorosity.h"
#include "RankTwoTensor.h"
#include <algorithm>
registerMooseObject("raccoonApp", ADComputePorosity);

InputParameters
ADComputePorosity::validParams()
{
  InputParameters params = Material::validParams();
  params.addClassDescription(
      "compute porosity in poroelastic media as a function of fluid pressure and solid volumetric strain");
  params.addRequiredCoupledVar("porepressure", "fluid phase porepressure");
  params.addParam<MaterialPropertyName>(
      "porosity_name", "porosity", "Name of porosity material property");
  // params.addRequiredRangeCheckedParam<Real>(
  //     "initial_porosity", "initial_porosity>0.0 & initial_porosity<1.0", "Initial porosity");
  params.addRequiredCoupledVar("initial_porosity", "Initial porosity");
  //params.addParam<MaterialPropertyName>("biot_coefficient", "biot_coefficient", "biot_coefficient");
  //params.addParam<MaterialPropertyName>("inv_biot_modulus", "inv_biot_modulus", "inv_biot_modulus");
  return params;
}

ADComputePorosity::ADComputePorosity(const InputParameters & parameters)
  : Material(parameters),
    _porepressure(adCoupledValue("porepressure")),
    _strain(getADMaterialPropertyByName<RankTwoTensor>("total_strain")),
    _porosity(declareADProperty<Real>(getParam<MaterialPropertyName>("porosity_name"))),
    _porosity_old(getMaterialPropertyOld<Real>(getParam<MaterialPropertyName>("porosity_name"))),
//    _initial_porosity(getParam<Real>("initial_porosity")),
    _initial_porosity(adCoupledValue("initial_porosity")),
  //  _alpha(getADMaterialProperty<Real>("biot_coefficient")),
  //  _invM(getADMaterialProperty<Real>("inv_biot_modulus")),
    _Ks(getADMaterialProperty<Real>("Ks"))
{
}

void
ADComputePorosity::initQpStatefulProperties()
{
//  _porosity[_qp] = _initial_porosity;
  _porosity[_qp] = _initial_porosity[0]; //as in PorousFlowPorosityConst
}

void
ADComputePorosity::computeQpProperties()
{
//    initQpStatefulProperties();
//  _porosity[_qp] = _initial_porosity[0];
  // _porosity[_qp] = std::max(std::min(_invM[_qp]*_porepressure[_qp] + _alpha[_qp] * (_strain[_qp].trace()) + _initial_porosity[0],1),0);
  ADReal test = (1-_initial_porosity[0])/_Ks[_qp]* _porepressure[_qp] + (1-_initial_porosity[0]) * (_strain[_qp].trace()) + _initial_porosity[0];
   //_porosity[_qp] = std::max(std::min(MetaPhysicL::raw_value(test),1),0);

   if(test > 1)
    test = 1;
   if(test < 0)
    test = 0;
    //  _porosity[_qp] = (1-_initial_porosity[0])/_Ks[_qp]* _porepressure[_qp] + (1-_initial_porosity[0]) * (_strain[_qp].trace()) + _initial_porosity[0];
  //  _porosity[_qp] = std::max(std::min(0.01*_porepressure[_qp] + _alpha[_qp] * (_strain[_qp].trace()) + _initial_porosity[0],1),0); //using a stabilizing pressure term
  //  _porosity[_qp] = std::max(std::min(_alpha[_qp] * (_strain[_qp].trace()) + _initial_porosity[0],1),0);
//  _porosity[_qp] = std::max(std::min( 1 - (_alpha[_qp] -_initial_porosity[0]) * std::exp(-_strain[_qp].trace()),1),0);
}
