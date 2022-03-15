
#include <iostream>
#include "point.h"
#include "point_functions.h"
#include "arrow.h"
#include "arrow_functions.h"
#include "triangle.h"

int main()
{
    const Point p1{1, 1, 0}, p2{2, 0, 0};
    const Point p3(0, 2, 0);

    std::cout << "p1 = " << p1 << std::endl;
    std::cout << "p2 = " << p2 << std::endl;
    std::cout << "p3 = " << p3 << std::endl;

    const Arrow arrow12(p1, p2);

    std::cout << "p1->p2 = " << arrow12 << std::endl;

    const Arrow arrow21 = arrow12.invert();

    std::cout << "p2->p1 = " << arrow21 << std::endl;

    const Triangle triangle(p1, p2, p3);

    std::cout << "triangle area = " << triangle.area() << std::endl;
    std::cout << "triangle perimeter = " << triangle.perimeter() << std::endl;
    std::cout << "triangle center = " << triangle.center() << std::endl;
}