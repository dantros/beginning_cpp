# Basic single file C++ examples

These set of examples aims to illustrate different features of the C++ programming language

- [hello_world.cpp](./hello_world.cpp) : Where it all begins!
- [tutorial_01.cpp](./tutorial_01.cpp) : Tutorial C++ code showing how to use: structs, classes, templates, operator overloading, const, references, namespaces, std:vector, std::format, different 'for' loop versions, doxygen documentation and the standard input and output.

#  Building the examples

As the examples are in a single file, you can try them easily with one of the following methods.
The recomendation is to try options 1 to 3 in order.

1. Copy-paste the source code to an online C++ compiler, such as: https://cpp.sh/

2. Using Microsoft Visual Studio CLI (Command Line Interface). Just open 'Developer Command Prompt for VS 2022' and execute:

```
YOUR_WORKING_DIRECTORY> cl.exe /std:c++20 /EHsc your_program.cpp
```

`/std:c++20` tells the compiler to use the C++20 standard, while `/EHsc` enable the exceptions used by the STL. ?The compiler will complain if you do not use both of this tags for most of the provided examples.

Your folder will get 2 new files: your_program.obj and your_program.exe
To execute the code, run the exe file with

```
YOUR_WORKING_DIRECTORY> your_program.exe
```

And that's it :)

3. On Visual Studio on Windows

[WIP]

4. MinGW on Windows

[WIP]

5. g++ on Ubuntu

[WIP]

6. g++ on WSL with Ubuntu

[WIP]
