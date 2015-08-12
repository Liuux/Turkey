
#pragma once

#include "IntegratedBC.h"
#include "IntegratedBCMaterial.h"
#include "PyrolysisMaterial.h"

class SurfaceRecessionBC : public IntegratedBC
{
public:
	SurfaceRecessionBC(const InputParameters & parameters);
protected:
	virtual Real computeQpResidual();
	const MaterialProperty<BCProperty> & _bcproperty;
	const MaterialProperty<PropertyPack> & _property;
	const MaterialProperty<Real> & _flux;
	const MaterialProperty<Real> & _flux_jacobi;

	int _component;
};

template<>
InputParameters validParams<SurfaceRecessionBC>();
