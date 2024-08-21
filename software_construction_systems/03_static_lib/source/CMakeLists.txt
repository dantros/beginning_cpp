cmake_minimum_required(VERSION 3.20)
set(CMAKE_LEGACY_CYGWIN_WIN32 OFF)

project(code_as_static_library CXX)

# Here we are including the "CMakeLists.txt" file in the subdirectory "arrow_lib"
# It is a way to distribute/encapsulate the build process.
# But we could also have described the arrow_lib library here in the same file.
add_subdirectory(arrow_lib)

# We also need to know where are the headers
set(ARROW_LIB_INCLUDES arrow_lib/include)

add_executable(static_lib_demo "main.cpp")
set_property(TARGET static_lib_demo PROPERTY CXX_STANDARD 20)

# Here we bind the library and its headers
target_link_libraries(static_lib_demo PRIVATE arrow_library)
target_include_directories(static_lib_demo PRIVATE ${ARROW_LIB_INCLUDES})
