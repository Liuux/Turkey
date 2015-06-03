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
[]

[ICs]
  [./temp_ic]
    variable = temperature
    type = ConstantIC
    value = 300
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
[]

[BCs]
  [./left]
    type = HeatFluxBC
    variable = temperature
    boundary = left
    value = 10000
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
    block = 0
    k = 1.2
    cp = 500
    rho = 1440
    rhov = 1440
    rhoc = 1440
    cpg = 1
    rhog = 0
    deltaH = 1000
    precoff = 0
    m = 2
    ER = 0
    permeability = 0
    viscosity = 0 
    porosity = 0 
  [../]
[]

[Executioner]
  type = Transient
  solve_type = newton
  dt = 1E-02
  num_steps = 1000

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

