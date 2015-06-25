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
   _property(getMaterialProperty<PropertyPack>("property")),
   _component(getParam<MooseEnum>("component"))
{}

Real SurfaceRecessionBC::computeQpResidual()
{
	if (abs(_property[_qp]._Rho - _property[_qp]._rhoc)<50)
			{

				return _test[_i][_qp]*_bcproperty[_qp]._flux*_normals[_qp](_component)/10000000;
			}
	else
	       {
		        return 0;
	       }
}

