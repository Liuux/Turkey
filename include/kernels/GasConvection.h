#pragma once

#include "Kernel.h"
#include "PyrolysisMaterial.h"
class GasConvection : public Kernel
{
public:

	GasConvection(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);
private:
  const MaterialProperty<PropertyPack> & _property;
};

template<>
InputParameters validParams<GasConvection>();
