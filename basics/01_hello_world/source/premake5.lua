-- premake5.lua
workspace "hello_world_ws"
   -- Do note these are just names, the compiler characteristics for each are defined with the filters bellow
   configurations { "Debug", "Release" }
   location "../build_premake5"

project "hello_world_project"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "../build_premake5/bin/%{cfg.buildcfg}"

   files { "hello_world.cpp" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      -- check out the values for 'optimize' at https://premake.github.io/docs/optimize/
      optimize "On"

-- run this script on the terminal as: premake5 vs2022
-- for other generators, check: https://premake.github.io/docs/Using-Premake