#include "DarcyPressure.h"

template<>
InputParameters validParams<DarcyPressure>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Daarcy Pressure");
  return params;
}

DarcyPressure::DarcyPressure(const std::string & name, InputParameters parameters) :
     Kernel(name, parameters),
	 _property(getMaterialProperty<PropertyPack>("property"))
{
}

Real DarcyPressure::computeQpResidual()
{
  Real r1(0);
  Real r2(0);
  r1 =  _property[_qp]._rhog*_property[_qp]._permeability/_property[_qp]._viscosity/_property[_qp]._porosity*_property[_qp]._gradient_Pressure*_grad_test[_i][_qp];
  r2 = _property[_qp]._Source*_test[_i][_qp];
//  r2 = 0.01*_test[_i][_qp];
  return (r1-r2);

}

Real DarcyPressure::computeQpJacobian()
{
	  return  _property[_qp]._permeability/_property[_qp]._viscosity/_property[_qp]._porosity*_grad_phi[_j][_qp] * _grad_test[_i][_qp];
}
Real  DarcyPressure::computeQpOffDiagJacobian(unsigned int jvar)
 {


	 if ( jvar == _property[_qp]._Rho_num  )
	    {
	 	  return(_property[_qp]._dsource_dRho * _test[_i][_qp] );
	    }
	 else
	 {
		 return (0);
	 }
 }




