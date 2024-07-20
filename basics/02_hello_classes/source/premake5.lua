-- premake5.lua
workspace "hello_classes_ws"
-- Do note these are just names, the compiler characteristics for each are defined with the filters bellow
   configurations { "Debug", "Release" }
   location "../build_premake5"
   

project "hello_classes_project"
   location "%{wks.location}/hello_classes_project"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "%{wks.location}/%{cfg.buildcfg}"

   files { "hello_classes.cpp" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      -- check out the values for 'optimize' at https://premake.github.io/docs/optimize/
      optimize "On"

-- run this script on the terminal as: premake5 vs2022
-- for other generators, check: https://premake.github.io/docs/Using-Premake