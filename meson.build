project(
  'mesontest',
  'cpp',
  meson_version   : '>= 1.4.0',
  version         : '0.0.0',
  default_options : [
    'cpp_std=c++20',
    'buildtype=release',
    'warning_level=3',
    'optimization=plain',
  ],
)

# -------------------------
# Compiler setup
# -------------------------
cpp = meson.get_compiler('cpp')

compiler_args = []
if cpp.get_id() == 'msvc'
  compiler_args += ['/Oi', '/wd4100', '/wd4189']
elif cpp.get_id() in ['clang', 'gcc']
  compiler_args += ['-march=native', '-Wno-unused-parameter']
endif
add_project_arguments(compiler_args, language: 'cpp')

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
# Build Slang via CMake externally
# (avoids Meson choking on SPIRV-Tools cyclic targets)
# -------------------------
cmake_prog = find_program('cmake', required: true)

slang_source_dir = meson.project_source_root() / 'subprojects/slang'
slang_build_dir  = meson.project_build_root()  / 'subprojects/slang-build'

# Configure
run_command(
  cmake_prog,
  '-S', slang_source_dir,
  '-B', slang_build_dir,
  '-DCMAKE_BUILD_TYPE=Release',
  '-DSLANG_LIB_TYPE=STATIC',
  '-DSLANG_ENABLE_TESTS=OFF',
  '-DSLANG_ENABLE_EXAMPLES=OFF',
  '-DSLANG_ENABLE_GFX=OFF',
  '-DSLANG_ENABLE_SLANGD=OFF',
  '-DSLANG_ENABLE_SLANGRT=OFF',
  check: true,
)

# Build
run_command(
  cmake_prog,
  '--build', slang_build_dir,
  '--config', 'Release',
  '--parallel',
  check: true,
)

# -------------------------
# Slang dependency
# Point link_args at the .a files produced by the CMake build above.
# Run: find <slang_build_dir> -name "*.a" to verify these paths on
# your machine after a first manual cmake build.
# -------------------------
slang_dep = declare_dependency(
  include_directories : include_directories('subprojects/slang/include'),
  link_args           : [
    slang_build_dir / 'libslang.a',
  ],
)

# -------------------------
# Platform dependencies (GLFW + Vulkan)
# -------------------------
if host_machine.system() == 'windows'
  glfw_dep = declare_dependency(
    include_directories : incdir,
    link_args           : [
      meson.project_source_root() / 'Dependencies/lib/glfw3_mt.lib',
    ],
  )
  vulkan_dep = declare_dependency(
    include_directories : incdir,
    link_args           : [
      meson.project_source_root() / 'Dependencies/lib/vulkan-1.lib',
    ],
  )
elif cpp.get_id() in ['gcc', 'clang']
  glfw_dep   = dependency('glfw3',  required: true, static: false)
  vulkan_dep = dependency('vulkan', required: true, static: false)
endif

all_deps = [glfw_dep, vulkan_dep, slang_dep]

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
# Copy shader assets to build dir
# -------------------------
copy_shaders = custom_target(
  'copy_shaders',
  output  : 'shader_copy_stamp',
  command : [
    py3,
    meson.project_source_root() / 'build_helper/add_shader_sources_to_builddir.py',
    meson.current_build_dir(),
  ],
  build_by_default: true,
)

# -------------------------
# Executable
# -------------------------
exe = executable(
  'RED-RAiiN',
  sources,
  include_directories : incdir,
  dependencies        : all_deps,
  install             : true,
)

# -------------------------
# Tests
# -------------------------
test('test', exe)