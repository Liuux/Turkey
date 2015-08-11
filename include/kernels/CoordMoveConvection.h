#pragma once

#include "Kernel.h"
#include "PyrolysisMaterial.h"
class CoordMoveConvection : public Kernel
{
public:

	CoordMoveConvection(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);
private:
  const MaterialProperty<PropertyPack> & _property;
};

template<>
InputParameters validParams<CoordMoveConvection>();
