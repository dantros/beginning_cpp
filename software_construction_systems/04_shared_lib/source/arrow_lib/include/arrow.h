#pragma once
#include "arrow_lib_shared.h"
#include "point.h"

/* Functions defined in the body of a class defintion are inlined...,
 * other choice is to declare them here and define them in a cpp file. */

/* the downside is that we need to start including all functionally
 * that will populate all files as they are in the headers.*/
#include "point_functions.h"

class ARROW_LIB_API Arrow
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