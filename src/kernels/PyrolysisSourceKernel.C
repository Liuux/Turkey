#include "PyrolysisSourceKernel.h"

template<>
InputParameters validParams<PyrolysisSourceKernel>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription(" Pyrolysis Source");
  return params;
}

PyrolysisSourceKernel::PyrolysisSourceKernel(const InputParameters & parameters) :
     Kernel(parameters),
	 _property(getMaterialProperty<PropertyPack>("property"))
{
}

Real PyrolysisSourceKernel::computeQpResidual()
{
	Real r(0);
	r = _property[_qp]._deltaH * _property[_qp]._Source* _test[_i][_qp];
  return r;
}

Real PyrolysisSourceKernel::computeQpJacobian()
{
	Real r(0);
	r = _property[_qp]._deltaH * _property[_qp]._dsource_dT * _test[_i][_qp] * _phi[_j][_qp];

   return r;
}
Real  PyrolysisSourceKernel::computeQpOffDiagJacobian(unsigned int jvar)
 {


	 if ( jvar == _property[_qp]._Rho_num  )
	    {
	 	  return( _property[_qp]._deltaH * _property[_qp]._dsource_dRho * _test[_i][_qp] * _phi[_j][_qp]);
	    }
	 else
	 {
		 return (0);
	 }
 }




