#include "PyrolysisMaterial.h"
#include<iostream>
using std::cout;
using std::endl;

template<>
InputParameters validParams<PyrolysisMaterial>()
{
  InputParameters params = validParams<Material>();

  params.addParam<Real>("k", "k");
  params.addParam<Real>("cp", "cp");
  params.addParam<Real>("rho", "rho");
  params.addParam<Real>("rhov", "rhov");
  params.addParam<Real>("rhoc", "rhoc");
  params.addParam<Real>("cpg", "cpg");
  params.addParam<Real>("rhog", "rhog");
  params.addParam<Real>("deltaH", "deltaH");
  params.addParam<Real>("precoff", "precoff");
  params.addParam<Real>("m", "m");
  params.addParam<Real>("ER", "ER");
  params.addParam<Real>("permeability", "permeability");
  params.addParam<Real>("viscosity", "viscosity");
  params.addParam<Real>("porosity", "porosity");
  params.addRequiredCoupledVar("temperature", "Coupled Temperature");
//  params.addRequiredCoupledVar("pressure", "Coupled Pressure");
  return params;
}

PyrolysisMaterial::PyrolysisMaterial(const std::string & name, InputParameters parameters) :
      Material(name, parameters),
    _k(declareProperty<Real>("thermal_conductivity")),
    _cp(declareProperty<Real>("specific_heat")),
    _rho(declareProperty<Real>("density")),
	_rhov(declareProperty<Real>("virgindensity")),
	_rhoc(declareProperty<Real>("chardensity")),
	_cpg(declareProperty<Real>("pygas_specific_heat")),
	_rhog( declareProperty<Real>("pygas_density")),
	_deltaH( declareProperty<Real>("pyrolysis_heat")),
	_precoff( declareProperty<Real>("prexp_coff")),
	_m( declareProperty<Real>("power_number")),
	_ER( declareProperty<Real>("E/R")),
	_permeability( declareProperty<Real>("permeability")),
	_viscosity( declareProperty<Real>("viscosity")),
	_porosity( declareProperty<Real>("porosity")),
	_temperature_gradient(coupledGradient("temperature"))
//    _pressure_gradient(coupledGradient("pressure"))

{
	_k_value = getParam<Real>("k");
	_cp_value = (getParam<Real>("cp"));
	_rho_value = getParam<Real> ("rho");
	_rhov_value = getParam<Real> ("rhov");
	_rhoc_value = getParam<Real> ("rhoc");
	_cpg_value = getParam<Real> ("cpg");
	_rhog_value  = getParam<Real> ("rhog");
	_deltaH_value = getParam<Real> ("deltaH");
	_precoff_value = getParam<Real> ("precoff");
	_m_value = getParam<Real> ("m");
	_ER_value = getParam<Real> ("ER");
	_permeability_value = getParam<Real> ("permeability");
	_viscosity_value = getParam<Real> ("viscosity");
	_porosity_value = getParam<Real> ("porosity");
}
void PyrolysisMaterial::computeProperties()
{
  Real epsi = 1E-08;
  for (unsigned int qp(0); qp < _qrule->n_points(); ++qp)
  {
	    _k[qp] = _k_value;
	    _cp[qp] = _cp_value;
	    _rho[qp] = _rho_value;
	 	_rhov[qp] = _rhov_value;
	 	_rhoc[qp] = _rhoc_value;
	 	_cpg[qp] = _cpg_value;
	 	_rhog[qp] = _rhog_value;
	 	_deltaH[qp] = _deltaH_value;
	 	_precoff[qp] = _precoff_value,
	 	_m[qp] = _m_value;
	 	_ER[qp] = _ER_value;
	 	_permeability[qp] = _permeability_value;
	 	_viscosity[qp] = _viscosity_value;
	 	_porosity[qp] = _porosity_value;
  }
}





