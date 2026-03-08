project(
  'mesontest',
  'cpp',
  meson_version: '>= 1.3.0',
  version: '0.0.0',
  default_options: [
    'cpp_std=c++20',
    'buildtype=debug',
    'warning_level=3',
    'optimization=plain',
  ],
)

# -------------------------
# Include directories
# -------------------------
incdir = include_directories(
  'Dependencies/include',
  'Engine/tools',
  'Engine/vulkanaid/include',
  'Engine/render_engine/include',
  'Engine/shader_compiler/include',
)

# -------------------------
# Python3 for scripts
# -------------------------
py3 = find_program('python3', required: true)

# -------------------------
# Compiler-specific flags
# -------------------------
compiler_args = []
cpp = meson.get_compiler('cpp')
if cpp.get_id() == 'msvc'
  compiler_args += ['/Oi', '/wd4100', '/wd4189']
elif cpp.get_id() in ['clang', 'gcc']
  compiler_args += ['-march=native', '-Wno-unused-parameter']
endif
add_project_arguments(compiler_args, language: 'cpp')

# -------------------------
# Dependencies
# -------------------------
if host_machine.system() == 'windows'
  glfw_dep = declare_dependency(
    include_directories: incdir,
    link_args: [meson.project_source_root() / 'Dependencies/lib/glfw3_mt.lib'],
  )
  vulkan_dep = declare_dependency(
    include_directories: incdir,
    link_args: [meson.project_source_root() / 'Dependencies/lib/vulkan-1.lib'],
  )
  slang_dep = declare_dependency(
    include_directories: incdir,
    link_args: [],  # Windows Slang linking handled separately
  )
elif cpp.get_id() == 'gcc'
  glfw_dep = dependency('glfw3', required: true, static: false)
  vulkan_dep = dependency('vulkan', required: true, static: false)

  slang_lib_dir = meson.project_source_root() / 'Dependencies/lib/slang/lix/gcc'
  slang_dep = declare_dependency(
    include_directories: incdir,
    link_args: [
      '-L' + slang_lib_dir,
      '-lslang-rt',
      '-lslang-compiler',
      '-lgfx',
      '-lcompiler-core',
      '-lcore',
      '-llz4',
      '-lminiz',
      '-lslang-cpp-parser',
    ]
  )
elif cpp.get_id() == 'clang'
  glfw_dep = dependency('glfw3', required: true, static: false)
  vulkan_dep = dependency('vulkan', required: true, static: false)

  slang_lib_dir = meson.project_source_root() / 'Dependencies/lib/slang/lix/clang'
  slang_dep = declare_dependency(
    include_directories: incdir,
    link_args: [
      '-L' + slang_lib_dir,
      '-lslang-rt',
      '-lslang-compiler',
      '-lgfx',
      '-lcompiler-core',
      '-lcore',
      '-llz4',
      '-lminiz',
      '-lslang-cpp-parser',
    ]
  )
endif

dependencies = [glfw_dep, vulkan_dep, slang_dep]

# -------------------------
# Gather source files via Python
# -------------------------
sources_cmd = run_command(
  py3,
  [meson.project_source_root() / 'build_helper/harvest_sources.py'],
  check: true,
)
sources = sources_cmd.stdout().strip().split(' ')


# -------------------------
# Executable target
# -------------------------
exe = executable(
  'RED-RAiiN',
  sources,
  include_directories: incdir,
  dependencies: dependencies,
  install: true,
)

# -------------------------
# Basic test target
# -------------------------
test('test', exe)