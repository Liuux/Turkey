
#include "NormalRecessionBC.h"
#include "Function.h"

template<>
InputParameters validParams<NormalRecessionBC>()
{
  InputParameters params = validParams<NodalBC>();
  MooseEnum component("x y z");
  params.addRequiredParam<MooseEnum>("component", component, "The desired component of velocity.");
  params.addCoupledVar("nx", "x-component of the normal");
  params.addCoupledVar("ny", "y-component of the normal");
  params.addCoupledVar("nz", "z-component of the normal");
  params.addCoupledVar("variableold", "variable");
  params.addCoupledVar("temperature", "temperature");
  params.addCoupledVar("rho", "rho");
  params.addRequiredParam<Real>("startRho", "startRho");
  params.addRequiredParam<Real>("ablatecoff", "ablatecoff");
  params.set<std::vector<VariableName> >("nx") = std::vector<VariableName>(1, "nodal_normal_x");
  params.set<std::vector<VariableName> >("ny") = std::vector<VariableName>(1, "nodal_normal_y");
  params.set<std::vector<VariableName> >("nz") = std::vector<VariableName>(1, "nodal_normal_z");
  return params;
}

NormalRecessionBC::NormalRecessionBC(const InputParameters & parameters) :
    NodalBC( parameters),
	_component(getParam<MooseEnum>("component")),
	_nx(coupledValue("nx")),
	_ny(coupledValue("ny")),
	_nz(coupledValue("nz")),
	_oldu(coupledValueOld("variableold")),
	_T(coupledValue("temperature")),
	_Rho(coupledValue("rho")),
	_startRho(getParam<Real>("startRho")),
	_ablateCoff(getParam<Real>("ablatecoff"))
{
}

Real
NormalRecessionBC::computeQpResidual()
{
	if ((_Rho[_qp]-_startRho)<3)
	{
		if (_component == 0)
		{
			return _u[_qp]-_oldu[_qp]+_T[_qp]*_nx[_qp]/_ablateCoff*_dt;
		}
		else
		{
			if(_component == 1)
			{
				return _u[_qp]-_oldu[_qp]+_T[_qp]*_ny[_qp]/_ablateCoff*_dt;
			}
			else
			{
				return _u[_qp]-_oldu[_qp]+_T[_qp]*_nz[_qp]/_ablateCoff*_dt;
			}
		}
	}
	else
	{
		return 0;
	}
}
