# Basic single file C++ examples

These set of examples aims to illustrate different features of the C++ programming language

- [hello_world.cpp](./hello_world.cpp) : Where it all begins!
- [tutorial_01.cpp](./tutorial_01.cpp) : Tutorial C++ code showing how to use: structs, classes, templates, operator overloading, const, references, namespaces, std:vector, std::format, different 'for' loop versions, doxygen documentation and the standard input and output.

#  Building the examples

As the examples are in a single file, you can try them easily with one of the following methods.
The recomendation is to try options 1 to 3 in order.

## Online C++ compiler

Copy-paste the source code to an online C++ compiler, such as: https://cpp.sh/

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

Do note, that in a normal 'cmd' you won't have access to 'cl' nor other building software. The 'cmd' needs to be configured with some environment variables to gain access.

I know you are excited at this point, so go ahead and compile a hello_world program all by yourself. Get the code at 'basics/hello_world.cpp', put this file in a folder of your preference (Let us say C:\tutorials) and then run:
```
C:\tutorials>cl hello_world.cpp
```
Your folder will get 2 new files: hello_world.obj and hello_world.exe
To execute the code, run the exe file with
```
C:\tutorials> hello_world.exe
```
And that's it :)

You will get your executable 'hello_world.exe' in the same folder. Try it.

*We are just starting the C++ journey.*

For most of the examples provided, you will need a few extra flags
```
C:\tutorials> cl.exe /std:c++20 /EHsc tutorial_01.cpp
```
`/std:c++20` tells the compiler to use the C++20 standard, while `/EHsc` enable the exceptions used by the STL. The compiler will complain if you do not use both of these tags for most of the examples provided in this section.

## Visual Studio on Windows

[WIP]

## MinGW on Windows

[WIP]

## g++ on Ubuntu

[WIP]

## g++ on WSL with Ubuntu

[WIP]
