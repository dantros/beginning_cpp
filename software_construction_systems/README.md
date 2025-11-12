# Software Construction Systems Tutorials

This is a simple set of examples meant to aid beginners with C++ on Windows using different build systems.

Currently there are examples for:

- CMake, including CMakePresets.json
- premake
- Meson
- SCons

All of them are used to build (and link):

- Executable based on a single file
- Executable based on many files
- Static library
- Shared library

## Companion Videos (in Spanish)

General concepts related to the build process of a C++ program: [Conceptos C++: Translation units, object files, precompiler, linker, static/shared libs, etc](https://www.youtube.com/watch?v=LwqKLCjYYoM)

Step by step tutorial to build executables, static and dynamic libraries with different build systems. You can use the video index to jump to the system you are interested in.
- [Construyendo una Static Lib via CMake, Premake, Meson, SCons](https://www.youtube.com/watch?v=YwzqPj_isus)
- [Construyendo una DLL vía CMake, Premake, Meson, SCons](https://www.youtube.com/watch?v=CJbXOBGs8Fs)

## Pending

- Add [Bazel](https://bazel.build/) and [Buck2](https://buck2.build/) examples.
- Test and fix examples on Ubuntu and MacOS.
