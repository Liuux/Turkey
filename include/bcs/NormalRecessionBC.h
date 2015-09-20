
#include "NodalBC.h"
#include "PyrolysisMaterial.h"

//Forward Declarations
class NormalRecessionBC;

template<>
InputParameters validParams<NormalRecessionBC>();

class NormalRecessionBC : public NodalBC
{
public:
	NormalRecessionBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
   int _component;
   VariableValue & _nx;
   VariableValue & _ny;
   VariableValue & _nz;
   VariableValue & _oldu;
   VariableValue & _T;
   VariableValue & _Rho;
   Real _startRho;
   Real _ablateCoff;


};

