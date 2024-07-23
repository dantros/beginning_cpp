#pragma once
#include "arrow_lib_shared.h"
#include "point.h"

class ARROW_LIB_API Triangle
{
private:
    Point mA, mB, mC;

public:
    Triangle() = delete;

    Triangle(const Point& a, const Point& b, const Point& c);

    float area() const;

    float perimeter() const;

    Point center() const;
};