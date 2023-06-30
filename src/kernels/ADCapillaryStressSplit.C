//* This file is part of the RACCOON application
//* being developed at Dolbow lab at Duke University
//* http://dolbow.pratt.duke.edu

#include "ADCapillaryStressSplit.h"

registerMooseObject("raccoonApp", ADCapillaryStressSplit);

InputParameters
ADCapillaryStressSplit::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addClassDescription(
      "Kernel computing the gradient of the order parameter, to be used in capillary stress kernel");
      params.addCoupledVar("saturation","saturation variable");
      params.addRequiredParam<unsigned int>("component",
                                            "An integer corresponding to the direction "
                                            "the variable this kernel acts in. (0 for x, "
                                            "1 for y, 2 for z)");
  return params;
}

ADCapillaryStressSplit::ADCapillaryStressSplit(const InputParameters & parameters)
  : ADKernel(parameters),
  _grad_v(adCoupledGradient("saturation")),
  _component(getParam<unsigned int>("component"))
{
}

ADReal
ADCapillaryStressSplit::computeQpResidual()
{
  return (_u[_qp] - _grad_v[_qp](_component)) *  _test[_i][_qp];
}
