#pragma once

#include "Kernel.h"
#include "Material.h"
#include "PyrolysisMaterial.h"

class HeatConductionKernel : public Kernel
{
public:

HeatConductionKernel(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:
  MaterialProperty<PropertyPack> & _property;
};

template<>
InputParameters validParams<HeatConductionKernel>();
