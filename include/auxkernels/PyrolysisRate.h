
#include "AuxKernel.h"
#include "PyrolysisMaterial.h"

class PyrolysisRate;

template<>
InputParameters validParams<PyrolysisRate>();

class PyrolysisRate : public AuxKernel
{
public:
	PyrolysisRate(const std::string & name, InputParameters parameters);

    virtual ~PyrolysisRate() {}

protected:
  virtual Real computeValue();
  const MaterialProperty<PropertyPack> & _property;
};


