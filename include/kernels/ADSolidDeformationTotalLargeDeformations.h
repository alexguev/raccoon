//* This file is part of the RACCOON application
//* being developed at Dolbow lab at Duke University
//* http://dolbow.pratt.duke.edu

#pragma once

#include "ADTimeKernel.h"

class ADSolidDeformationTotalLargeDeformations : public ADTimeKernel
{
public:
  static InputParameters validParams();

  ADSolidDeformationTotalLargeDeformations(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  const ADMaterialProperty<Real> & _porosity;

  const ADMaterialProperty<Real> & _logJ;

  const MaterialProperty<Real> & _logJ_old;
};
