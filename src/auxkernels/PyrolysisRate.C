
#include "PyrolysisRate.h"


template<>
InputParameters validParams<PyrolysisRate>()
{
  InputParameters params = validParams<AuxKernel>();
  return params;
}

PyrolysisRate::PyrolysisRate(const InputParameters & parameters) :
    AuxKernel(parameters),
    _property(getMaterialProperty<PropertyPack>("property"))
{
}

Real
PyrolysisRate::computeValue()
{
  return -_property[_qp]._Source;
}
