

#include "PostprocessorFluxBC.h"


template<>
InputParameters validParams<PostprocessorFluxBC>()
{
	InputParameters params = validParams<IntegratedBC>();
     params.addRequiredParam<PostprocessorName>("postprocessor", "The postprocessor to set the value to on the boundary.");
	 return params;
}


PostprocessorFluxBC::PostprocessorFluxBC(const InputParameters & params) :
    IntegratedBC(params),
    _value(getPostprocessorValue("postprocessor"))
{
}

Real PostprocessorFluxBC::computeQpResidual()
{
  return -_test[_i][_qp]*_value;
}
