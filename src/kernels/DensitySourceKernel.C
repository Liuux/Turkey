#include "DensitySourceKernel.h"

template<>
InputParameters validParams<DensitySourceKernel>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription(" rho changes with T");
  return params;
}

DensitySourceKernel::DensitySourceKernel(const InputParameters & parameters) :
     Kernel(parameters),
	 _property(getMaterialProperty<PropertyPack>("property"))
{
}


Real DensitySourceKernel::Source(Real rho,Real T,Real rhoc,Real rhov,Real precoff, Real ER,Real m)
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
 Real DensitySourceKernel::computeQpResidual()
{
  return  _u_dot[_qp]*_test[_i][_qp]+Source(_property[_qp]._Rho,_property[_qp]._T,_property[_qp]._rhoc,_property[_qp]._rhov,_property[_qp]._precoff,_property[_qp]._ER,_property[_qp]._m) *_test[_i][_qp];
}

Real DensitySourceKernel::computeQpJacobian()
{
	Real epsi = 1E-08;
	Real source = Source(_property[_qp]._Rho,_property[_qp]._T,_property[_qp]._rhoc,_property[_qp]._rhov,_property[_qp]._precoff,_property[_qp]._ER,_property[_qp]._m);
	Real source_new = Source(_property[_qp]._Rho+epsi,_property[_qp]._T,_property[_qp]._rhoc,_property[_qp]._rhov,_property[_qp]._precoff,_property[_qp]._ER,_property[_qp]._m);
    return  _test[_i][_qp]*_phi[_j][_qp]*_du_dot_du[_qp]+(source_new-source)/epsi*_phi[_j][_qp]*_test[_i][_qp];
}

 Real  DensitySourceKernel::computeQpOffDiagJacobian(unsigned int jvar)
 {


	 if ( jvar == _property[_qp]._T_num)
	    {
		 Real epsi = 1E-08;
	     Real source = Source(_property[_qp]._Rho,_property[_qp]._T,_property[_qp]._rhoc,_property[_qp]._rhov,_property[_qp]._precoff,_property[_qp]._ER,_property[_qp]._m);
	 	 Real source_new =  Source(_property[_qp]._Rho,_property[_qp]._T,_property[_qp]._rhoc,_property[_qp]._rhov,_property[_qp]._precoff,_property[_qp]._ER,_property[_qp]._m);
	    return (source_new-source)/epsi*_phi[_j][_qp]*_test[_i][_qp];
	    }
 else
	 {
		 return (0);
	 }
 }






