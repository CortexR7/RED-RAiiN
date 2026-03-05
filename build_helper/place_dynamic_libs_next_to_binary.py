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

    # Set up launcher script
    setupLauncher(exe_dir, exe_name="RED-RAiiN")


def setupLauncher(exe_dir: Path, exe_name: str):
    """
    Generates a shell script next to the executable that sets LD_LIBRARY_PATH
    to the build folder where all the .so files were copied.
    """
    launcher_path = exe_dir / f"launch_{exe_name}.sh"
    build_dir_str = str(exe_dir.resolve())  # absolute path of the build dir

    script_content = f"""#!/usr/bin/env bash
# Auto-generated launcher for {exe_name}

# Use the build folder as LD_LIBRARY_PATH so the exe finds all .so files
export LD_LIBRARY_PATH="{build_dir_str}:$LD_LIBRARY_PATH"
exec "{build_dir_str}/{exe_name}" "$@"
"""

    try:
        launcher_path.write_text(script_content)
        launcher_path.chmod(0o755)  # make it executable
        print(f"Launcher script created: {launcher_path}")
    except Exception as e:
        print(f"Warning: Failed to create launcher script: {e}")

if __name__ == "__main__":
    main()
