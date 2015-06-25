
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
	MaterialProperty<BCProperty> & _bcproperty;
	MaterialProperty<PropertyPack> & _property;
	int _component;
};

template<>
InputParameters validParams<SurfaceRecessionBC>();
