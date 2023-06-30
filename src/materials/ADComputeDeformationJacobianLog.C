//* This file is part of the RACCOON application
//* being developed at Dolbow lab at Duke University
//* http://dolbow.pratt.duke.edu

#include "ADComputeDeformationJacobianLog.h"

registerMooseObject("raccoonApp",ADComputeDeformationJacobianLog);

InputParameters
ADComputeDeformationJacobianLog::validParams()
{
  InputParameters params = Material::validParams();
  params.addClassDescription(
      "compute the logarithm of the Jacobian, where the Jacobian is the determinant of the deformation gradient");
  return params;
}

ADComputeDeformationJacobianLog::ADComputeDeformationJacobianLog(const InputParameters & parameters)
  : Material(parameters),
  _logJ(declareADProperty<Real>("log_jacobian_name")),
  _J(getADMaterialPropertyByName<Real>("jacobian_name"))
{
}

void
ADComputeDeformationJacobianLog::initQpStatefulProperties()
{
  _logJ[_qp] = 0;
}

void
ADComputeDeformationJacobianLog::computeQpProperties()
{

      _logJ[_qp] = std::log(_J[_qp]);
    //  std::cout << _logJ[_qp] << std::end;


}
