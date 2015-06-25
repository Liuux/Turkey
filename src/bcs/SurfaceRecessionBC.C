#include "SurfaceRecessionBC.h"

template<>
InputParameters validParams<SurfaceRecessionBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  MooseEnum component("x y z");
  params.addRequiredParam<MooseEnum>("component", component, "The desired component of velocity.");
  return params;
}

SurfaceRecessionBC::SurfaceRecessionBC(const std::string & name, InputParameters parameters) :
  IntegratedBC(name, parameters),
   _bcproperty(getMaterialProperty<BCProperty>("bcproperty")),
   _component(getParam<MooseEnum>("component"))
{}

Real SurfaceRecessionBC::computeQpResidual()
{
     return _test[_i][_qp]*_bcproperty[_qp]._flux*_normals[_qp](_component);
//     return -_test[_i][_qp] * _normals[_qp](_component)/50;
}

