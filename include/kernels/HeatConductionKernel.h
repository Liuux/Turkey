#pragma once

#include "Kernel.h"
#include "Material.h"
#include "PyrolysisMaterial.h"

class HeatConductionKernel : public Kernel
{
public:

HeatConductionKernel(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:
 const MaterialProperty<PropertyPack> & _property;
};

template<>
InputParameters validParams<HeatConductionKernel>();
