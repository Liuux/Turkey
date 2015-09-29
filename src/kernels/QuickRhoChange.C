#include "QuickRhoChange.h"

template<>
InputParameters validParams<QuickRhoChange>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription(" rho changes with T");
  return params;
}

QuickRhoChange::QuickRhoChange(const InputParameters & parameters) :
     Kernel(parameters),
	 _property(getMaterialProperty<PropertyPack>("property"))
{
}


Real QuickRhoChange::Source(Real T,Real rhoc,Real rhov)
{
	if (T>600)
	{
		return rhoc;
	}
	else
	{
		return rhov;
	}
}
 Real QuickRhoChange::computeQpResidual()
{
  return  _u[_qp]*_test[_i][_qp]-Source(_property[_qp]._T,_property[_qp]._rhoc,_property[_qp]._rhov) *_test[_i][_qp];
}

Real QuickRhoChange::computeQpJacobian()
{
    return  _test[_i][_qp]*_phi[_j][_qp];
}

 Real  QuickRhoChange::computeQpOffDiagJacobian(unsigned int jvar)
 {
		 return (0);
 }






