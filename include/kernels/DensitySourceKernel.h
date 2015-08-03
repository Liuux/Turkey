#pragma once

#include "Kernel.h"
#include "PyrolysisMaterial.h"
class DensitySourceKernel : public Kernel
{
public:

DensitySourceKernel(const std::string & name, InputParameters parameters);
protected:
  Real Source(Real rho,Real T,Real rhoc,Real rhov,Real precoff, Real ER,Real m);
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

private:
   const MaterialProperty<PropertyPack> & _property;

};

template<>
InputParameters validParams<DensitySourceKernel>();
