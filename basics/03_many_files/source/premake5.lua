-- premake5.lua
workspace "many_files_ws"
    -- Do note these are just names, the compiler characteristics for each are defined with the filters bellow
    configurations { "Debug", "Release" }
    location "../build_premake5"

project "many_files_project"
    location "../build_premake5/many_files_project"
    -- check out the values for 'kind' at https://premake.github.io/docs/kind
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    targetdir "../build_premake5/bin/%{cfg.buildcfg}"

    -- you can use wildcards to catch all the files...
    -- files { "**.h", "**.c" }
    -- but this time we will write them one by one...
    files {
        "main.cpp",
        "arrow_functions.h",
        "arrow_functions.cpp",
        "arrow.h",
        "arrow.cpp",
        "point_functions.h",
        "point_functions.cpp",
        "point.h",
        "triangle.h",
        "triangle.cpp"
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        -- check out the values for 'optimize' at https://premake.github.io/docs/optimize/
        optimize "On"

-- run this script on the terminal as: premake5 vs2022
-- for other generators, check: https://premake.github.io/docs/Using-Premake