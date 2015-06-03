
#pragma once

#include "Material.h"
#include "LinearInterpolation.h"

class Function;

class PyrolysisMaterial : public Material
{
public:
	PyrolysisMaterial(const std::string & name, InputParameters parameters);

protected:
  virtual void computeProperties();

  MaterialProperty<Real> & _k;
  MaterialProperty<Real> & _cp;
  MaterialProperty<Real> & _rho;
  MaterialProperty<Real> & _rhov;
  MaterialProperty<Real> & _rhoc;
  MaterialProperty<Real> & _cpg;
  MaterialProperty<Real> & _rhog;
  MaterialProperty<Real> & _deltaH;
  MaterialProperty<Real> & _precoff;
  MaterialProperty<Real> & _m;
  MaterialProperty<Real> & _ER;
  MaterialProperty<Real> & _permeability;
  MaterialProperty<Real> & _viscosity;
  MaterialProperty<Real> & _porosity;
  VariableGradient & _temperature_gradient;
//  VariableGradient & _pressure_gradient;
   Real  _k_value;
   Real  _cp_value;
   Real  _rho_value;
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
