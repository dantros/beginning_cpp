
#include "point.h"
#include "point_functions.h"

std::ostream& operator<<(std::ostream& os, const Point& point)
{
    return os << "( " << point.x
            << ", " << point.y
            << ", " << point.z
            << ")";
}

Point operator+(const Point& lhs, const Point& rhs)
{
    return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
}

Point operator-(const Point& lhs, const Point& rhs)
{
    return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z };
}

Point operator*(const Point& lhs, float rhs)
{
    return { lhs.x * rhs, lhs.y * rhs, lhs.z * rhs };
}

Point operator*(float lhs, const Point& rhs)
{
    return { lhs * rhs.x, lhs * rhs.y, lhs * rhs.z };
}

Point operator/(const Point& lhs, float rhs)
{
    return { lhs.x / rhs, lhs.y / rhs, lhs.z / rhs };
}

Point operator/(float lhs, const Point& rhs)
{
    return { lhs / rhs.x, lhs / rhs.y, lhs / rhs.z };
}