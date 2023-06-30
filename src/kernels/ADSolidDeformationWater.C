//* This file is part of the RACCOON application
//* being developed at Dolbow lab at Duke University
//* http://dolbow.pratt.duke.edu

#include "ADSolidDeformationWater.h"
#include "MooseVariable.h"
#include "libmesh/quadrature.h"
#include <limits>

registerMooseObject("raccoonApp", ADSolidDeformationWater);

InputParameters
ADSolidDeformationWater::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addClassDescription(
      "Kernel handling solid deformation term in water mass balance");
  params.addRequiredParam<MaterialPropertyName>("porosity_name", "porosity");
  params.addRequiredCoupledVar("saturation_name", "saturation");
  params.addRequiredParam<MaterialPropertyName>("total_strain_name", "total strain");
  return params;
}

ADSolidDeformationWater::ADSolidDeformationWater(const InputParameters & parameters)
  : ADTimeKernel(parameters),
  _porosity(getADMaterialProperty<Real>("porosity_name")),
  _saturation(adCoupledValue("saturation_name")),
  _strain(getADMaterialProperty<RankTwoTensor>("total_strain_name")),
  _strain_old(getMaterialPropertyOld<RankTwoTensor>(("total_strain_name")))
{
}

ADReal
ADSolidDeformationWater::computeQpResidual()
{
  return _porosity[_qp] * _saturation[_qp] *
         ((_strain[_qp].trace()-_strain_old[_qp].trace()) / _dt)
         * _test[_i][_qp];
}
