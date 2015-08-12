
#include "AuxKernel.h"
#include "PyrolysisMaterial.h"

class PyrolysisGasVelocity;

template<>
InputParameters validParams<PyrolysisGasVelocity>();

class PyrolysisGasVelocity : public AuxKernel
{
public:
	PyrolysisGasVelocity(const InputParameters & parameters);

    virtual ~PyrolysisGasVelocity() {}

protected:
  virtual Real computeValue();
  int _component;
  const MaterialProperty<PropertyPack> & _property;
};


