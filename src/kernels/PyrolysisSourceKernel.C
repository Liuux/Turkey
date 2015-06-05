#include "PyrolysisSourceKernel.h"

template<>
InputParameters validParams<PyrolysisSourceKernel>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription(" Pyrolysis Source");
  return params;
}

PyrolysisSourceKernel::PyrolysisSourceKernel(const std::string & name, InputParameters parameters) :
     Kernel(name, parameters),
	 _property(getMaterialProperty<PropertyPack>("property"))
{
}

Real PyrolysisSourceKernel::computeQpResidual()
{
	Real r(0);
	r = _property[_qp]._deltaH * _property[_qp]._Rho_dt;
  return r;
}

Real PyrolysisSourceKernel::computeQpJacobian()
{
	Real r(0);
	r = _property[_qp]._deltaH * _property[_qp]._RhoDot_dRho * _test[_i][_qp] * _phi[_j][_qp];

   return r;
}
Real  PyrolysisSourceKernel::computeQpOffDiagJacobian(unsigned int jvar)
 {


//	 if ( jvar ==   _rho_num)
//	    {
//	 	  return( _phi[_j][_qp]*_cp *_u_dot[_qp]*_test[_i][_qp]+_deltaH * _rhoDot_dRho[_qp]  * _test[_i][_qp] * _phi[_j][_qp] );
//	    }
//	 else
//	 {
		 return (0);
//	 }
 }




