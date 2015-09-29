
#include "AuxKernel.h"
#include "PyrolysisMaterial.h"

class ShowK;

template<>
InputParameters validParams<ShowK>();

class ShowK : public AuxKernel
{
public:
	ShowK(const InputParameters & parameters);

    virtual ~ShowK() {}

protected:
  virtual Real computeValue();
  const MaterialProperty<PropertyPack> & _property;
};


