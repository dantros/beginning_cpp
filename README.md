# Beginning C++

This repository aims to aid beginners with C++. Covering different topics. It is a constant work in progress. So far there are examples for:

- [Software Construction Systems Tutorials](./software_construction_systems/README.md)

## Getting the necessary software

The following software is used in these tutorials.

- Get Visual Studio Community from https://visualstudio.microsoft.com/vs/community/. When installing it, select "Desktop development with C++".
- Git for windows website: https://gitforwindows.org/
- CMake website: https://cmake.org/
- Ninja website: https://ninja-build.org/
- Premake website: https://premake.github.io/
- Meson website: https://mesonbuild.com/
- SCons website: https://scons.org/
- Bazel website: https://bazel.build/

## Using the 'Developer Command Prompt for VS 2022'

Open the 'Developer Command Prompt for VS 2022' selecting it from the Windows app launcher in the 'Visual Studio 2022' folder. You can also press 'Windows key' and then start typing 'Developer Command Prompt for VS 2022'. you will get a terminal with the following text:

```
**********************************************************************
** Visual Studio 2022 Developer Command Prompt v17.9.2
** Copyright (c) 2022 Microsoft Corporation
**********************************************************************
```

The compiler is 'cl', you can get how to use it just typing it.

```
C:\tutorials>cl
Microsoft (R) C/C++ Optimizing Compiler Version 19.38.33135 for x64
Copyright (C) Microsoft Corporation.  All rights reserved.

usage: cl [ option... ] filename... [ /link linkoption... ]

C:\tutorials>
```

Do not, that in a normal 'cmd' you won't have access to 'cl' nor other building software. The 'cmd' needs to be configured with some environment variables to gain access.

I know you are exscited at this point, so go ahead and compile a hello_world program all by yourself. Get the code at 'basics/01_hello_world/source/hello_world.cpp', put this file in a folder of your preference (I'm using C>\tutorials) and then run:

```
C>\tutorials>cl hello_world.cpp
```

You will get your executable 'hello_world.exe' in the same folder. Try it.

We are just starting the C++ journey.

## Using "raw" Visual Studio Community

TODO.

## Setting up a development terminal (WIP)
- Configure a terminal to have the necesary programs available. Meaning, adding all relevant directories to the system path. There are many ways to achieve this, the basic one is directly edditing the system path.
- However, I have found convenient to create a batch file that modifies the path, so we call this batch file only when we need the development environment. You also have the advantage of using different configurations for different purposes by simply using different batch files.

For this tutorial, I'm using this 'prog.bat' file, I located it at 'C:\tutorials\prog\'. Then, I added the directory 'C:\tutorials\prog\' to the system path.

```
echo off

:: conda directory
set conda_dir="C:\ProgramData\anaconda3\condabin"
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
