
#include "PyrolysisGasVelocity.h"


template<>
InputParameters validParams<PyrolysisGasVelocity>()
{
  InputParameters params = validParams<AuxKernel>();
  MooseEnum component("x y z");

  params.addRequiredParam<MooseEnum>("component", component, "The desired component of velocity.");
  return params;
}

PyrolysisGasVelocity::PyrolysisGasVelocity(const std::string & name, InputParameters parameters) :
    AuxKernel(name, parameters),

    _component(getParam<MooseEnum>("component")),
    _property(getMaterialProperty<PropertyPack>("property"))
{
}

Real
PyrolysisGasVelocity::computeValue()
{
	RealVectorValue tmp = _property[_qp]._rhog*_property[_qp]._permeability/_property[_qp]._viscosity/_property[_qp]._porosity*_property[_qp]._gradient_Pressure;
  return -tmp(_component);
//  return -_kp/_viscosity/_poro*_pressure_gradient[_qp](_component);
}
