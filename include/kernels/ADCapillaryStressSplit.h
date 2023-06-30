//* This file is part of the RACCOON application
//* being developed at Dolbow lab at Duke University
//* http://dolbow.pratt.duke.edu

#pragma once

#include "ADKernel.h"

class ADCapillaryStressSplit : public ADKernel
{
public:
  static InputParameters validParams();

  ADCapillaryStressSplit(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  const ADVariableGradient & _grad_v;

  const unsigned int _component;
};
