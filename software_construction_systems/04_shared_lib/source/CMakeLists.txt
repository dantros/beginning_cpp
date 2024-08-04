cmake_minimum_required(VERSION 3.20)
set(CMAKE_LEGACY_CYGWIN_WIN32 OFF)

project(code_as_shared_library CXX)

# Problems building a shared library on windows? -> https://stackoverflow.com/questions/33062728/cmake-link-shared-library-on-windows
# https://learn.microsoft.com/en-us/cpp/build/reference/module-definition-dot-def-files?view=msvc-170
# https://learn.microsoft.com/en-us/cpp/build/exporting-from-a-dll-using-declspec-dllexport?view=msvc-170
# https://stackoverflow.com/questions/71824443/using-declspecdllexport-before-every-public-method

# Only with CMake, you could tell all content of the dll to be public
# You also need to add the (*) statements bellow to successfully build and use the share library on windows.
# Check https://cmake.org/cmake/help/v3.4/prop_tgt/WINDOWS_EXPORT_ALL_SYMBOLS.html#prop_tgt:WINDOWS_EXPORT_ALL_SYMBOLS
# for more information.
#if(MSVC)
#    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
#    set(BUILD_SHARED_LIBS TRUE)
#endif()

# We will do a more conventional approach, compatible with other build systems.
# This means you have to mark the public API of the dll in your code using 
# __declspec(dllexport) and __declspec(dllexport)
# check these pages:
# https://stackoverflow.com/questions/71824443/using-declspecdllexport-before-every-public-method
# https://learn.microsoft.com/en-us/cpp/build/exporting-from-a-dll-using-declspec-dllexport?view=msvc-170
# For linux, all the content of the shared library is public, so building the library is "easier", you need
# less boilerplate, but there are discussions about it, as it may not be the best way as you may want to
# keep some things private.
# Check the CMakeLists.txt file inside the arrow_lib directory.
add_subdirectory(arrow_lib)

# We also need to know where are the headers (same as for static libraries)
set(ARROW_LIB_INCLUDES arrow_lib/include)

# (*) this is the trick explained above.
#include(GenerateExportHeader)
#generate_export_header(arrow_library)

add_executable(shared_lib_demo "main.cpp")
set_property(TARGET shared_lib_demo PROPERTY CXX_STANDARD 20)

# Here we bind the library and its headers
target_link_libraries(shared_lib_demo PRIVATE arrow_library)
target_include_directories(shared_lib_demo PRIVATE ${ARROW_LIB_INCLUDES})


# We need the shared library to be in a place known by the executable. Adding its location to the system
# path will work, but also just placing it next to the executable. We can do this automatically with the
# install interface.

install(TARGETS shared_lib_demo arrow_library DESTINATION ${CMAKE_INSTALL_PREFIX})

# The install interface allows you to select the files that you want to distribute, and isolate them from
# of the build system and other temporary files.