//* This file is part of the RACCOON application
//* being developed at Dolbow lab at Duke University
//* http://dolbow.pratt.duke.edu

#pragma once

#include "Material.h"

class ADComputeDeformationJacobian : public Material
{
public:
  static InputParameters validParams();

  ADComputeDeformationJacobian(const InputParameters & parameters);

protected:
  virtual void initQpStatefulProperties() override;
  virtual void computeQpProperties() override;

  ADMaterialProperty<Real> & _J;

  const ADMaterialProperty<RankTwoTensor> & _Fm;
};
