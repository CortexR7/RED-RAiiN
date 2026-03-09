
#
#  This is a python script that shall get executed by meson
#  For more information, look ate the meson.build file
#
#
#  Copyright (c) 2026 CortexR7
#  
#  This build.py file is part of the build system
#  for the RED-RAiiN project. And any modification 
#  may result in build failure. Please refer to the meson.build
#  This script asumes cmake and ninja is preinstalled on the host system 
#


from pathlib import Path
import shutil
import subprocess
import platform

subproject_slang_path = "../subprojects/slang"
path = subproject_slang_path   # folder where CMakeLists.txt is
cmd_win = [
    "cmake",
    "-B", "build",
    "-G", "Ninja",
    "-DCMAKE_BUILD_TYPE=Release",
    "-DSLANG_ENABLE_TESTS=OFF",
    "-DSLANG_ENABLE_EXAMPLES=OFF",
    "-DSLANG_LIB_TYPE=STATIC",
    "-DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded"
]

cmd_lin = [
    "cmake",
    "-B", "build",
    "-G", "Ninja",
    "-DCMAKE_BUILD_TYPE=Release",
    "-DSLANG_ENABLE_TESTS=OFF",
    "-DSLANG_ENABLE_EXAMPLES=OFF",
    "-DSLANG_LIB_TYPE=STATIC",
]

cmd_build = [
    "cmake",
    "--build", "build",
    "--config", "Release",
    "--parallel"
]

if platform.system() == "Windows":
    subprocess.run(cmd_win, cwd=path, check=True)
else:
    subprocess.run(cmd_lin, cwd=path, check=True)

subprocess.run(cmd_build, cwd=path, check=True)


# copy now the libs from subprojects to Dependencies

# List of source files
libs = [
    '../subprojects/slang/build/Release/lib/libcompiler-core.a',
    '../subprojects/slang/build/Release/lib/libcore.a',
    '../subprojects/slang/build/Release/lib/libgfx.a',
    '../subprojects/slang/build/Release/lib/libslang-compiler.a',
    '../subprojects/slang/build/Release/lib/libslang-cpp-parser.a',
    '../subprojects/slang/build/Release/lib/libslang-rt.a',

    # external static libs
    '../subprojects/slang/build/external/lz4/build/cmake/liblz4.a',
    '../subprojects/slang/build/external/miniz/libminiz.a'
]

# Destination directory
dest = Path("../Dependencies/lib/slang")

# Create destination folder if it doesn't exist
dest.mkdir(parents=True, exist_ok=True)

for lib in libs:
    src = Path(lib)

    if not src.exists():
        print(f"⚠ Missing: {src}")
        continue

    shutil.copy2(src, dest / src.name)
    print(f"✔ Copied {src.name}")