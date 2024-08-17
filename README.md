# Beginning C++

This repository aims to aid beginners with C++. Covering different topics. It is a constant work in progress. So far there are examples for:

- [C++ Basics](./basics/README.md)
- [Software Construction Systems Tutorials](./software_construction_systems/README.md)

## Getting the necessary software

The following software is used in these tutorials.

- Visual Studio Community website : https://visualstudio.microsoft.com/vs/community/
- Git for windows website: https://gitforwindows.org/
- CMake website: https://cmake.org/
- MSYS2 website: https://www.msys2.org/
- Ninja website: https://ninja-build.org/
- Premake website: https://premake.github.io/
- Meson website: https://mesonbuild.com/
- SCons website: https://scons.org/
- Bazel website: https://bazel.build/
- Python website: https://www.python.org/
- Miniconda website: https://docs.anaconda.com/miniconda/

That is a lot of software, but we will go step by step, so you know what is going on.

## Getting Started (Windows)

The recomended way toi start is using Visual Studio Comunity to get a C++ development environment.
When installing it, select "Desktop development with C++".

At this point, you can jump right ahead to [C++ Basics](./basics/README.md)

## Setting up a development terminal (Windows)
- Configure a terminal to have the necesary programs available. Meaning, adding all relevant directories to the system path. There are many ways to achieve this, the basic one is directly editing the system path.
- However, I have found convenient to create a batch file that modifies the path, so we call this batch file only when we need the development environment. You also have the advantage of using different configurations for different purposes by simply using different batch files.

For this tutorial, I'm using this 'prog.bat' file, I located it at 'C:\tutorials\prog\'. Then, I added the directory 'C:\tutorials\prog\' to the system path.

```
echo off

:: conda directory
set conda_dir="C:\Users\{YOUR_WINDOWS_USER}\miniconda3\condabin"
set "PATH=%conda_dir%;%PATH%"

:: ninja
set ninja_dir="C:\tutorials\ninja-win"
set "PATH=%ninja_dir%;%PATH%"

:: premake
set premake_dir="C:\tutorials\premake5-win"
set "PATH=%premake_dir%;%PATH%"

:: cmake
set cmake_dir="C:\Program Files\CMake\bin"
set "PATH=%cmake_dir%;%PATH%"

echo on

:: Visual Studio Developer
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
```

You should have the right paths depending on the installations you did on your machine.
