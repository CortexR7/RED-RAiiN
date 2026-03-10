#   RED-RAiiN Engine ![Vulkan](https://img.shields.io/badge/Vulkan-API-orange?logo=vulkan&style=flat-square)

## Notes
- This engine is still in alpha and probably will stay in alpha for a long time.
- Abstraction layer might break sooner or later.
- This project was created to dive into Vulkan and learn about CG Math and GPU execution.

## Features
- This a really simple game engine to build 3D games.
- Additinal info coming soon.

## How to compile ? ![GCC](https://img.shields.io/badge/GCC-GNU-red)  ![Clang](https://img.shields.io/badge/Clang-LLVM-blue)  ![MSVC](https://img.shields.io/badge/MSVC-Visual%20Studio-0078D7)   ![Meson](https://img.shields.io/badge/Meson-Build%20System-339999)


WARNING THIS SCETION STLL LACKS A LOT OF INFORMATION!


In order to compile the engine from source you must have [Meson](https://mesonbuild.com/) installed on your system.
After you have done this you can clone the repo by doing this:
```powershell
git clone https://github.com/CortexR7/RED-RAiiN.git --recursive
```
Now you can continue with building. First we need to build the dependencies. For this go to the root directory and then execute the script that is located inside build_helper/compile_slang_lib.py

The steps should look like this:

```powershell
cd RED-RAiiN
python3 build_helper/compile_slang_lib.py       # or use python instead on windows 
```

Once the dependencies are built we can go to and start building the actual project. For this type in the command:
```powershell
meson setup build       # "build" can be replaced with any name for the build directory
```

Now we are almost done.

You can go into the build directory now and compile the executable and then run it:
```powershell
cd build
meson compile
```
```powershell
./RED-RAiiN
```

And that is it Now the engien should be running.