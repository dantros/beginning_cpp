#pragma once
#include "point.h"

class Triangle
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