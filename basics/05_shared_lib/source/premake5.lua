-- premake5.lua

workspace "shared_lib_demo_ws"
    -- Do note these are just names, the compiler characteristics for each are defined with the filters bellow
    configurations { "Debug", "Release" }
    location "../build_premake5"

    -- Here we are including the "premake5.lua" file in the subdirectory "arrow_lib"
    -- It is a way to distribute/encapsulate the build process.
    include "arrow_lib"

    -- But we could also have written the arrow_lib premake project here in the same file.

project "shared_lib_demo"
    location "%{wks.location}/shared_lib_demo"
    -- This is the executable that we will link against the library
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    targetdir "%{wks.location}/%{cfg.buildcfg}"

    -- Do note: We only have the files related to thois project here, not files related to the library.
    files {"main.cpp"}

    -- Linking against arrow_lib, we need the binary and the includes.
    includedirs {"arrow_lib/include"}
    links { "arrow_library" }

    -- We use the same configurations than for the library, but we could build all permutations
    -- meaning, for instance, executable in release configuration while the library in debug configuration.
    -- TODO: develop an example for that situation
    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

-- run this script on the terminal as: premake5 vs2022
-- for other generators, check: https://premake.github.io/docs/Using-Premake