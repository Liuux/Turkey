
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
	Real  _Source;
	Real  _precoff;
	Real  _m;
	Real  _ER;
	RealTensorValue  _permeability;
	Real  _viscosity;
	Real  _porosity;
// variables
	Real _T;
	RealGradient _gradient_T;
	Real _Rho;
	Real _Rho_dt;
	Real _RhoDot_dRho;
	Real _Pressure;
	RealGradient _gradient_Pressure;
//  variable number
	unsigned int _T_num;
	unsigned int _Rho_num;
	unsigned int _Pressure_num;
	// compute dsource_dt dsource_drho
	  Real _dsource_dT;
	  Real _dsource_dRho;
   // get grid movement
	  Real _disp_x;
	  Real _disp_y;
	  Real _disp_z;
	  Real _vm_x;
	  Real _vm_y;
	  Real _vm_z;
	  RealVectorValue _vm;

};

class Function;

class PyrolysisMaterial : public Material
{
public:
	PyrolysisMaterial(const std::string & name, InputParameters parameters);

protected:
	Real Source(Real rho,Real T,Real rhoc,Real rhov,Real precoff, Real ER,Real m);
    virtual void computeProperties();
  //get variables
  MaterialProperty<PropertyPack> & _property;
  VariableValue & _T_value;
  VariableGradient & _gradient_T_value;
  VariableValue & _Rho_value;
  VariableValue & _Rho_dt_value;
  VariableValue & _RhoDot_dRho_value;
  VariableValue & _Pressure_value;
  VariableGradient & _gradient_Pressure_value;
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
  RealTensorValue _permeability_value;
  Real  _viscosity_value;
  Real  _porosity_value;
  // get variables number
  unsigned int _T_num_value;
  unsigned int _Rho_num_value;
  unsigned int _Pressure_num_value;
// get grid movement
  VariableValue & _disp_x_value;
  VariableValue & _disp_y_value;
  VariableValue & _disp_z_value;
  VariableValue & _vm_x_value;
  VariableValue & _vm_y_value;
  VariableValue & _vm_z_value;


};

template<>
InputParameters validParams<PyrolysisMaterial>();
