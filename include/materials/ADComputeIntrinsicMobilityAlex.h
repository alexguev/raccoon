//* This file is part of the RACCOON application
//* being developed at Dolbow lab at Duke University
//* http://dolbow.pratt.duke.edu

#pragma once

#include "Material.h"
#include "RankTwoTensorForward.h"

class ADComputeIntrinsicMobilityAlex : public Material
{
public:
  static InputParameters validParams();

  ADComputeIntrinsicMobilityAlex(const InputParameters & parameters);

  virtual void computeQpProperties() override;

  ADMaterialProperty<RankTwoTensor> & _intrinsic_mob;

  const ADMaterialProperty<Real> & _matrix_perm;

  const ADMaterialProperty<RankTwoTensor> & _fracture_perm;

  const ADMaterialProperty<Real> & _eta_w;

  const ADMaterialProperty<Real> & _eta_o;

  const ADVariableValue & _d;

  const Real & _mob_exp;

  //const ADVariableValue & _S;

  const Real & _visco;
};
