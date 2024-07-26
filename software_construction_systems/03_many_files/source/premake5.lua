-- premake5.lua
workspace "many_files_ws"
    -- Do note these are just names, the compiler characteristics for each are defined with the filters bellow
    configurations { "Debug", "Release" }
    location "../build_premake5"

project "many_files"
    location "%{wks.location}/many_files"
    -- check out the values for 'kind' at https://premake.github.io/docs/kind
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    targetdir "%{wks.location}/%{cfg.buildcfg}"

    -- you can use wildcards to catch all the source files...
    -- files { "**.cpp" }
    -- but this time we will write them one by one...
    files {
        "main.cpp",
        "arrow_functions.cpp",
        "arrow.cpp",
        "point_functions.cpp",
        "triangle.cpp"
    }
    -- We do not need to specify headers, each cpp file
    -- should now how to find them when including them.

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        -- check out the values for 'optimize' at https://premake.github.io/docs/optimize/
        optimize "On"

-- run this script on the terminal as: premake5 vs2022
-- for other generators, check: https://premake.github.io/docs/Using-Premake