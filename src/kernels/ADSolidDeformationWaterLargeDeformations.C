//* This file is part of the RACCOON application
//* being developed at Dolbow lab at Duke University
//* http://dolbow.pratt.duke.edu

#include "ADSolidDeformationWaterLargeDeformations.h"
#include "MooseVariable.h"
#include "libmesh/quadrature.h"
#include <limits>

registerMooseObject("raccoonApp", ADSolidDeformationWaterLargeDeformations);

InputParameters
ADSolidDeformationWaterLargeDeformations::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addClassDescription(
      "Kernel handling solid deformation term in water mass balance");
  params.addRequiredParam<MaterialPropertyName>("porosity_name", "porosity");
  params.addRequiredCoupledVar("saturation_name", "saturation");
  return params;
}

ADSolidDeformationWaterLargeDeformations::ADSolidDeformationWaterLargeDeformations(const InputParameters & parameters)
  : ADTimeKernel(parameters),
  _porosity(getADMaterialProperty<Real>("porosity_name")),
  _saturation(adCoupledValue("saturation_name")),
  _logJ(getADMaterialPropertyByName<Real>("log_jacobian_name")),
  _logJ_old(getMaterialPropertyOldByName<Real>("log_jacobian_name"))
{
}

ADReal
ADSolidDeformationWaterLargeDeformations::computeQpResidual()
{
  return _porosity[_qp] * _saturation[_qp] *
         ((_logJ[_qp] - _logJ_old[_qp])  / _dt)
         * _test[_i][_qp];
}
