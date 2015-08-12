#include "HeatConductionKernel.h"

template<>
InputParameters validParams<HeatConductionKernel>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Compute heat conductivity kernel ");
  return params;
}

HeatConductionKernel::HeatConductionKernel(const InputParameters & parameters) :
  Kernel(parameters),
  _property(getMaterialProperty<PropertyPack>("property"))
{
}

Real HeatConductionKernel::computeQpResidual()
{

  Real r(0);
  r = _property[_qp]._k* _property[_qp]._gradient_T * _grad_test[_i][_qp];
  return r;
}

Real HeatConductionKernel::computeQpJacobian()
{
  Real jac(0);
  jac =_property[_qp]._k*_grad_phi[_j][_qp] * _grad_test[_i][_qp];
  return jac;
}
