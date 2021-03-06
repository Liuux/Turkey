#pragma once

#include "Kernel.h"
#include "PyrolysisMaterial.h"

class PyrolysisSourceKernel : public Kernel
{
public:

	PyrolysisSourceKernel(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);
private:
  const MaterialProperty<PropertyPack> & _property;

};

template<>
InputParameters validParams< PyrolysisSourceKernel>();
