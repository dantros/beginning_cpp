#pragma once
#include <iostream>
#include "arrow_lib_shared.h"
#include "point.h"

ARROW_LIB_API std::ostream& operator<<(std::ostream& os, const Point& point);

ARROW_LIB_API Point operator+(const Point& lhs, const Point& rhs);

ARROW_LIB_API Point operator-(const Point& lhs, const Point& rhs);

ARROW_LIB_API Point operator*(const Point& lhs, float rhs);

ARROW_LIB_API Point operator*(float lhs, const Point& rhs);

ARROW_LIB_API Point operator/(const Point& lhs, float rhs);

ARROW_LIB_API Point operator/(float lhs, const Point& rhs);
