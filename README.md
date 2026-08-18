# RED-RAiiN Engine

![Vulkan](https://img.shields.io/badge/Vulkan-API-orange?logo=vulkan&style=flat-square)
![Status](https://img.shields.io/badge/Status-Alpha-red?style=flat-square)
![License](https://img.shields.io/badge/License-Open%20Source-green?style=flat-square)

> A lightweight 3D game engine built on top of Vulkan — crafted as a deep dive into GPU execution, CG math, and low-level graphics programming.

---

## ⚠️ Disclaimer

- This engine is in **alpha** and will likely remain so for a while.
- The abstraction layer **may break** at any point without notice.
- This project was created primarily to explore Vulkan and learn about CG math and GPU execution.

---

## ✨ Features

- Simple and accessible 3D game engine foundation
- Built directly on the Vulkan API
- Additional features and documentation coming soon

---

## ~🔧 Build Instructions~ **This section is now obsolete and is replaced by cmake. New Section coming soon**

![GCC](https://img.shields.io/badge/GCC-GNU-red?style=flat-square)
![Clang](https://img.shields.io/badge/Clang-LLVM-blue?style=flat-square)
![MSVC](https://img.shields.io/badge/MSVC-Visual%20Studio-0078D7?style=flat-square)
![Meson](https://img.shields.io/badge/Meson-Build%20System-339999?style=flat-square)
![CMake](https://img.shields.io/badge/CMake-Build%20Tool-064F8C?style=flat-square&logo=cmake)
![Ninja](https://img.shields.io/badge/Ninja-Build%20System-darkgreen?style=flat-square)

> ⚠️ **Note:** This section is still incomplete and will be expanded over time.

### Prerequisites

Before building, make sure you have the following tools installed on your system:

- [Meson](https://mesonbuild.com/) — primary build system
- [CMake](https://cmake.org/) — required for building dependencies
- [Ninja](https://ninja-build.org/) — fast build backend used by Meson

---

### Step 1 — Clone the Repository

```powershell
git clone https://github.com/CortexR7/RED-RAiiN.git --recursive
```

---

### Step 2 — Build Dependencies

Navigate to the root directory and run the dependency build script:

```powershell
cd RED-RAiiN
python3 build_helper/compile_slang_lib.py   # use 'python' instead of 'python3' on Windows
```

---

### Step 3 — Configure the Build

Set up the Meson build directory (you can replace `build` with any name you prefer):

```powershell
meson setup build
```

---

### Step 4 — Compile

Move into the build directory and compile:

```powershell
cd build
meson compile
```

---

### Step 5 — Run

```powershell
./RED-RAiiN                                  #or .\RED-RAiiN on windows
```

That's it — the engine should now be running! 🎉
