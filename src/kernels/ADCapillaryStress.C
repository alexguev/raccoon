//* This file is part of the RACCOON application
//* being developed at Dolbow lab at Duke University
//* http://dolbow.pratt.duke.edu

#include "ADCapillaryStress.h"

registerMooseObject("raccoonApp", ADCapillaryStress);

InputParameters
ADCapillaryStress::validParams()
{
  InputParameters params = ADKernel::validParams();
  params.addClassDescription(
      "Kernel computing the divergence of the capillary stress multiplied by mobility");
  params.addRequiredParam<MaterialPropertyName>(
      "mobility_name", "Name of fluid mobility material property");
  params.addParam<MaterialPropertyName>("kappa", "Gradient energy coefficient");
  params.addRequiredCoupledVar("phis", "3 components of variable phi");
  return params;
}

ADCapillaryStress::ADCapillaryStress(const InputParameters & parameters)
  : ADKernel(parameters),
  _fluid_mob(getADMaterialProperty<RankTwoTensor>("mobility_name")),
  //_fluid_mob(getADMaterialProperty<Real>("mobility_name")),
  _kappa(getADMaterialProperty<Real>("kappa")),
  //_nphi(coupledComponents("phis")),
  _phis(adCoupledValues("phis")),
  _grad_phis(adCoupledGradients("phis"))
  //_v(adCoupledValue("phi1a")),
  //_v(adCoupledValue("phi1")),
//  _grad_v(adCoupledGradient("saturation_gradient"))
{
  _phis.resize(3,&_ad_zero);
  _grad_phis.resize(3, &_ad_grad_zero);
}

ADReal
ADCapillaryStress::computeQpResidual()
{
  auto F = ADRankTwoTensor::initializeFromRows(
      (*_grad_phis[0])[_qp], (*_grad_phis[1])[_qp], (*_grad_phis[2])[_qp]);

  ADRealVectorValue phi((*_phis[0])[_qp], (*_phis[1])[_qp], (*_phis[2])[_qp]);

  return _fluid_mob[_qp] * _kappa[_qp] * (F * phi + F.trace() * phi) * _grad_test[_i][_qp];
}
