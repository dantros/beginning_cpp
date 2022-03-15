-- premake5.lua
workspace "HelloClasses"
   configurations { "Debug", "Release" }
   location "build"
   cppdialect "C++20"

project "HelloClasses"
   kind "ConsoleApp"
   language "C++"   
   
   targetdir "bin/%{cfg.buildcfg}"

   files { "hello_classes.cpp" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"