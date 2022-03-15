# beginning_cpp

This is a simple set of examples mean to aid beginners with C++ on Windows with CMake and Premake.

## Getting started

- Get Visual Studio Community from https://visualstudio.microsoft.com/vs/community/. When installing it, select "Desktop development with C++".
- Get git for windows from https://gitforwindows.org/, and clone this repository.
- Get CMake from https://cmake.org/
- Get Premake from https://premake.github.io/
- You only need one building system, but it is useful to learn how both of them work.
- Make a folder called build next to each source folder.
- Open "x64 Native Tools Command Prompt for VS 2019" inside the build folder. Execute there `cmake ..\source`.
- Open the `.sln` file inside the build folder. clic on the menus `Build > Build Solution`. You can try Relese and Debug modes ass Solution Configuration. You should see a message stating successful compilation in the Output console.
- Run the executable in the folder Release or Debug (depending on the solution configuration). Run it from a CMD or PowerShell as it will only print some lines and close.
- Just Rock with C++ and CMake!
- You should try premake as well
- Add premake5.exe to your path or call it with the right path. then execute `premake5 vs2019` (or the version of your Visual Studio) in the source folder (i.e. where you have the premake5.lua). This will create a build forder with the `.sln` file.
- Compile it in the same way with Visual Studio. A bin folder will be created with a Release or Debug folder depending on the Solution Configuration. Inside them, you will find your binaries.
- Just Rock with C++ and Premake!

## In progress

- premake files for examples with many files.
- C++ examples using templates.
- C++ examples using the C++ STL.
- Checking building systems on Ubuntu.