#include "GiveHeatFluxMaterial.h"
#include "libmesh/system.h"
#include "libmesh/radial_basis_interpolation.h"
#include<iostream>
using std::cout;
using std::endl;

template<>
InputParameters validParams<GiveHeatFluxMaterial>()
{
  InputParameters params = validParams<Material>();

  params.addRequiredCoupledVar("temperature", "Coupled Temperature");
  params.addRequiredParam<Real>("epsilon", "epsilon");
  params.addRequiredParam<Real>("tw0", "tw0");
  params.addRequiredParam<Real>("ts", "ts");
  params.addRequiredParam<Real>("qc", "qc");
  return params;
}

GiveHeatFluxMaterial::GiveHeatFluxMaterial(const InputParameters & parameters) :
      Material( parameters),
    _property(getMaterialProperty<PropertyPack>("property")),
    _flux(declareProperty<Real>("heat_flux")),
    _flux_jacobi(declareProperty<Real>("heat_flux_jacobi")),
    _temperature(coupledValue("temperature")),
	_epsilon(getParam<Real>("epsilon")),
	_tw0(getParam<Real>("tw0")),
	_ts(getParam<Real>("ts")),
	_qc(getParam<Real>("qc"))
	
 {
 }


void GiveHeatFluxMaterial::computeProperties()
{
	for(_qp = 0; _qp < _qrule->n_points(); ++_qp)
	{
		Real tw = _temperature[_qp];
		Real tw4 = Utility::pow<4>(tw);
		Real tw3 = Utility::pow<3>(tw);
	    _flux[_qp] = (_ts - tw)/(_ts - _tw0)*_qc - _epsilon*_property[_qp]._sigma*tw4;
	    _flux_jacobi[_qp] = -_qc/(_ts - _tw0) - 4*_epsilon*_property[_qp]._sigma*tw3;
	}
}
