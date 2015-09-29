#pragma once

#include "Kernel.h"
#include "PyrolysisMaterial.h"
class QuickRhoChange : public Kernel
{
public:

	QuickRhoChange(const InputParameters & parameters);
protected:
  Real Source(Real T,Real rhoc,Real rhov);
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

private:
   const MaterialProperty<PropertyPack> & _property;

};

template<>
InputParameters validParams<QuickRhoChange>();
