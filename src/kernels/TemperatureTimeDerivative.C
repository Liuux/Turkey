#include "TemperatureTimeDerivative.h"

template<>
InputParameters validParams<TemperatureTimeDerivative>()
{
  InputParameters params = validParams<TimeDerivative>();
  return params;
}

TemperatureTimeDerivative::TemperatureTimeDerivative(const std::string & name, InputParameters parameters) :
    TimeDerivative(name, parameters),
    _cp(getMaterialProperty<Real>("specific_heat")),
    _rho(getMaterialProperty<Real>("density"))
{
}

Real TemperatureTimeDerivative::computeQpResidual()
{
  return _rho[_qp]*_cp[_qp]*_u_dot[_qp]*_test[_i][_qp];
}

Real TemperatureTimeDerivative::computeQpJacobian()
{
  Real r(0);
  r = _rho[_qp]*(_cp[_qp])*_phi[_j][_qp]*_du_dot_du[_qp]*_test[_i][_qp];
  return r;
}
