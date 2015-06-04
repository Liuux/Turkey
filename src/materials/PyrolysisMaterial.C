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
  params.addRequiredCoupledVar("rho", "Coupled Density");

  return params;
}

PyrolysisMaterial::PyrolysisMaterial(const std::string & name, InputParameters parameters) :
      Material(name, parameters),
	  _property(declareProperty<PropertyPack>("property")),
	  _T_value(coupledValue("temperature")),
      _gradient_T_value(coupledGradient("temperature")),
	  _Rho_value(coupledValue("rho"))

{
	_k_value = getParam<Real>("k");
	_cp_value = (getParam<Real>("cp"));
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
	  _property[qp]._k = _k_value;
	  _property[qp]._cp = _cp_value;
	  _property[qp]._rhov = _rhov_value;
	  _property[qp]._rhoc = _rhoc_value;
	  _property[qp]._cpg = _cpg_value;
	  _property[qp]._rhog = _rhog_value;
	  _property[qp]._deltaH = _deltaH_value;
	  _property[qp]._precoff = _precoff_value,
	  _property[qp]._m = _m_value;
	  _property[qp]._ER = _ER_value;
	  _property[qp]._permeability = _permeability_value;
	  _property[qp]._viscosity = _viscosity_value;
	  _property[qp]._porosity = _porosity_value;
	  _property[qp]._T = _T_value[qp];
	  _property[qp]._gradient_T = _gradient_T_value[qp];
	  _property[qp]._Rho = _Rho_value[qp];
  }
}





