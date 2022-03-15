#include <cmath>
#include "triangle.h"
#include "point_functions.h"

// This function is only avaliable for this cpp file...
float distance(const Point& lhs, const Point& rhs)
{
    const Point delta = lhs - rhs;
    const float squaredDistance = delta.x * delta.x + delta.y * delta.y;
    return std::sqrt(squaredDistance);
}

Triangle::Triangle(const Point& a, const Point& b, const Point& c):
    mA(a), mB(b), mC(c)
{
}

float Triangle::area() const
{
    // Heron's formula

    const float a = distance(mB, mC);
    const float b = distance(mC, mA);
    const float c = distance(mA, mB);
    const float s = a + b + c;

    return std::sqrt(s * (s - a) * (s - b) * (s - c));
}

float Triangle::perimeter() const
{
    return distance(mA, mB) + distance(mB, mC) + distance(mC, mA);
}

Point Triangle::center() const
{
    return (mA + mB + mC) / 3.0f;
}