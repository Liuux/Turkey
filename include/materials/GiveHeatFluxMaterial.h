
#pragma once

#include "Material.h"
#include "libmesh/meshfree_interpolation.h"
#include "PyrolysisMaterial.h"
using std::string;
using std::vector;

class Function;

class GiveHeatFluxMaterial : public Material
{
public:
	GiveHeatFluxMaterial(const InputParameters & parameters);

protected:
  virtual void computeProperties();

private:
  const MaterialProperty<PropertyPack> & _property;
  MaterialProperty<Real> & _flux;
  MaterialProperty<Real> & _flux_jacobi;

  VariableValue & _temperature;

  Real _epsilon;
  Real _tw0;
  Real _ts;
  Real _qc;
};

template<>
InputParameters validParams<GiveHeatFluxMaterial>();
