[Mesh]
  type = GeneratedMesh
  dim = 3
  xmin = -0.005
  xmax =  0.005
  ymin = -0.005
  ymax =  0.005
  zmin = -0.005
  zmax =  0.005
  nx = 15
  ny = 15
  nz = 15
  displacements = 'disp_x disp_y disp_z'
  elem_type = HEX
[]
[MeshModifiers]
[./block_1]
  type = Transform
  transform = SCALE
  vector_value = '1 1 1'
[../]
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
    damp = 50000000
    use_displaced_mesh = true
 [../]
 [./disp_y_td]
    type = DisplaceTimeDerivative
    variable = disp_y
    damp = 50000000
    use_displaced_mesh = true
 [../]
 [./disp_z_td]
    type = DisplaceTimeDerivative
    variable = disp_z
    damp = 50000000
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
  [./disp_z_diff]
    type = Diffusion
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
    type = HeatRadiationBC
    variable = temperature
    boundary = top
    epsilon = 1e-8
    tw0 = 300
    scale = '1 1 1'
    flux_data = qc.dat
    fluxcoff = 1
  [../]
  [./bottom]
    type = HeatFluxBC
    variable = temperature
    boundary = bottom
    value = 0
  [../]
  [./front]
    type = HeatFluxBC
    variable = temperature
    boundary = front
    value = 0
  [../]
  [./back]
    type = HeatFluxBC
    variable = temperature
    boundary = back
    value = 0
  [../]
  [./pressureleft]
    type = DirichletBC
    variable = pressure
    boundary = left
    value = 1000000
  [../]
  [./pressureright]
    type = DirichletBC
    variable = pressure
    boundary = right
    value = 1000000
  [../]
  [./pressuretop]
    type = DirichletBC
    variable = pressure
    boundary = top
    value = 1000000
  [../]
  [./pressurebottom]
    type = DirichletBC
    variable = pressure
    boundary = bottom
    value = 1000000
  [../]
  [./pressurefront]
    type = DirichletBC
    variable = pressure
    boundary = front
    value = 1000000
  [../]
  [./pressureback]
    type = DirichletBC
    variable = pressure
    boundary = back
    value = 1000000
  [../]
  [./disp_y_top]
    type = SurfaceRecessionBC
    variable = disp_y
    boundary = 'top bottom left right front back'
    component = y
  [../]
  [./disp_x_top]
    type = SurfaceRecessionBC
    variable = disp_x
    boundary = 'top bottom left right front back'
    component = x
  [../]
  [./disp_z_top]
    type = SurfaceRecessionBC
    variable = disp_z
    boundary = 'top bottom left right front back'
    component = z
  [../]
[]

[Materials]
  [./material]
    type = PyrolysisMaterial
    temperature = temperature
    rho = rho
    pressure = pressure
    block = ANY_BLOCK_ID
    sigma = 0.4
    kv = 0.75
    kc = 1.5
    cpv = 556
    cpc = 800
    rhov = 1448
    rhoc = 1185
    cpg = 100
    rhog = 10
    deltaH = 100000
    precoff = 11000
    m = 2
    ER = 10000
    permeability = '8.9e-9 0 0 
                    0 8.9e-9 0
                    0 0 8.9e-9'
    viscosity = 1.98e-5
    porosity = 0.3 
    disp_x = disp_x
    disp_y = disp_y
    disp_z = disp_z
  [../]
  [./bcmaterial1]
   type = IntegratedBCMaterial
   flux = 100000
   boundary = top
  [../]
  [./bcmaterial2]
   type = IntegratedBCMaterial
   flux = 100000
   boundary = left
  [../]
  [./bcmaterial3]
   type = IntegratedBCMaterial
   flux = 100000
   boundary = front
  [../]
  [./bcmaterial4]
   type = IntegratedBCMaterial
   flux = 0
   boundary = 'bottom right back'
  [../]
  [./heat_flux]
    type = HeatFluxMaterial
    temperature = temperature
    boundary = top
    epsilon = 1e-8
    tw0 = 300
    scale = '1 1 1'
    flux_data = qc.dat
    fluxcoff = 1 
  [../]

[]

[Executioner]
  type = Transient
  solve_type = newton
  scheme = bdf2
  dt = 0.1
  num_steps = 5000

  l_tol = 1e-04
  nl_rel_tol = 1e-04
  l_max_its = 12
  nl_max_its = 8
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




