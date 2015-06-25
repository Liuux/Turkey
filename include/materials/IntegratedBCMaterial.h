
#pragma once

#include "Material.h"
#include "LinearInterpolation.h"

class BCProperty
{
	public :
	Real _flux;
};
class Function;

class IntegratedBCMaterial : public Material
{
public:
	IntegratedBCMaterial(const std::string & name, InputParameters parameters);

protected:
  virtual void computeProperties();

  MaterialProperty<BCProperty> & _bcproperty;
  Real _flux_value;

};

template<>
InputParameters validParams<IntegratedBCMaterial>();
