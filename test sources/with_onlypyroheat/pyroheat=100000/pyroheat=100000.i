
[Mesh]
  type = GeneratedMesh
  dim = 1
  xmin = 0 
  xmax = 0.04
  nx = 400
  displacements = 'disp_x'
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
  [./disp_x]
  [../]
  [./disp_y]
  [../]
  [./disp_z]
  [../]
[]
[NodalNormals]
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
  [./flux]
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
    value = 700
  [../]
  [./pressure_ic]
    variable = pressure
    type = ConstantIC
    value = 1000000
  [../]
[]

[Kernels]
  [./temporal]
    type = TemperatureTimeDerivative
    variable = temperature
    use_displaced_mesh = true
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

[./disp_x_td]
    type = DisplaceTimeDerivative
    variable = disp_x
    damp = 80000000
    use_displaced_mesh = true
 [../]
 [./disp_y_td]
    type = DisplaceTimeDerivative
    variable = disp_y
    damp = 80000000
    use_displaced_mesh = true
 [../]
 [./disp_z_td]
    type = DisplaceTimeDerivative
    variable = disp_z
    damp = 80000000
    use_displaced_mesh = true
 [../]
 [./disp_x_diff]
    type = DisplayDiffusion
    variable = disp_x
    use_displaced_mesh = true
  [../]
  [./disp_y_diff]
    type = DisplayDiffusion
    variable = disp_y
    use_displaced_mesh = true
  [../]
  [./disp_z_diff]
    type = DisplayDiffusion
    variable = disp_z
    use_displaced_mesh = true
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
  [./gasvelocity_z]
    type = PyrolysisGasVelocity
    variable = GasVelocity_z
    component = z
  [../]
  [./PyrolysisRate]
    type = PyrolysisRate
    variable = Rho_dt
  [../]
  [./showflux]
    type = HeatFluxAuxKernel
    variable = flux
    boundary = left
  [../]
[]

[BCs]
  [./right]
    type = HeatRadiationBC
    boundary = right
    variable = temperature
  [../]
  [./left]
    type = HeatFluxBC
    boundary = left
    value = 0
    variable = temperature
  [../]
  [./pressureright]
    type = DirichletBC
    variable = pressure
    boundary = right
    value = 1000000
  [../]
  [./pressureleft]
    type = HeatFluxBC
    variable = pressure
    boundary = left
    value = 0
  [../]
  [./disp_x_right]
    type = NormalRecessionBC
    variable = disp_x
    variableold = disp_x
    temperature = temperature
    boundary = right
    ablatecoff = 36000000
    component = x
    rho = rho
    startRho = 600
  [../]
  [./disp_y_right]
    type = NormalRecessionBC
    variable = disp_y
    variableold = disp_y
    temperature = temperature
    boundary = right
    ablatecoff = 36000000
    component = y
    rho = rho
    startRho = 600
  [../]
  [./disp_z_right]
    type = NormalRecessionBC
    variable = disp_z
    variableold = disp_z
    temperature = temperature
    boundary = right
    ablatecoff = 36000000
    component = z
    rho = rho
    startRho = 600
  [../]
  [./disp_x_left]
    type = DirichletBC
    variable = disp_y
    boundary = left
    value = 0
  [../]
  [./disp_y_left]
    type = DirichletBC
    variable = disp_x
    boundary = left
    value = 0
  [../]
  [./disp_z_left]
    type = DirichletBC
    variable = disp_z
    boundary = left
    value = 0
  [../]
[]

[Materials]
  [./materialfg7]
    type = PyrolysisMaterial
    temperature = temperature
    rho = rho
    pressure = pressure
    block = ANY_BLOCK_ID
    sigma = 0.85
    kv = 0.15
    kc = 0.45
    cpv = 1480
    cpc = 1650
    rhov = 700
    rhoc = 470
    cpg = 0
    rhog = 100
    deltaH = 100000
    precoff = 15000
    m = 2
    ER = 7000
    permeability = '8.9e-9 0 0 
                    0 8.9e-9 0
                    0 0 8.9e-9'
    viscosity = 1.98e-5
    porosity = 0.3 
    disp_x = disp_x
    disp_y = disp_y
    disp_z = disp_z
  [../]
  [./materialbc]
    type = GiveHeatFluxMaterial
    boundary = right
    temperature = temperature
    epsilon = 5.67e-08
    tw0 = 300
    ts = 18000
    qc = 2000000
  [../]
[]

[Executioner]
  type = Transient
  solve_type = PJFNK
  scheme = bdf2
  dt = 0.1
  num_steps = 50000
  start_time = 0

  l_tol = 1e-04
  nl_rel_tol = 1e-06
  l_max_its = 12
  nl_max_its = 12
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
  [./exodus1]
    type = Exodus
    #refinements = 1
    output_on = 'initial timestep_end'
  [../]
  [./tecplot]
    type = Tecplot
    sync_times = '20.003 40.01 60.01 80.001 100.0013 120.001 140.0013 160.005 180.0012 200.00131'
    sync_only = true
    use_displaced = true
  [../]
  [./console]
    type = Console
    perf_log = true
    output_on = 'timestep_end failed nonlinear linear'
  [../]
  
[]



