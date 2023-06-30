//* This file is part of the RACCOON application
//* being developed at Dolbow lab at Duke University
//* http://dolbow.pratt.duke.edu

#include "ADComputeDeformationJacobian.h"

registerMooseObject("raccoonApp",ADComputeDeformationJacobian);

InputParameters
ADComputeDeformationJacobian::validParams()
{
  InputParameters params = Material::validParams();
  params.addClassDescription(
      "compute the Jacobian, i.e. the determinant of the deformation gradient");
      //params.addRequiredParam<MaterialPropertyName>("jacobian_name", "jacobian of deformation gradient");
  return params;
}

ADComputeDeformationJacobian::ADComputeDeformationJacobian(const InputParameters & parameters)
  : Material(parameters),
  _J(declareADProperty<Real>("jacobian_name")),
  _Fm(getADMaterialPropertyByName<RankTwoTensor>("mechanical_deformation_gradient"))
{
}

void
ADComputeDeformationJacobian::initQpStatefulProperties()
{
  _J[_qp] = 1;
}

void
ADComputeDeformationJacobian::computeQpProperties()
{
      _J[_qp] = _Fm[_qp].det();

}
