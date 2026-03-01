project(
  'mesontest',
  'cpp',
  meson_version: '>= 1.3.0',
  version: '0.1',
  default_options: [
    'cpp_std=c++20',
    'buildtype=release',
    'warning_level=3',
  ],
)

# Include dirs
incdir = include_directories(
  'Dependencies/include',
  'Engine/tools',
  'Engine/engine/vulkanaid/include',
  'Engine/engine/render_engine/include',
)

# find python3 program
py3 = find_program('python3', required: true)

# Platform-specific compiler args
compiler_args = []
cpp = meson.get_compiler('cpp')

if cpp.get_id() == 'msvc'
  compiler_args += ['/Oi', '/Ot', '/wd4100', '/wd4189']
elif cpp.get_id() == 'clang'
  compiler_args += ['-march=native', '-O3', '-Wno-unused-parameter']
else
  # GCC
  compiler_args += ['-march=native', '-O3', '-Wno-unused-parameter']
endif

add_project_arguments(compiler_args, language: 'cpp')


# Dependencies
if host_machine.system() == 'windows'
  glfw_dep = declare_dependency(
    include_directories: incdir,
    link_args: [meson.project_source_root() / 'Dependencies/lib/glfw3_mt.lib'],
  )
  vulkan_dep = declare_dependency(
    include_directories: incdir,
    link_args: [meson.project_source_root() / 'Dependencies/lib/vulkan-1.lib'],
  )
else
  # On Linux, use pkg-config to find glfw3 and Vulkan
  glfw_dep = dependency('glfw3', required: true)
  vulkan_dep = dependency('vulkan', required: true)
endif
dependencies = [glfw_dep, vulkan_dep]


# Run Python script and get sources
sources_cmd = run_command(
  py3,
  [meson.project_source_root() / 'build_helper/harvest_sources.py']
)
sources = sources_cmd.stdout().strip().split(' ')

# Executable
exe = executable(
  'RED-RAiiN',
  sources,
  include_directories: incdir,
  dependencies: dependencies,
  install: true,
)

test('test', exe)
