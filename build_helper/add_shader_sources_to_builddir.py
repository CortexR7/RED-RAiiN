
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
import shutil
import sys
import os

build_dir = sys.argv[1]

# Derive project root from this script's location (build_helper/)
script_dir = os.path.dirname(os.path.abspath(__file__))
project_root = os.path.dirname(script_dir)

vert_shader = os.path.join(project_root, "Engine", "shader_source", "vertex_shader.slang")
frag_shader = os.path.join(project_root, "Engine", "shader_source", "fragment_shader.slang")

dest_vert = os.path.join(build_dir, "vertex_shader.slang")
dest_frag = os.path.join(build_dir, "fragment_shader.slang")

shutil.copy(vert_shader, dest_vert)
shutil.copy(frag_shader, dest_frag)
print("Shaders copied to:", build_dir)