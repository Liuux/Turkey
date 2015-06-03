#pragma once

#include "TimeDerivative.h"
#include "Material.h"


class TemperatureTimeDerivative : public TimeDerivative
{
public:
	TemperatureTimeDerivative(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:
  MaterialProperty<Real> & _cp;
  MaterialProperty<Real> & _rho;
};

template<>
InputParameters validParams<TemperatureTimeDerivative>();
