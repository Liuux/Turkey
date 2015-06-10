
#include "PyrolysisRate.h"


template<>
InputParameters validParams<PyrolysisRate>()
{
  InputParameters params = validParams<AuxKernel>();
  return params;
}

PyrolysisRate::PyrolysisRate(const std::string & name, InputParameters parameters) :
    AuxKernel(name, parameters),
    _property(getMaterialProperty<PropertyPack>("property"))
{
}

Real
PyrolysisRate::computeValue()
{
  return -_property[_qp]._Source;
}
