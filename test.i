[Mesh]
  type = GeneratedMesh
  dim = 2
  xmin = 0
  ymin = 0
  xmax = 0.018
  ymax = 0.018
  nx = 60
  ny = 60
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
 #[./gasconvection]
  #  type = GasConvection
  #  variable = temperature
 #[../]
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
    value = 10000
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
    value = 10000
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
    cp = 1256
    rhov = 1448
    rhoc = 1185
    cpg = 1
    rhog = 0.01
    deltaH = 100000
    precoff = 11000
    m = 2
    ER = 10000
    permeability = 8.968e-12
    viscosity = 1.98e-4
    porosity = 0.3 
  [../]
[]

[Executioner]
  type = Transient
  solve_type = newton
  scheme = bdf2
  dt = 1E-02
  num_steps = 2000

  l_tol = 1e-04
  nl_rel_tol = 1e-08
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

