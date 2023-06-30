//* This file is part of the RACCOON application
//* being developed at Dolbow lab at Duke University
//* http://dolbow.pratt.duke.edu

#pragma once

#include "Material.h"

class ADComputeDeformationJacobianLog : public Material
{
public:
  static InputParameters validParams();

  ADComputeDeformationJacobianLog(const InputParameters & parameters);

protected:
  virtual void initQpStatefulProperties() override;
  virtual void computeQpProperties() override;

  ADMaterialProperty<Real> & _logJ;

  const ADMaterialProperty<Real> & _J;


};
