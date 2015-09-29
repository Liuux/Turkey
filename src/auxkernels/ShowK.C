
#include "ShowK.h"


template<>
InputParameters validParams<ShowK>()
{
  InputParameters params = validParams<AuxKernel>();
  return params;
}

ShowK::ShowK(const InputParameters & parameters) :
    AuxKernel(parameters),
    _property(getMaterialProperty<PropertyPack>("property"))
{
}

Real
ShowK::computeValue()
{
  return -_property[_qp]._k;
}
