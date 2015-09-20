/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#include "DisplayDiffusion.h"


template<>
InputParameters validParams<DisplayDiffusion>()
{
  InputParameters p = validParams<Kernel>();
  return p;
}


DisplayDiffusion::DisplayDiffusion(const InputParameters & parameters) :
    Kernel(parameters)
{

}

DisplayDiffusion::~DisplayDiffusion()
{

}

Real
DisplayDiffusion::computeQpResidual()
{
  return 80*_grad_u[_qp] * _grad_test[_i][_qp];
}

Real
DisplayDiffusion::computeQpJacobian()
{
  return 80*_grad_phi[_j][_qp] * _grad_test[_i][_qp];
}
