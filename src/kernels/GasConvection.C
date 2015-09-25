
#include "GasConvection.h"

template<>
InputParameters validParams<GasConvection>()
{
  InputParameters params = validParams<Kernel>();
  return params;
}

GasConvection::GasConvection(const InputParameters & parameters) :
		Kernel(parameters),
      _property(getMaterialProperty<PropertyPack>("property"))
{
}

Real
GasConvection::computeQpResidual()
{
  Real r(0);
  r = -_property[_qp]._rhog*_property[_qp]._cpg*_property[_qp]._permeability/_property[_qp]._viscosity/_property[_qp]._porosity*_property[_qp]._gradient_Pressure*_property[_qp]._gradient_T*_test[_i][_qp];
  return r;
}
Real GasConvection::computeQpJacobian()
{
  return -_property[_qp]._rhog*_property[_qp]._cpg*_property[_qp]._permeability/_property[_qp]._viscosity/_property[_qp]._porosity*_property[_qp]._gradient_Pressure*_test[_i][_qp]*_grad_phi[_j][_qp];
}
Real  GasConvection::computeQpOffDiagJacobian(unsigned int jvar)
 {


	 if ( jvar == _property[_qp]._Pressure_num)
	    {
	 	  return -_property[_qp]._rhog*_property[_qp]._cpg*_property[_qp]._permeability/_property[_qp]._viscosity/_property[_qp]._porosity*_grad_phi[_j][_qp]*_property[_qp]._gradient_T*_test[_i][_qp];
		  }
		 else
		  {
			 return 0;
		  }


 }

