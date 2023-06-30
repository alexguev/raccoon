//* This file is part of the RACCOON application
//* being developed at Dolbow lab at Duke University
//* http://dolbow.pratt.duke.edu

#include "ADPorosityTimeDerivativeAlex.h"
#include "MooseVariable.h"
#include "libmesh/quadrature.h"
#include <limits>

registerMooseObject("raccoonApp", ADPorosityTimeDerivativeAlex);

InputParameters
ADPorosityTimeDerivativeAlex::validParams()
{
  InputParameters params = ADTimeKernel::validParams();
  params.addClassDescription("Kernel computing the rate of porosity coming from Materials.");
  params.addParam<MaterialPropertyName>(
      "porosity_name", "porosity", "Name of porosity material property");
  return params;
}

ADPorosityTimeDerivativeAlex::ADPorosityTimeDerivativeAlex(const InputParameters & parameters)
  : ADTimeKernel(parameters),
    _porosity(getADMaterialProperty<Real>(getParam<MaterialPropertyName>("porosity_name"))),
    _porosity_old(getMaterialPropertyOld<Real>(getParam<MaterialPropertyName>("porosity_name")))
{
}

ADReal
ADPorosityTimeDerivativeAlex::computeQpResidual()
{
  return _test[_i][_qp] * ((_porosity[_qp] - _porosity_old[_qp]) / _dt);
}
