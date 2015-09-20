#include "TurkeyApp.h"
#include "Moose.h"
#include "AppFactory.h"
//#include "ModulesApp.h"
#include "HeatConductionKernel.h"
#include "TemperatureTimeDerivative.h"
#include "DensitySourceKernel.h"
#include "PyrolysisSourceKernel.h"
#include "DarcyPressure.h"
#include "GasConvection.h"
#include "CoordMoveConvection.h"
#include "DisplaceTimeDerivative.h"
#include"DisplayDiffusion.h"

#include "PyrolysisMaterial.h"
#include "IntegratedBCMaterial.h"
#include "HeatFluxMaterial.h"
#include "GiveHeatFluxMaterial.h"


#include "IsoThermalBC.h"
#include "HeatFluxBC.h"
#include "HeatTransferBC.h"
#include "PostprocessorFluxBC.h"
#include "SurfaceRecessionBC.h"
#include "HeatRadiationBC.h"
#include "NormalRecessionBC.h"

#include "PyrolysisGasVelocity.h"
#include "PyrolysisRate.h"
#include "GridMovement.h"
#include "HeatFluxAuxKernel.h"




template<>
InputParameters validParams<TurkeyApp>()
{
  InputParameters params = validParams<MooseApp>();

  params.set<bool>("use_legacy_uo_initialization") = false;
  params.set<bool>("use_legacy_uo_aux_computation") = false;
  return params;
}

TurkeyApp::TurkeyApp(InputParameters parameters) :
    MooseApp(parameters)
{
  srand(processor_id());

  Moose::registerObjects(_factory);
//  ModulesApp::registerObjects(_factory);
  TurkeyApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
//  ModulesApp::associateSyntax(_syntax, _action_factory);
  TurkeyApp::associateSyntax(_syntax, _action_factory);
}

TurkeyApp::~TurkeyApp()
{
}

// External entry point for dynamic application loading
extern "C" void TurkeyApp__registerApps() { TurkeyApp::registerApps(); }
void
TurkeyApp::registerApps()
{
  registerApp(TurkeyApp);
}

// External entry point for dynamic object registration
extern "C" void TurkeyApp__registerObjects(Factory & factory) { TurkeyApp::registerObjects(factory); }
void
TurkeyApp::registerObjects(Factory & factory)
{
	registerKernel(TemperatureTimeDerivative);
	registerKernel(HeatConductionKernel);
	registerKernel(DensitySourceKernel);
	registerKernel(PyrolysisSourceKernel);
	registerKernel(DarcyPressure);
	registerKernel(GasConvection);
	registerKernel(CoordMoveConvection);
	registerKernel(DisplaceTimeDerivative);
	registerKernel(DisplayDiffusion);

	registerMaterial(PyrolysisMaterial);
	registerMaterial(IntegratedBCMaterial);
	registerMaterial(HeatFluxMaterial);
	registerMaterial(GiveHeatFluxMaterial);

	registerBoundaryCondition(IsoThermalBC);
    registerBoundaryCondition(HeatFluxBC);
	registerBoundaryCondition(HeatTransferBC);
	registerBoundaryCondition(PostprocessorFluxBC);
	registerBoundaryCondition(SurfaceRecessionBC);
	registerBoundaryCondition(HeatRadiationBC);
	registerBoundaryCondition(NormalRecessionBC);

	registerAux(PyrolysisGasVelocity);
	registerAux(PyrolysisRate);
	registerAux(GridMovement);
	registerAux(HeatFluxAuxKernel);


}


// External entry point for dynamic syntax association
extern "C" void TurkeyApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory) { TurkeyApp::associateSyntax(syntax, action_factory); }
void
TurkeyApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
}
