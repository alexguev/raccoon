//* This file is part of the RACCOON application
//* being developed at Dolbow lab at Duke University
//* http://dolbow.pratt.duke.edu

#pragma once

#include "ADTimeKernel.h"

class ADSolidDeformationWater : public ADTimeKernel
{
public:
  static InputParameters validParams();

  ADSolidDeformationWater(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  const ADMaterialProperty<Real> & _porosity;

  const ADVariableValue & _saturation;

  const ADMaterialProperty<RankTwoTensor> & _strain;
  const MaterialProperty<RankTwoTensor> & _strain_old;
};
