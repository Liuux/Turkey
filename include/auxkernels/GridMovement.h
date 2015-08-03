
#include "AuxKernel.h"
#include "PyrolysisMaterial.h"
class GridMovement;

template<>
InputParameters validParams<GridMovement>();

class GridMovement : public AuxKernel
{
public:
	GridMovement(const std::string & name, InputParameters parameters);

    virtual ~GridMovement() {}

protected:
  virtual Real computeValue();
  int _component;
  const MaterialProperty<PropertyPack> & _property;
};


