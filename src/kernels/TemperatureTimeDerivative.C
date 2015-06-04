#include "TemperatureTimeDerivative.h"

template<>
InputParameters validParams<TemperatureTimeDerivative>()
{
  InputParameters params = validParams<TimeDerivative>();
  return params;
}

TemperatureTimeDerivative::TemperatureTimeDerivative(const std::string & name, InputParameters parameters) :
    TimeDerivative(name, parameters),
	 _Property(getMaterialProperty<PropertyPack>("property"))
{
}

Real TemperatureTimeDerivative::computeQpResidual()
{
  return _Property[_qp]._Rho*_Property[_qp]._cp*_u_dot[_qp]*_test[_i][_qp];
}

Real TemperatureTimeDerivative::computeQpJacobian()
{
  Real r(0);
  r = _Property[_qp]._Rho*(_Property[_qp]._cp)*_phi[_j][_qp]*_du_dot_du[_qp]*_test[_i][_qp];
  return r;
}
