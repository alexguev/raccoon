//* This file is part of the RACCOON application
//* being developed at Dolbow lab at Duke University
//* http://dolbow.pratt.duke.edu

#include "ADComputeFluidMobilityAlex.h"

registerMooseObject("raccoonApp", ADComputeFluidMobilityAlex);

InputParameters
ADComputeFluidMobilityAlex::validParams()
{
  InputParameters params = Material::validParams();
  params.addClassDescription("compute mobility in porous media including effect of damage");
  params.addParam<MaterialPropertyName>(
      "fluid_mobility_name", "fluid_mobility", "Name of fluid mobility material property");
  //params.addParam<MaterialPropertyName>(
  //    "fracture_permeability_name", "fracture_permeability", "Name of fracture permeability material property");
  //params.addRequiredCoupledVar("damage", "damage field");
  params.addParam<MaterialPropertyName>(
      "fluid_viscosity_name", "fluid_viscosity", "fluid_viscosity");
  params.addParam<MaterialPropertyName>(
      "intrinsic_permeability_name", "intrinsic_permeability", "intrinsic_permeability");
  //params.addRequiredParam<Real>("mobility_exponent", "exponent used in mobility equation");
  //params.addParam<Real>("initial_crack_opening", 0.0, "initial opening of a crack");
  params.addParam<MaterialPropertyName>(
      "relative_permeability_name", "relative_permeability", "relative_permeability");
  params.addRequiredParam<Real>("residual_mobility", "residual mobility in multiphase flow mobility");
  return params;
}

ADComputeFluidMobilityAlex::ADComputeFluidMobilityAlex(const InputParameters & parameters)
  : Material(parameters),
    _fluid_mob(
        declareADProperty<RankTwoTensor>(getParam<MaterialPropertyName>("fluid_mobility_name"))),
//_fracture_perm(
    //    declareADProperty<RankTwoTensor>(getParam<MaterialPropertyName>("fracture_permeability_name"))),
    //_wn(getADMaterialPropertyByName<Real>("crack_opening")),
  //  _d(adCoupledValue("damage")),
  //  _grad_d(adCoupledGradient("damage")),
    _eta(getADMaterialProperty<Real>("fluid_viscosity_name")),
    _K(getADMaterialProperty<Real>("intrinsic_permeability_name")),
    //_mob_eps(getParam<Real>("mobility_exponent")),
    //_wcr(getParam<Real>("initial_crack_opening")),
    _rel_perm(getADMaterialProperty<Real>("relative_permeability_name")),
    _mob_res(getParam<Real>("residual_mobility"))
{
}

void
ADComputeFluidMobilityAlex::computeQpProperties()
{
  ADRankTwoTensor identity(ADRankTwoTensor::initIdentity);

  //_matrix_mob[_qp] = _K[_qp] / _eta[_qp] * identity;

  //ADRealVectorValue n(0,1,0);
  //const Real eps = 1e-2; //should not be too low
  //ADRealVectorValue n;
  //ADRankTwoTensor nn;
  //if (_grad_d[_qp].norm() > 1e-15) {
  //if (_d[_qp] > 0.5 && _grad_d[_qp].norm() > 1e-15) {
    //n = _grad_d[_qp] / _grad_d[_qp].norm();
    //nn.vectorOuterProduct(n, n);
  //  _fracture_perm[_qp] = (_wn[_qp]+_wcr) * (_wn[_qp]+_wcr) / 12 * (identity - nn);
//  }
//  else {
//    n = 0;
//    _fracture_perm[_qp] = 0;
//  }

  //_fluid_mob[_qp] = (_K[_qp] / _eta[_qp] * identity + std::pow(_d[_qp], _mob_eps) * _fracture_perm[_qp] / _eta[_qp]) * _rel_perm[_qp]
                    //+  _mob_res * identity;
  _fluid_mob[_qp] = _K[_qp] / _eta[_qp] * identity * _rel_perm[_qp]
                                      +  _mob_res * identity;
}
