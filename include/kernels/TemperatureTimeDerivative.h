#pragma once

#include "TimeDerivative.h"
#include "Material.h"
#include "PyrolysisMaterial.h"


class TemperatureTimeDerivative : public TimeDerivative
{
public:
	TemperatureTimeDerivative(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:
  const MaterialProperty<PropertyPack> & _Property;;
};

template<>
InputParameters validParams<TemperatureTimeDerivative>();
