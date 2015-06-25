#include "IntegratedBCMaterial.h"
#include<iostream>
using std::cout;
using std::endl;

template<>
InputParameters validParams<IntegratedBCMaterial>()
{
  InputParameters params = validParams<Material>();
  params.addParam<Real>("flux", "flux");
  return params;
}

IntegratedBCMaterial::IntegratedBCMaterial(const std::string & name, InputParameters parameters) :
      Material(name, parameters),
	  _bcproperty( declareProperty<BCProperty>("Sigma"))
{
	_flux_value = getParam<Real> ("flux");
}

void IntegratedBCMaterial::computeProperties()
{
  Real epsi = 1E-08;
  for (unsigned int qp(0); qp < _qrule->n_points(); ++qp)
  {
	  _bcproperty[qp]._flux= _flux_value;
  }
}

