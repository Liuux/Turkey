
#pragma once

#include "IntegratedBC.h"

class PostprocessorFluxBC : public IntegratedBC
{
public:
	PostprocessorFluxBC(const std::string & name, InputParameters parameters);
protected:
	virtual Real computeQpResidual();
	const Real & _value;
};

template<>
InputParameters validParams<PostprocessorFluxBC>();
