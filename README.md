
## 🔧 Build Instructions

![GCC](https://img.shields.io/badge/GCC-GNU-red?style=flat-square)
![Clang](https://img.shields.io/badge/Clang-LLVM-blue?style=flat-square)
![MSVC](https://img.shields.io/badge/MSVC-Visual%20Studio-0078D7?style=flat-square)
![CMake](https://img.shields.io/badge/CMake-Build%20Tool-064F8C?style=flat-square&logo=cmake)
![Ninja](https://img.shields.io/badge/Ninja-Build%20System-darkgreen?style=flat-square)
![Make](https://img.shields.io/badge/Make-Build%20System-lightgrey?style=flat-square)

> ⚠️ **Note:** This section is still incomplete and will be expanded over time.
>
> **Supported platforms:** Windows and Linux only.

### Prerequisites

Before building, make sure you have the following tools installed on your system:

- [CMake](https://cmake.org/) — primary build system
- **Linux:** `make`
- **Windows:** [Ninja](https://ninja-build.org/), **or** Visual Studio 2026 with an MSVC toolset that supports C++20

---

### Step 1 — Clone the Repository

```powershell
git clone https://github.com/CortexR7/RED-RAiiN.git --recursive
```

---

### Step 2 — Create the Build Directory

```powershell
cd RED-RAiiN
mkdir build
cd build
```

---

### Step 3 — Configure the Build

**Linux:**

```powershell
cmake ..
```

**Windows (Ninja):**

```powershell
cmake -G Ninja ..
```

**Windows (Visual Studio 2026):**

```powershell
cmake -G "Visual Studio 18 2026" -A x64 ..
```

---

### Step 4 — Compile

**Linux:**

```powershell
make
```

**Windows (Ninja):**

```powershell
ninja
```

**Windows (Visual Studio 2026):**

Open the generated `.sln` in Visual Studio 2026 and build, or run:

```powershell
cmake --build .
```

---

### Step 5 — Run

```powershell
./RED-RAiiN                                  #or .\RED-RAiiN on windows
```

That's it — the engine should now be running! 🎉

