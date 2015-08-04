[Mesh]
  type = GeneratedMesh
  dim = 3
  xmin = -0.005
  xmax =  0.005
  ymin = -0.005
  ymax =  0.005
  zmin = -0.005
  zmax =  0.005
  nx = 20
  ny = 20
  nz = 20
 displacements = 'disp_x disp_y disp_z'
[]
[MeshModifiers]
[./block_1]
  type = Transform
  transform = SCALE
  vector_value = '1 1 1'
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
    damp = 4000000
    use_displaced_mesh = true
 [../]
 [./disp_y_td]
    type = DisplaceTimeDerivative
    variable = disp_y
    damp = 4000000
    use_displaced_mesh = true
 [../]
 [./disp_z_td]
    type = DisplaceTimeDerivative
    variable = disp_z
    damp = 4000000
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
[BCs]
  [./disp_y]
    type = SurfaceRecessionBC
    variable = disp_y
    boundary = 'top bottom left right front back'
    component = y
  [../]
  [./disp_x]
    type = SurfaceRecessionBC
    variable = disp_x
    boundary = 'top bottom left right front back'
    component = x
  [../]
  [./disp_z]
    type = SurfaceRecessionBC
    variable = disp_z
    boundary = 'top bottom left right front back'
    component = z
  [../]
[]

[Materials]
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
   flux = 0
   boundary = 'bottom right front back'
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
  l_max_its = 8
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




