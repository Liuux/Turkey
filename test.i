[Mesh]
  type = circle-quads.e
  dim = 2
  xmin = 0
  ymin = 0
  xmax = 0.009
  ymax = 0.009
  nx = 30
  ny = 30
[]

[Variables]
  [./temperature]
    family = LAGRANGE
    order = FIRST
  [../]
[./rho]
    family = LAGRANGE
    order = FIRST
  [../]
[./pressure]
    family = LAGRANGE
    order = FIRST
  [../]
[]

[AuxVariables]
 
  [./GasVelocity_x]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./GasVelocity_y]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./GasVelocity_z]
    order = CONSTANT
    family = MONOMIAL
  [../]
  [./Rho_dt]
    order = CONSTANT
    family = MONOMIAL
  [../]

[]

[ICs]
  [./temp_ic]
    variable = temperature
    type = ConstantIC
    value = 300
  [../]
[./rho_ic]
    variable = rho
    type = ConstantIC
    value = 1448
  [../]
[./pressure_ic]
    variable = pressure
    type = ConstantIC
    value = 0
  [../]
[]

[Kernels]
  [./temporal]
    type = TemperatureTimeDerivative
    variable = temperature
  [../]
  [./diff]
    type = HeatConductionKernel
    variable = temperature
  [../]
  [./pyrolysisource]
    type = PyrolysisSourceKernel
    variable = temperature
  [../]
  [./gasconvection]
    type = GasConvection
    variable = temperature
  [../]
  [./density]
    type = DensitySourceKernel
    variable = rho
  [../]
[./darcypressure]
    type = DarcyPressure
    variable = pressure
  [../]
[]
[AuxKernels]
 
  [./gasvelocity_x]
    type = PyrolysisGasVelocity
    variable = GasVelocity_x
    component = x    
  [../]
  [./gasvelocity_y]
    type = PyrolysisGasVelocity
    variable = GasVelocity_y
    component = y
  [../]
 [./PyrolysisRate]
    type = PyrolysisRate
    variable = Rho_dt
  [../]
[]

[BCs]
  [./left]
    type = HeatFluxBC
    variable = temperature
    boundary = left
    value = 200000
  [../]
  [./right]
    type = HeatFluxBC
    variable = temperature
    boundary = right
    value = 0
  [../]
  [./top]
    type = HeatFluxBC
    variable = temperature
    boundary = top
    value = 200000
  [../]
 [./bottom]
    type = HeatFluxBC
    variable = temperature
    boundary = bottom
    value = 0
  [../]
 [./pressureleft]
    type = DirichletBC
    variable = pressure
    boundary = left
    value = 0
  [../]
  [./pressureright]
    type = HeatFluxBC
    variable = pressure
    boundary = right
    value = 0
  [../]
  [./pressuretop]
    type = DirichletBC
    variable = pressure
    boundary = top
    value = 0
  [../]
 [./pressurebottom]
    type = HeatFluxBC
    variable = pressure
    boundary = bottom
    value = 0
  [../]
[]

[Materials]
  [./material]
    type = PyrolysisMaterial
    temperature = temperature
    rho = rho
    pressure = pressure
    block = 0
    k = 0.75
    cp = 556
    rhov = 1448
    rhoc = 1000
    cpg = 100
    rhog = 10
    deltaH = 100000
    precoff = 11000
    m = 2
    ER = 10000
    permeability = '8.9e-9 0 0 
                    0 8.9e-9 0
                    0 0 0'
    viscosity = 1.98e-5
    porosity = 0.3 
  [../]
[]

[Executioner]
  type = Transient
  solve_type = newton
  scheme = bdf2
  dt = 1E-01
  num_steps = 5000

  l_tol = 1e-04
  nl_rel_tol = 1e-06
  l_max_its = 10
  nl_max_its = 10
  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Postprocessors]
  [./run_time]
    type = RunTime
    time_type = active
  [../]
[Postprocessors]
  [./integral]
    type = ElementIntegralVariablePostprocessor
    variable = Rho_dt
  [../]
 [./left]
    type = AreaPostprocessor
    boundary = left
  [../]

[]
[]
[Outputs]
  [./exodus]
    type = Exodus
    #refinements = 1
    output_on = 'initial timestep_end'
  [../]
  [./console]
    type = Console
    perf_log = true
    output_on = 'timestep_end failed nonlinear linear'
  [../]
[]

