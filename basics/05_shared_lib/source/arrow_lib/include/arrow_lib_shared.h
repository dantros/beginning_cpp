#pragma once

#if defined(ARROW_LIB)
    #define ARROW_LIB_API __declspec(dllexport)
#else
    #define ARROW_LIB_API __declspec(dllimport)
#endif