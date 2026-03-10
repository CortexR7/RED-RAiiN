import os
import sys
import platform

required_libs_lin = [
    'libcompiler-core.a',
    'libcore.a',
    'libgfx.a',
    'libslang-compiler.a',
    'libslang-cpp-parser.a',
    'libslang-rt.a',
    'liblz4.a',
    'libminiz.a',
]

required_libs_win = [
    "slang-rt.lib",
    "slang-compiler.lib",
    "gfx.lib",
    "compiler-core.lib",
    "core.lib",
    "lz4.lib",
    "miniz.lib",
    "slang-cpp-parser.lib",
]


def check_dependencies():
    script_dir = os.getcwd()
    lib_dir = os.path.join(script_dir, "Dependencies", "lib", "slang")

    is_windows = platform.system() == "Windows"
    required_libs = required_libs_win if is_windows else required_libs_lin
    os_label = "Windows" if is_windows else "Linux"

    print(f"OS detected : {os_label}")
    print(f"Checking    : {lib_dir}\n")

    if not os.path.isdir(lib_dir):
        print(f"ERROR: Directory not found: {lib_dir}")
        sys.exit(1)

    missing = []
    found = []

    for lib in required_libs:
        full_path = os.path.join(lib_dir, lib)
        if os.path.isfile(full_path):
            found.append(lib)
            print(f"  [OK]      {lib}")
        else:
            missing.append(lib)
            print(f"  [MISSING] {lib}")

    print(f"\n{len(found)}/{len(required_libs)} libraries found.")

    if missing:
        print(f"\nMissing libraries:")
        for lib in missing:
            print(f"  - {lib}")
        sys.exit(1)
    else:
        print("All required libraries are present.")


if __name__ == "__main__":
    check_dependencies()
