[Mesh]
  type = GeneratedMesh
  dim = 2
   dim = 2
  xmin = 0
  ymin = 0
  xmax = 0.0362
  ymax = 0.0362
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
 [./density]
    type = DensitySourceKernel
    variable = rho
  [../]
[]

[BCs]
  [./left]
    type = HeatFluxBC
    variable = temperature
    boundary = left
    value = 100000
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
    value = 0
  [../]
 [./bottom]
    type = HeatFluxBC
    variable = temperature
    boundary = bottom
    value = 0
  [../]
[]

[Materials]
  [./material]
    type = PyrolysisMaterial
    temperature = temperature
    rho = rho
    block = 0
    k = 0.75
    cp = 1256
    rhov = 1448
    rhoc = 1185
    cpg = 1
    rhog = 0
    deltaH = 1000
    precoff = 11000
    m = 2
    ER = 10000
    permeability = 0
    viscosity = 0 
    porosity = 0 
  [../]
[]

[Executioner]
  type = Transient
  solve_type = newton
  dt = 1E-01
  num_steps = 2000

  l_tol = 1e-04
  nl_rel_tol = 1e-05
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

