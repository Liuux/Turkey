#pragma once

#include "Kernel.h"
#include "PyrolysisMaterial.h"
class CoordMoveConvection : public Kernel
{
public:

	CoordMoveConvection(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);
private:
  MaterialProperty<PropertyPack> & _property;
};

template<>
InputParameters validParams<CoordMoveConvection>();
