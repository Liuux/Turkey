
#pragma once

#include "IntegratedBC.h"
#include "IntegratedBCMaterial.h"
#include "PyrolysisMaterial.h"

class SurfaceRecessionBC : public IntegratedBC
{
public:
	SurfaceRecessionBC(const std::string & name, InputParameters parameters);
protected:
	virtual Real computeQpResidual();
	const MaterialProperty<BCProperty> & _bcproperty;
	const MaterialProperty<PropertyPack> & _property;
	int _component;
};

template<>
InputParameters validParams<SurfaceRecessionBC>();
