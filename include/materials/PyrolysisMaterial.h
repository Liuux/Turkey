
#pragma once

#include "Material.h"
#include "LinearInterpolation.h"

class PropertyPack
{
public :
// properties
	Real  _k;
	Real  _cp;
    Real  _rhov;
	Real  _rhoc;
	Real  _cpg;
	Real  _rhog;
	Real  _deltaH;
	Real  _precoff;
	Real  _m;
	Real  _ER;
	Real  _permeability;
	Real  _viscosity;
	Real  _porosity;
// variables
	Real _T;
	RealGradient _gradient_T;
	Real _Rho;
};

class Function;

class PyrolysisMaterial : public Material
{
public:
	PyrolysisMaterial(const std::string & name, InputParameters parameters);

protected:
  virtual void computeProperties();
  //get variables
  MaterialProperty<PropertyPack> & _property;
  VariableValue & _T_value;
  VariableGradient & _gradient_T_value;
  VariableValue & _Rho_value;
  //get properties
  Real  _k_value;
  Real  _cp_value;
  Real  _rhov_value;
  Real  _rhoc_value;
  Real  _cpg_value;
  Real  _rhog_value;
  Real  _deltaH_value;
  Real  _precoff_value;
  Real  _m_value;
  Real  _ER_value;
  Real  _permeability_value;
  Real  _viscosity_value;
  Real  _porosity_value;


};

template<>
InputParameters validParams<PyrolysisMaterial>();
