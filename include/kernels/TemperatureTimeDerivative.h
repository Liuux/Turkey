#pragma once

#include "TimeDerivative.h"
#include "Material.h"
#include "PyrolysisMaterial.h"


class TemperatureTimeDerivative : public TimeDerivative
{
public:
	TemperatureTimeDerivative(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:
  MaterialProperty<PropertyPack> & _Property;;
};

template<>
InputParameters validParams<TemperatureTimeDerivative>();
