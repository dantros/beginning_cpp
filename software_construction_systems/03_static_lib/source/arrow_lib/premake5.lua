
project "arrow_library"
    location "%{wks.location}/arrow_library"
    -- Building as a static library
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"

    -- We are locationg the lib in the same directory than the executable.
    -- but it could be anywhere else...
    targetdir "%{wks.location}/%{cfg.buildcfg}"

    -- Considering only the files related to this library
    -- for ilustration purposes, we are using wildcards
    files { "sources/*.cpp" }

    -- ... but we could also have listed each file independently
    --[[
    files {
        "sources/arrow_functions.cpp",
        "sources/arrow.cpp",
        "sources/point_functions.cpp",
        "sources/triangle.cpp"
    }
    ]]--

    -- since headers are not located next to the source files, we need to specify the path where to look for headers
    -- this way, we can include header files in the cpp files simply as '#include "myheader.h"'
    includedirs {"includes"}

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

