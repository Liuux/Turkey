#include "SurfaceRecessionBC.h"

template<>
InputParameters validParams<SurfaceRecessionBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  MooseEnum component("x y z");
  params.addRequiredParam<MooseEnum>("component", component, "The desired component of velocity.");
  return params;
}

SurfaceRecessionBC::SurfaceRecessionBC(const InputParameters & parameters) :
  IntegratedBC(parameters),
   _bcproperty(getMaterialProperty<BCProperty>("bcproperty")),
   _property(getMaterialProperty<PropertyPack>("property")),
   _flux(getMaterialProperty<Real>("heat_flux")),
   _flux_jacobi(getMaterialProperty<Real>("heat_flux_jacobi")),
   _component(getParam<MooseEnum>("component"))
{}

Real SurfaceRecessionBC::computeQpResidual()
{
	if (abs(_property[_qp]._Rho - _property[_qp]._rhoc)<10)
			{

				return _test[_i][_qp]*_flux[_qp]*_normals[_qp](_component)/200000;
			}
	else
	       {
		        return 0;
	       }
}

