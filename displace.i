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
  [./disp_x]
  [../]
  [./disp_y]
  [../]
  [./disp_z]
  [../]
[]

[ICs]
[]

[Kernels]
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

[BCs]
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
    type = HeatFluxBC
    variable = disp_x
    boundary = left
    value = 0
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
    type = DirichletBC
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

