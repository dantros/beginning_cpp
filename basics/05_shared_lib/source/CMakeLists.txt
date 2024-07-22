cmake_minimum_required(VERSION 3.4)
set(CMAKE_LEGACY_CYGWIN_WIN32 OFF)

project(code_as_shared_library CXX)

# Problems building a shared library on windows? -> https://stackoverflow.com/questions/33062728/cmake-link-shared-library-on-windows
# https://learn.microsoft.com/en-us/cpp/build/reference/module-definition-dot-def-files?view=msvc-170
# https://learn.microsoft.com/en-us/cpp/build/exporting-from-a-dll-using-declspec-dllexport?view=msvc-170
# https://stackoverflow.com/questions/71824443/using-declspecdllexport-before-every-public-method

if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    set(BUILD_SHARED_LIBS TRUE)
endif()

add_subdirectory(arrow_lib)

# We also need to know where are the headers
set(ARROW_LIB_INCLUDES arrow_lib/include)

#
include(GenerateExportHeader)
generate_export_header(arrow_library)

add_executable(shared_lib_demo "main.cpp")
set_property(TARGET shared_lib_demo PROPERTY CXX_STANDARD 20)

# Here we bind the library and its headers
target_link_libraries(shared_lib_demo PRIVATE arrow_library)
target_include_directories(shared_lib_demo PRIVATE ${ARROW_LIB_INCLUDES})
