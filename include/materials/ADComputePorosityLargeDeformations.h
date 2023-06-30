//* This file is part of the RACCOON application
//* being developed at Dolbow lab at Duke University
//* http://dolbow.pratt.duke.edu

#pragma once

#include "Material.h"

class ADComputePorosityLargeDeformations : public Material
{
public:
  static InputParameters validParams();

  ADComputePorosityLargeDeformations(const InputParameters & parameters);

protected:
  virtual void initQpStatefulProperties() override;
  virtual void computeQpProperties() override;

  const ADVariableValue & _p;

  const ADMaterialProperty<Real> & _J;

  ADMaterialProperty<Real> & _porosity;

  const ADVariableValue & _initial_porosity;

  const ADMaterialProperty<Real> & _Ks;
};
