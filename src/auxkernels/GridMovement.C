
#include "GridMovement.h"
#include<iostream>

template<>
InputParameters validParams<GridMovement>()
{
  InputParameters params = validParams<AuxKernel>();
  MooseEnum component("x y z");
  params.addRequiredParam<MooseEnum>("component", component, "The desired component of velocity.");
  return params;
}

GridMovement::GridMovement(const InputParameters & parameters) :
    AuxKernel(parameters),
	_component(getParam<MooseEnum>("component")),
    _property(getMaterialProperty<PropertyPack>("property"))
{
}

Real
GridMovement::computeValue()
{
	using namespace std;
	RealVectorValue tmp;
	tmp(0) = _property[_qp]._vm_x;
	tmp(1) = _property[_qp]._vm_y;
	tmp(2) = _property[_qp]._vm_z;
  return tmp(_component);
}
