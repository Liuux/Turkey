[Mesh]
  type = GeneratedMesh
  dim = 2
  xmin = 0
  ymin = 0
  xmax = 0.018
  ymax = 0.018
  nx = 30
  ny = 30
  elem_type = QUAD4
  displacements = 'disp_x disp_y'
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
  [./CoordMoveConvection]
    type = CoordMoveConvection
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
    damp = 1000000 
    use_displaced_mesh = true
 [../]
 [./disp_y_td]
    type = DisplaceTimeDerivative
    variable = disp_y
    damp = 1000000 
    use_displaced_mesh = true
 [../]
 [./disp_x_diff]
    type = Diffusion
    variable = disp_x
    use_displaced_mesh = true
  [../]
  [./disp_y_diff]
    type = Diffusion
    variable = disp_y
    use_displaced_mesh = true
  [../]
  [./disp_z_td]
    type = TimeDerivative
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
    value = 0
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
    value = 100000
  [../]
 [./bottom]
    type = HeatFluxBC
    variable = temperature
    boundary = bottom
    value = 0
  [../]
 [./pressureleft]
    type = HeatFluxBC
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

  [./disp_x_top]
    type = HeatFluxBC
    variable = disp_x
    boundary = top 
    value = 0
  [../]
  [./disp_y_top]
    type = SurfaceRecessionBC
    variable = disp_y
    boundary = top
    component = y
  [../]
  [./disp_x_left]
    type = SurfaceRecessionBC
    variable = disp_x
    boundary = left
    component = x
  [../]
  [./disp_y_left]
    type = HeatFluxBC
    variable = disp_y
    boundary = left
    value = 0
  [../]
  [./disp_x_right]
    type = HeatFluxBC
    variable = disp_x
    boundary = right
    value = 0
  [../]
  [./disp_y_right]
    type = HeatFluxBC
    variable = disp_y
    boundary = right
    value = 0
  [../]
  [./disp_x_bottom]
    type = HeatFluxBC
    variable = disp_x
    boundary = bottom
    value = 0
  [../]
  [./disp_y_bottom]
    type = DirichletBC
    variable = disp_y
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
    disp_x = disp_x
    disp_y = disp_y
    disp_z = disp_z
  [../]
  [./bcmaterial]
   type = IntegratedBCMaterial
   flux = 0.01
   boundary = 'top bottom left right'
  [../]
[]

[Executioner]
  type = Transient
  solve_type = newton
  scheme = bdf2
  dt = 1E-02
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

