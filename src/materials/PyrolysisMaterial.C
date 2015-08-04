#include "PyrolysisMaterial.h"
#include<iostream>
using std::cout;
using std::endl;

template<>
InputParameters validParams<PyrolysisMaterial>()
{
  InputParameters params = validParams<Material>();

  params.addParam<Real>("sigma", "sigma");
  params.addParam<Real>("kv", "kv");
  params.addParam<Real>("kc", "kc");
  params.addParam<Real>("cpv", "cpv");
  params.addParam<Real>("cpc", "cpc");
  params.addParam<Real>("rhov", "rhov");
  params.addParam<Real>("rhoc", "rhoc");
  params.addParam<Real>("cpg", "cpg");
  params.addParam<Real>("rhog", "rhog");
  params.addParam<Real>("deltaH", "deltaH");
  params.addParam<Real>("precoff", "precoff");
  params.addParam<Real>("m", "m");
  params.addParam<Real>("ER", "ER");
  params.addParam<RealTensorValue>("permeability", "permeability");
  params.addParam<Real>("viscosity", "viscosity");
  params.addParam<Real>("porosity", "porosity");
  params.addRequiredCoupledVar("temperature", "Coupled Temperature");
  params.addRequiredCoupledVar("rho", "Coupled Density");
  params.addRequiredCoupledVar("pressure", "gas pressure");
  params.addCoupledVar("disp_x",0, "disp_x");
  params.addCoupledVar("disp_y",0, "disp_y");
  params.addCoupledVar("disp_z",0, "disp_z");

  return params;
}
Real PyrolysisMaterial::Source(Real rho,Real T,Real rhoc,Real rhov,Real precoff, Real ER,Real m)
{
	if (T>600)
	{
		if ((rho-rhoc)<1)
		{
			return 0;
		}
		else
		{
			Real tmp = (rho-rhoc)/rhov;
			return  precoff*exp(-ER / T)*rhov*pow(tmp,m);
		}
	}
	else
	{
		return 0;
	}
}
PyrolysisMaterial::PyrolysisMaterial(const std::string & name, InputParameters parameters) :
      Material(name, parameters),
	  _property(declareProperty<PropertyPack>("property")),
	  _T_value(coupledValue("temperature")),
      _gradient_T_value(coupledGradient("temperature")),
	  _Rho_value(coupledValue("rho")),
	  _Rho_dt_value(coupledDot("rho")),
	  _RhoDot_dRho_value(coupledDotDu("rho")),
	  _Pressure_value(coupledValue("pressure")),
	  _gradient_Pressure_value(coupledGradient("pressure")),
	  _T_num_value(coupled("temperature")),
	  _Rho_num_value(coupled("rho")),
	  _Pressure_num_value(coupled("pressure")),
	  _disp_x_value(coupledValue("disp_x")),
	  _disp_y_value(coupledValue("disp_y")),
	  _disp_z_value(coupledValue("disp_z")),
	  _vm_x_value(coupledDot("disp_x")),
	  _vm_y_value(coupledDot("disp_y")),
	  _vm_z_value(coupledDot("disp_z"))

{
	_sigma_value = getParam<Real>("sigma");
	_kv_value = getParam<Real>("kv");
	_kc_value = getParam<Real>("kc");
	_cpv_value = (getParam<Real>("cpv"));
	_cpc_value = (getParam<Real>("cpc"));
	_rhov_value = getParam<Real> ("rhov");
	_rhoc_value = getParam<Real> ("rhoc");
	_cpg_value = getParam<Real> ("cpg");
	_rhog_value  = getParam<Real> ("rhog");
	_deltaH_value = getParam<Real> ("deltaH");
	_precoff_value = getParam<Real> ("precoff");
	_m_value = getParam<Real> ("m");
	_ER_value = getParam<Real> ("ER");
	_permeability_value = getParam<RealTensorValue> ("permeability");
	_viscosity_value = getParam<Real> ("viscosity");
	_porosity_value = getParam<Real> ("porosity");

}
void PyrolysisMaterial::computeProperties()
{
  Real epsi = 1E-08;
  for (unsigned int qp(0); qp < _qrule->n_points(); ++qp)
  {
	  _property[qp]._sigma = _sigma_value;
	  _property[qp]._charpercent = _rhov_value/(_rhov_value-_rhoc_value)*(1-_rhoc_value/_Rho_value[qp]);
	  _property[qp]._k = _kv_value*_property[qp]._charpercent+(1-_property[qp]._charpercent)*_kc_value;
	  _property[qp]._cp = _cpv_value*_property[qp]._charpercent+(1-_property[qp]._charpercent)*_cpc_value;
	  _property[qp]._rhov = _rhov_value;
	  _property[qp]._rhoc = _rhoc_value;
	  _property[qp]._cpg = _cpg_value;
	  _property[qp]._rhog = _rhog_value;
	  _property[qp]._deltaH = _deltaH_value;
	  _property[qp]._Source = Source( _Rho_value[qp],_T_value[qp],_rhoc_value,_rhov_value,_precoff_value,_ER_value,_m_value);
	  _property[qp]._precoff = _precoff_value,
	  _property[qp]._m = _m_value;
	  _property[qp]._ER = _ER_value;
	  _property[qp]._permeability = _permeability_value;
	  _property[qp]._viscosity = _viscosity_value;
	  _property[qp]._porosity = _porosity_value;
	  _property[qp]._T = _T_value[qp];
	  _property[qp]._gradient_T = _gradient_T_value[qp];
	  _property[qp]._Rho = _Rho_value[qp];
	  _property[qp]._Rho_dt = _Rho_dt_value[qp];
	  _property[qp]._RhoDot_dRho = _RhoDot_dRho_value[qp];
	  _property[qp]._Pressure = _Pressure_value[qp];
	  _property[qp]._gradient_Pressure = _gradient_Pressure_value[qp];
	  _property[qp]._T_num = _T_num_value;
	  _property[qp]._Rho_num = _Rho_num_value;
	  _property[qp]._Pressure_num = _Pressure_num_value;
	  _property[qp]._disp_x = _disp_x_value[qp];
	  _property[qp]._disp_y = _disp_y_value[qp];
	  _property[qp]._disp_z = _disp_z_value[qp];
	  _property[qp]._vm_x = _vm_x_value[qp];
	  _property[qp]._vm_y = _vm_y_value[qp];
	  _property[qp]._vm_z = _vm_z_value[qp];
	  _property[qp]._vm(0) = _property[qp]._vm_x;
	  _property[qp]._vm(1) = _property[qp]._vm_y;
	  _property[qp]._vm(2) = _property[qp]._vm_z;


	  Real epsi = 1E-08;
	  Real source = Source( _Rho_value[qp],_T_value[qp],_rhoc_value,_rhov_value,_precoff_value,_ER_value,_m_value);
	  Real source_new1 = Source( _Rho_value[qp],_T_value[qp]+epsi,_rhoc_value,_rhov_value,_precoff_value,_ER_value,_m_value);
	  Real source_new2 = Source( _Rho_value[qp]+epsi,_T_value[qp]+epsi,_rhoc_value,_rhov_value,_precoff_value,_ER_value,_m_value);
	  _property[qp]._dsource_dT = (source_new1-source)/epsi;
	 _property[qp]._dsource_dRho = (source_new2-source)/epsi;
  }
}





