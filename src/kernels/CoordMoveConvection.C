
#include "CoordMoveConvection.h"

template<>
InputParameters validParams<CoordMoveConvection>()
{
  InputParameters params = validParams<Kernel>();
  return params;
}

CoordMoveConvection::CoordMoveConvection(const std::string & name, InputParameters parameters) :
		Kernel(name, parameters),
      _property(getMaterialProperty<PropertyPack>("property"))
{
}

Real
CoordMoveConvection::computeQpResidual()
{
  Real r(0);
  r =_property[_qp]._vm*_property[_qp]._Rho*_property[_qp]._cp*_property[_qp]._gradient_T*_test[_i][_qp];
  return r;
}
Real CoordMoveConvection::computeQpJacobian()
{
  return _property[_qp]._vm*_property[_qp]._Rho*_property[_qp]._cp*_test[_i][_qp]*_grad_phi[_j][_qp];
}
Real  CoordMoveConvection::computeQpOffDiagJacobian(unsigned int jvar)
 {


	 if ( jvar == _property[_qp]._Rho_num)
	    {
	 	  return _property[_qp]._vm*_property[_qp]._cp*_property[_qp]._gradient_T*_test[_i][_qp]*_phi[_j][_qp];
		  }
		 else
		  {
			 return 0;
		  }


 }

