#pragma once

#include <iostream>
#include <sstream>
#include <cstddef>

using units = std::size_t;

template<units WidthT, units HeightT>
class ScreenBufferT
{
public:
    const units width = WidthT;
    const units height = HeightT;
    using ArrayType = std::array<std::byte, WidthT * HeightT>;

    ScreenBufferT() : pixels() {};

    constexpr std::byte at(units col, units row) const
    {
        const units index = WidthT * row + col;
        return pixels[index];
    }

    constexpr ArrayType::reference at(units col, units row)
    {
        const units index = WidthT * row + col;
        return pixels[index];
    }

    void reset()
    {
        pixels.fill(static_cast<std::byte>(0));
    }

private:
    ArrayType pixels;
};

template<units WidthT, units HeightT>
void renderScreen(ScreenBufferT<WidthT, HeightT> const& screen)
{
    std::stringstream ss;

    for (units row = 0; row < screen.height; ++row)
    {
        for (units col = 0; col < screen.width; ++col)    
        {
            ss << (std::to_integer<int>(screen.at(col, row)) != 0 ? '*' : '.');
        }
        ss << std::endl;
    }
    ss << std::endl;

    std::cout << ss.str();

    // comment this to get the maximum speed...
    // the io will be a bottleneck anyway.
    // you can comment this function and see all the threading power in the CPU view of the task manager.
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(33ms);
}

struct Point
{
    units x, y;
};

struct Segment
{
    Point origin, destiny;
};

template<units WidthT, units HeightT>
void drawline(ScreenBufferT<WidthT, HeightT>& screen, Segment const& segment)
{
    const int x0 = segment.origin.x;
    const int y0 = segment.origin.y;
    const int x1 = segment.destiny.x;
    const int y1 = segment.destiny.y;

    auto plotPixel = [&screen](int x1, int y1, int x2, int y2, int dx, int dy, int decide)
    {
        // from: https://www.geeksforgeeks.org/bresenhams-line-generation-algorithm/

        //pk is initial decision making parameter
        //Note:x1&y1,x2&y2, dx&dy values are interchanged
        //and passed in plotPixel function so
        //it can handle both cases when m>1 & m<1
        int pk = 2 * dy - dx;
        for (int i = 0; i <= dx; i++)
        {
            //checking either to decrement or increment the value
            //if we have to plot from (0,100) to (100,0)
            x1 < x2 ? x1++ : x1--;
            if (pk < 0)
            {
                //decision value will decide to plot
                //either  x1 or y1 in x's position
                if (decide == 0)
                {
                    screen.at(x1, y1) = static_cast<std::byte>(1);
                    pk = pk + 2 * dy;
                }
                else
                {
                    //(y1,x1) is passed in xt
                    screen.at(y1, x1) = static_cast<std::byte>(2);
                    pk = pk + 2 * dy;
                }
            }
            else
            {
                y1 < y2 ? y1++ : y1--;
                if (decide == 0)
                {
                    screen.at(x1, y1) = static_cast<std::byte>(1);
                }
                else
                {
                    screen.at(y1, x1) = static_cast<std::byte>(2);
                }
                pk = pk + 2 * dy - 2 * dx;
            }
        }
    };
    
    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);

    //If slope is less than one
    if (dx > dy)
    {
        //passing argument as 0 to plot(x,y)
        plotPixel(x0, y0, x1, y1, dx, dy, 0);
    }
    //if slope is greater than or equal to 1
    else
    {
        //passing argument as 1 to plot (y,x)
        plotPixel(y0, x0, y1, x1, dy, dx, 1);
    }
}
