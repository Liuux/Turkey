[Mesh]
  file = circle-quads.e
  uniform_refine = 2
[]
[MeshModifiers]
[./block_1]
  type = Transform
  transform = SCALE
  vector_value = '0.01 0.01 0.01'
[../]
[]
[Variables]
  [./disp_x]
  [../]
  [./disp_y]
  [../]
  [./disp_z]
  [../]
[]
[Kernels]
[./disp_x_td]
    type = DisplaceTimeDerivative
    variable = disp_x
    damp = 100000
    use_displaced_mesh = true
 [../]
 [./disp_y_td]
    type = DisplaceTimeDerivative
    variable = disp_y
    damp = 100000
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
  [./disp_y_1]
    type = SurfaceRecessionBC
    variable = disp_y
    boundary = 1
    component = y
  [../]
  [./disp_x_1]
    type = SurfaceRecessionBC
    variable = disp_x
    boundary = 1
    component = x
  [../]
[]

[Materials]
  [./bcmaterial]
   type = IntegratedBCMaterial
   flux = 600000
   boundary = 1
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




