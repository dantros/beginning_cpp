# Software Construction Systems Tutorial

This is a simple set of examples meant to aid beginners with C++ on Windows using different build systems.

Currently there are examples for:

- CMake, including CMakePresets.json
- premake
- Meson

All of them are used in the following examples:

- Executable based on a single file
- Executable based on many files
- Static library
- Shared library

## Building the basic examples // outdated.

- Open "x64 Native Tools Command Prompt for VS 2019" inside the build folder. Execute there `cmake ..\source`.
- Open the `.sln` file inside the build folder. clic on the menus `Build > Build Solution`. You can try Relese and Debug modes ass Solution Configuration. You should see a message stating successful compilation in the Output console.
- Run the executable in the folder Release or Debug (depending on the solution configuration). Run it from a CMD or PowerShell as it will only print some lines and close.

## Using premake // outdated.

- Add premake5.exe to your path or call it with the right path. then execute `premake5 vs2019` (or the version of your Visual Studio) in the source folder (i.e. where you have the premake5.lua). This will create a build forder with the `.sln` file.
- Compile it in the same way with Visual Studio. A bin folder will be created with a Release or Debug folder depending on the Solution Configuration. Inside them, you will find your binaries.

## Pending:

- Bazel examples.
- Check build systems on Ubuntu and fix them if problems are found.
