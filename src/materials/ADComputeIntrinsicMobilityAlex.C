//* This file is part of the RACCOON application
//* being developed at Dolbow lab at Duke University
//* http://dolbow.pratt.duke.edu

#include "ADComputeIntrinsicMobilityAlex.h"

registerMooseObject("raccoonApp", ADComputeIntrinsicMobilityAlex);

InputParameters
ADComputeIntrinsicMobilityAlex::validParams()
{
  InputParameters params = Material::validParams();
  params.addClassDescription("compute intrinsice mobility k over harmonic viscosity");
  params.addParam<MaterialPropertyName>(
      "intrinsic_mobility_name", "intrinsic_mobility", "Name of intrinsic mobility material property");
  params.addParam<MaterialPropertyName>(
      "matrix_permeability_name", "matrix_permeability", "matrix_permeability");
  params.addParam<MaterialPropertyName>(
      "fracture_permeability_name", "fracture_permeability", "Name of fracture permeability material property");
  params.addParam<MaterialPropertyName>(
      "water_viscosity_name", "water_viscosity", "water_viscosity");
  params.addParam<MaterialPropertyName>(
      "oil_viscosity_name", "oil_viscosity", "oil_viscosity");
  params.addRequiredCoupledVar("damage", "damage field");
  params.addRequiredParam<Real>("mobility_exponent", "exponent used in mobility equation");
  //params.addRequiredCoupledVar("saturation", "saturation variable");
  params.addRequiredParam<Real>("visco", "coeff used to control magniture of kernel");
  return params;
}

ADComputeIntrinsicMobilityAlex::ADComputeIntrinsicMobilityAlex(const InputParameters & parameters)
  : Material(parameters),
    _intrinsic_mob(
        declareADProperty<RankTwoTensor>(getParam<MaterialPropertyName>("intrinsic_mobility_name"))),
    _matrix_perm(getADMaterialProperty<Real>("matrix_permeability_name")),
    _fracture_perm(getADMaterialProperty<RankTwoTensor>("fracture_permeability_name")),
    _eta_w(getADMaterialProperty<Real>("water_viscosity_name")),
    _eta_o(getADMaterialProperty<Real>("oil_viscosity_name")),
    _d(adCoupledValue("damage")),
    _mob_exp(getParam<Real>("mobility_exponent")),
    //_S(adCoupledValue("saturation")),
    _visco(getParam<Real>("visco"))
{
}

void
ADComputeIntrinsicMobilityAlex::computeQpProperties()
{
  ADRankTwoTensor identity(ADRankTwoTensor::initIdentity);

  //_intrinsic_mob[_qp] = _coeff * (_matrix_perm[_qp] * identity + std::pow(_d[_qp], _mob_exp) * _fracture_perm[_qp]) * 1e-4;
  //_intrinsic_mob[_qp] = _coeff * (_matrix_perm[_qp] * identity + std::pow(_d[_qp], _mob_exp) * _fracture_perm[_qp]) * (_eta_w[_qp] + _eta_o[_qp]) / (2 * _eta_w[_qp] * _eta_o[_qp]);
  //_intrinsic_mob[_qp] = (_matrix_perm[_qp] * identity + std::pow(_d[_qp], _mob_exp) * _fracture_perm[_qp]) / (std::max(_S[_qp],0) *_eta_w[_qp] + std::min(1-_S[_qp],1) * _eta_o[_qp]);
  _intrinsic_mob[_qp] = (_matrix_perm[_qp] * identity + std::pow(_d[_qp], _mob_exp) * _fracture_perm[_qp]) / _visco;
}
