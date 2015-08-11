
#include "DisplaceTimeDerivative.h"

template<>
InputParameters validParams<DisplaceTimeDerivative>()
{
  InputParameters params = validParams<TimeKernel>();
  params.addParam<bool>("lumping", false, "True for mass matrix lumping, false otherwise");
  params.addParam<Real>("damp",0, "damp");
  return params;
}

DisplaceTimeDerivative::DisplaceTimeDerivative(const InputParameters & parameters) :
    TimeKernel(parameters),
    _lumping(getParam<bool>("lumping")),
	_damp(getParam<Real>("damp"))
{
}

Real
DisplaceTimeDerivative::computeQpResidual()
{
  return _damp*_test[_i][_qp]*_u_dot[_qp];
}

Real
DisplaceTimeDerivative::computeQpJacobian()
{
  return _damp*_test[_i][_qp]*_phi[_j][_qp]*_du_dot_du[_qp];
}

void
DisplaceTimeDerivative::computeJacobian()
{
  if (_lumping)
  {
    DenseMatrix<Number> & ke = _assembly.jacobianBlock(_var.number(), _var.number());

    for (_i = 0; _i < _test.size(); _i++)
      for (_j = 0; _j < _phi.size(); _j++)
        for (_qp = 0; _qp < _qrule->n_points(); _qp++)
        {
          ke(_i, _i) += _JxW[_qp] * _coord[_qp] * computeQpJacobian();
        }
  }
  else
    TimeKernel::computeJacobian();
}
