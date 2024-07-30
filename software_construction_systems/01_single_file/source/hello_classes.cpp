
#include <iostream>

struct Point
{
    float x, y, z;
};

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

class Arrow
{
public:
    Arrow() :
        mSource{ 0, 0, 0 },
        mTarget{ 0, 0, 0}
        {}
        
        Arrow(const Point& source_, const Point& target_) :
            mSource(source_),
            mTarget(target_)
        {}

        const Point& source() const
        {
            return mSource;
        }

        const Point& target() const
        {
            return mTarget;
        }

        Arrow invert() const
        {
            return { mTarget, mSource };
        }

        // factor between 0 and 1 will interpolate between source and target points.
        Point interpolate(float factor) const
        {
            const Point delta = mTarget - mSource;
            const Point localInterpolate = delta * factor;
            return mSource + localInterpolate;
        }


    private:
        Point mSource, mTarget;
};

std::ostream& operator<<(std::ostream& os, const Arrow& arrow)
{
    return os<< "[" << arrow.source() << " -> " << arrow.target() << " ]";
}

int main()
{
    const Point p1{1, 1, 0}, p2{2, 0, 0};
    const Point p3(0.0f, 2.0f, 0.0f);

    std::cout << "p1 = " << p1 << std::endl;
    std::cout << "p2 = " << p2 << std::endl;
    std::cout << "p3 = " << p3 << std::endl;

    const Arrow arrow12(p1, p2);

    std::cout << "p1->p2 = " << arrow12 << std::endl;
}