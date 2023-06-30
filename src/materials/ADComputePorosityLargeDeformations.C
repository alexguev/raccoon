//* This file is part of the RACCOON application
//* being developed at Dolbow lab at Duke University
//* http://dolbow.pratt.duke.edu

#include "ADComputePorosityLargeDeformations.h"
#include "RankTwoTensor.h"

registerMooseObject("raccoonApp", ADComputePorosityLargeDeformations);

InputParameters
ADComputePorosityLargeDeformations::validParams()
{
  InputParameters params = Material::validParams();
  params.addClassDescription(
      "compute porosity in poroelastic media in the case of large deformations, as a function of fluid pressure and jacobian of deformation gradient");
  params.addRequiredCoupledVar("porepressure", "fluid phase porepressure");
  params.addParam<MaterialPropertyName>(
      "porosity_name", "porosity", "Name of porosity material property");
  // params.addRequiredRangeCheckedParam<Real>(
  //     "initial_porosity", "initial_porosity>0.0 & initial_porosity<1.0", "Initial porosity");
  params.addRequiredCoupledVar("initial_porosity", "Initial porosity");
  return params;
}

ADComputePorosityLargeDeformations::ADComputePorosityLargeDeformations(const InputParameters & parameters)
  : Material(parameters),
    _p(adCoupledValue("porepressure")),
    _J(getADMaterialPropertyByName<Real>("jacobian_name")),
    //_J(getADMaterialProperty<Real>(getParam<MaterialPropertyName>("jacobian_name"))),
    _porosity(declareADProperty<Real>(getParam<MaterialPropertyName>("porosity_name"))),
    _initial_porosity(adCoupledValue("initial_porosity")),
    _Ks(getADMaterialProperty<Real>("Ks"))
{
}

void
ADComputePorosityLargeDeformations::initQpStatefulProperties()
{
//  _porosity[_qp] = _initial_porosity;
  _porosity[_qp] = _initial_porosity[0]; //as in PorousFlowPorosityConst
}

void
ADComputePorosityLargeDeformations::computeQpProperties()
{
  //_porosity[_qp] = std::max(std::min(1 - (1-_initial_porosity[0])/ _J[_qp]  * std::exp(-_p[_qp]/_Ks[_qp]),1),0);
  ADReal test = _porosity[_qp] = 1 - (1-_initial_porosity[0]) / _J[_qp] * std::exp(-_p[_qp]/_Ks[_qp]);

  if(test > 1)
   test = 1;
  if(test < 0)
   test = 0;
    //  _porosity[_qp] = std::max(std::min((1-_initial_porosity[0])/_Ks[_qp]* _p[_qp] + (1-_initial_porosity[0]) * (_J[_qp] - 1) + _initial_porosity[0],1),0);

}
