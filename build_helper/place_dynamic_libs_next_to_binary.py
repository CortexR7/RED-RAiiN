
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


#!/usr/bin/env python3
import sys
import shutil
from pathlib import Path

def main():
    if len(sys.argv) < 2:
        print("Usage: place_dynamic_libs_next_to_binary.py <build_dir>")
        sys.exit(0)  # not fatal, just a warning

    build_dir = Path(sys.argv[1])
    if not build_dir.is_dir():
        print(f"Warning: Build directory {build_dir} does not exist")
        sys.exit(0)

    # Define source directory with .so files (custom libs like Slang)
    slang_lib_dir = Path(__file__).parent.parent / "Dependencies/lib/slang"
    if not slang_lib_dir.exists():
        print(f"Warning: Slang library directory {slang_lib_dir} does not exist")
        sys.exit(0)

    # Where to copy: next to the executable
    # For simplicity, assume executable is at build_dir/RED-RAiiN
    exe_dir = build_dir
    if not exe_dir.exists():
        exe_dir.mkdir(parents=True, exist_ok=True)

    # Gather all .so files in the Slang library directory
    so_files = list(slang_lib_dir.glob("*.so*"))  # matches libslang-rt.so, libgfx.so.0.2026.3.1, etc.

    if not so_files:
        print(f"Warning: No .so files found in {slang_lib_dir}")
        sys.exit(0)

    print(f"Copying {len(so_files)} .so files to {exe_dir}")

    for so_file in so_files:
        try:
            shutil.copy2(so_file, exe_dir)
            print(f"Copied {so_file.name} -> {exe_dir}")
        except Exception as e:
            print(f"Warning: Failed to copy {so_file.name}: {e}")

    # Touch a stamp file so Meson knows this custom target ran
    stamp_file = exe_dir / "runtime_libs_copied.stamp"
    stamp_file.touch()
    print(f"Runtime copy complete. Stamp: {stamp_file}")

if __name__ == "__main__":
    main()

