//* This file is part of the RACCOON application
//* being developed at Dolbow lab at Duke University
//* http://dolbow.pratt.duke.edu

#include "ADSolidDeformationTotalLargeDeformations.h"
#include "MooseVariable.h"
#include "libmesh/quadrature.h"
#include <limits>

registerMooseObject("raccoonApp", ADSolidDeformationTotalLargeDeformations);

InputParameters
ADSolidDeformationTotalLargeDeformations::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addClassDescription(
      "Kernel handling solid deformation term in total mass balance");
  params.addRequiredParam<MaterialPropertyName>("porosity_name", "porosity");
  //params.addRequiredCoupledVar("saturation_name", "saturation");
//  params.addRequiredParam<MaterialPropertyName>("jacobian_name", "jacobian of deformation gradient");
  return params;
}

ADSolidDeformationTotalLargeDeformations::ADSolidDeformationTotalLargeDeformations(const InputParameters & parameters)
  : ADTimeKernel(parameters),
  _porosity(getADMaterialProperty<Real>("porosity_name")),
  _logJ(getADMaterialPropertyByName<Real>("log_jacobian_name")),
  //_logJ_old(getMaterialPropertyOld<Real>(getParam<MaterialPropertyName>("log_jacobian_name")))
  _logJ_old(getMaterialPropertyOldByName<Real>("log_jacobian_name"))

{
}

ADReal
ADSolidDeformationTotalLargeDeformations::computeQpResidual()
{
  return _porosity[_qp] *
         ((_logJ[_qp] - _logJ_old[_qp])  / _dt)
         * _test[_i][_qp];
}
