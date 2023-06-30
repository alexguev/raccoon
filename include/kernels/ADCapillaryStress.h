//* This file is part of the RACCOON application
//* being developed at Dolbow lab at Duke University
//* http://dolbow.pratt.duke.edu

#pragma once

#include "ADKernel.h"
#include "ADRankTwoTensorForward.h"

class ADCapillaryStress : public ADKernel
{
public:
  static InputParameters validParams();

  ADCapillaryStress(const InputParameters & parameters);

protected:
  virtual ADReal computeQpResidual() override;

  const ADMaterialProperty<RankTwoTensor> & _fluid_mob;

  //const ADMaterialProperty<Real> & _fluid_mob;

  const ADMaterialProperty<Real> & _kappa;

  std::vector<const ADVariableValue *> _phis;

  std::vector<const ADVariableGradient *> _grad_phis;
};
