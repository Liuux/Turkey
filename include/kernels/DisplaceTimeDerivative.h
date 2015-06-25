


#include "TimeKernel.h"

class DisplaceTimeDerivative;

template<>
InputParameters validParams<DisplaceTimeDerivative>();

class DisplaceTimeDerivative : public TimeKernel
{
public:
	DisplaceTimeDerivative(const std::string & name, InputParameters parameters);

  virtual void computeJacobian();

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  bool _lumping;
  Real _damp;
};

