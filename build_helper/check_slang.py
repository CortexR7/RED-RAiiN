
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
#


import os
import sys

# Directory to check
lib_dir = "Dependencies/lib/slang"

# List of required files
required_libs = [
    'libcompiler-core.a',
    'libcore.a',
    'libgfx.a',
    'libslang-compiler.a',
    'libslang-cpp-parser.a',
    'libslang-rt.a',
    'liblz4.a',
    'libminiz.a',
]

missing = []

for lib in required_libs:
    lib_path = os.path.join(lib_dir, lib)
    if not os.path.isfile(lib_path):
        missing.append(lib_path)

if missing:
    print("Error: The following dependencies are missing:")
    for path in missing:
        print(f"  - {path}")
    sys.exit(1)

print("All dependencies are present ✅")