#pragma once

#include "Kernel.h"
#include "PyrolysisMaterial.h"

class DarcyPressure : public Kernel
{
public:

	DarcyPressure(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:
  MaterialProperty<PropertyPack> & _property;

};

template<>
InputParameters validParams<DarcyPressure>();
