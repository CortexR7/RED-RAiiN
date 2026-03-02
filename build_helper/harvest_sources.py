
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


from pathlib import Path

root_dir = Path(".")

RENDER_ENGINE_SOURCE_DIR = root_dir / "Engine" / "render_engine" / "src"
VULKANAID_SOURCE_DIR = root_dir / "Engine"  / "vulkanaid" / "src"
APP_SOURCE_DIR = root_dir / "src"

# List all .cpp files in each source folder
RENDER_ENGINE_SOURCES = list(RENDER_ENGINE_SOURCE_DIR.glob("*.cpp"))
VULKANAID_SOURCES = list(VULKANAID_SOURCE_DIR.glob("*.cpp"))
APP_SOURCES = list(APP_SOURCE_DIR.glob("*.cpp"))

# Creating a finalized list of all sources
ALL_SOURCES = RENDER_ENGINE_SOURCES + VULKANAID_SOURCES + APP_SOURCES
ALL_SOURCES_STR = [str(source) for source in ALL_SOURCES]

# Print as space-separated string
print(" ".join(ALL_SOURCES_STR))

