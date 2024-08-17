/**
 * @file tutorial_01.cpp
 * @author Daniel Calderón (https://github.com/dantros)
 * @brief Tutorial C++ code showing how to use: structs, classes, templates, operator overloading,
 *     const, references, namespaces, std:vector, std::format, different 'for' loop versions,
 *     doxygen documentation and the standard input and output.
 * @version 1.0
 * @date 2024-08-17
 * @license This code is released under the MIT public licence.
 * 
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <format>
#include <iomanip>

namespace Earth
{

template <typename Type>
struct PointT
{
    Type x, y, z;

    PointT<Type>& operator+=(const PointT<Type>& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    PointT<Type>& operator*=(const float scale)
    {
        x *= scale;
        y *= scale;
        z *= scale;
        return *this;
    }

    PointT<Type> operator-(const PointT<Type>& rhs) const
    {
        return { x - rhs.x, y - rhs.y, z - rhs.z };
    }
};

using PointF = PointT<float>;

template <typename Type>
std::ostream& operator<<(std::ostream& os, const PointT<Type>& point)
{
    return os << "( " << point.x << ", " << point.y << ", " << point.z << ")";
}

template <typename Type>
PointT<Type> operator+(const PointT<Type>& lhs, const PointT<Type>& rhs)
{
    return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
}

template <typename Type>
PointT<Type> operator*(const PointT<Type>& lhs, float rhs)
{
    return { lhs.x * rhs, lhs.y * rhs, lhs.z * rhs };
}

template <typename Type>
PointT<Type> operator*(float lhs, const PointT<Type>& rhs)
{
    return { lhs * rhs.x, lhs * rhs.y, lhs * rhs.z };
}

/* \class Arrow
 * \brief A class that represets an oriented segment between 2 points in the 3D space.
 * This is Doxygen documentation., check out https://www.doxygen.nl/
 */
class Arrow
{
public:
    Arrow() :
        mSource{ 0, 0, 0 },
        mTarget{ 0, 0, 0 }
        {}
        
    Arrow(const PointF& source_, const PointF& target_) :
        mSource(source_),
        mTarget(target_)
    {}

    const PointF& source() const
    {
        return mSource;
    }

    const PointF& target() const { return mTarget; }

    Arrow invert() const
    {
        return { mTarget, mSource };
    }

    /* \brief Get a Point between source and target at a distance proportional to factor.
     *
     * \param factor a float number between 0 and 1. 0 will be source, and 1 will be target.
     */ 
    PointF interpolate(float factor) const
    {
        const PointF delta = mTarget - mSource;
        const PointF localInterpolate = delta * factor;
        return mSource + localInterpolate;
    } 

    Arrow& operator+=(const PointF& rhs)
    {
        mSource += rhs;
        mTarget += rhs;
        return *this;
    }

private:
    PointF mSource, mTarget;
};

std::ostream& operator<<(std::ostream& os, const Arrow& arrow)
{
    return os<< "[" << arrow.source() << " -> " << arrow.target() << "]";
}

std::vector<PointF> linspace(const PointF& lhs, const PointF& rhs, const unsigned int numberOfPoints)
{
    std::vector<PointF> points;
    points.reserve(numberOfPoints);

    const Arrow arrow(lhs, rhs);
    for (std::size_t i = 0; i < numberOfPoints; ++i)
    {
        const double factor = static_cast<double>(i) / (numberOfPoints-1);
        points.push_back(
            arrow.interpolate(factor)
        );
    }
    return points;
}

}

int main()
{
    const Earth::PointF p1{1, 1, 0};
    const Earth::PointF p2(2.0f, 2.0f, 0.0f);

    std::cout << "p1 = " << p1 << std::endl;
    std::cout << "p2 = " << p2 << std::endl;

    const Earth::Arrow arrow12(p1, p2);

    std::cout << "p2->p1 = " << arrow12.invert() << std::endl;

    unsigned int numberOfPoints;
    std::cout << "How many points do you need to discretize p1 to p2 arrow? ";
    std::cin >> numberOfPoints;

    auto interpolatedPoints = Earth::linspace(p1, p2, numberOfPoints);

    std::cout << "Original points: " << std::endl;
    for(auto& point : interpolatedPoints)
        std::cout << point << ", ";

    // inplace transformation
    float scale = 10.0f;
    std::for_each(interpolatedPoints.begin(), interpolatedPoints.end(), [&scale](Earth::PointF& point){
        point *= scale;
    });

    std::cout << std::endl;
    std::cout << "Original points scaled by " << scale << ":" << std::endl;
    for (auto it = interpolatedPoints.begin(); it != interpolatedPoints.end(); ++it)
    {
        const auto& point = *it;
        std::cout << point << ", ";
    }

    // assigning new calculated values
    float scale2 = 1.e-4f;
    std::transform(interpolatedPoints.begin(), interpolatedPoints.end(), interpolatedPoints.begin(),
        [&scale2](Earth::PointF& point){
            return point * scale2;
        });

    std::cout << std::endl;
    std::cout << std::format("Original points scaled by {} and then by {}: ", scale, scale2) << std::endl;
    for (std::size_t index = 0; index != interpolatedPoints.size(); ++index)
    {
        const auto& point = interpolatedPoints[index];
        std::cout << std::setprecision(4) << point << ", ";
    }
}