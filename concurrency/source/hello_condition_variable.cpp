#include <iostream>
#include <iso646.h>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <array>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <sstream>

constexpr std::size_t ScreenWidth = 30;
constexpr std::size_t ScreenHeight = 10;

template<std::size_t WidthT, std::size_t HeightT>
class ScreenBufferT
{
public:
    const std::size_t width = WidthT;
    const std::size_t height = HeightT;
    using ArrayType = std::array<std::byte, WidthT * HeightT>;

    ScreenBufferT() : pixels() {};

    constexpr std::byte at(std::size_t col, std::size_t row) const
    {
        const std::size_t index = WidthT * row + col;
        return pixels[index];
    }

    constexpr ArrayType::reference at(std::size_t col, std::size_t row)
    {
        const std::size_t index = WidthT * row + col;
        return pixels[index];
    }

    void reset()
    {
        pixels.fill(static_cast<std::byte>(0));
    }

private:
    ArrayType pixels;
};

using ScreenBuffer = ScreenBufferT<ScreenWidth, ScreenHeight>;

void renderScreen(ScreenBuffer const& screen)
{
    std::stringstream ss;

    for (std::size_t row = 0; row < screen.height; ++row)
    {
        for (std::size_t col = 0; col < screen.width; ++col)    
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
    std::size_t x, y;
};

struct Segment
{
    Point origin, destiny;
};

void drawline(ScreenBuffer& screen, Segment const& segment)
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


void render(std::mutex& syncMutex, std::condition_variable& syncConditionalVariable, bool& readyToRender, Segment& segment, ScreenBuffer& screen)
{
    // local copy to avoid delaying other threads
    Segment renderSegment;

    while (true)
    {
        // waiting for a frame to be ready before rendering.
        {
            std::unique_lock<std::mutex> uniqueLock(syncMutex);
            syncConditionalVariable.wait(uniqueLock, [&readyToRender] { return readyToRender; });

            // copying to local memory.
            renderSegment = segment;

            // we notify other threads so we start with computing physics for the next frame while we render...
            readyToRender = false;
        }
        syncConditionalVariable.notify_all();

        // executing expensive rendering related with the frame that is just ready.
        screen.reset();
        drawline(screen, renderSegment);
        renderScreen(screen);
    }
}
 
void physics(std::mutex& syncMutex, std::condition_variable& syncConditionalVariable, bool& readyToRender, Segment& segment)
{
    constexpr double SpeedLeft = 2.0;
    constexpr double SpeedRight = 2.5;
    
    auto startTime = std::chrono::steady_clock::now();
    double timer = 0.0;

    auto integerSin = [](double angle, std::size_t min, std::size_t max)
    {
        return static_cast<std::size_t>(min + (max - min) * (std::sin(angle) + 1.0) / 2.0);
    };

    // local copy to avoid delaying other threads
    Segment physicsSegment;

    while (true)
    {
        // deltaTime to compute physics...
        auto endTime = std::chrono::steady_clock::now();
        std::chrono::duration<double> deltaTime = endTime - startTime;
        startTime = endTime;
        timer += deltaTime.count();

        // executing expensive physics computation...
        physicsSegment.origin = {0, integerSin(SpeedLeft * timer, 0, ScreenHeight-1)};
        physicsSegment.destiny = {ScreenWidth-1, integerSin(SpeedRight * timer, 0, ScreenHeight-1)};

        // waiting for the render thread to finish the rendering...
        {
            std::unique_lock<std::mutex> uniqueLock(syncMutex);
            syncConditionalVariable.wait(uniqueLock, [&readyToRender] { return not readyToRender; });

            segment = physicsSegment;
            readyToRender = true;
        }
        // notifying others threads to start rendering...
        syncConditionalVariable.notify_all();
    }
}
 
int main()
{
    std::mutex syncMutex;
    std::condition_variable syncConditionalVariable;
    bool readyToRender = false;
    Segment renderSegment;
    ScreenBuffer screen;

    screen.reset();
    renderSegment = { {0,2}, {12,7} };
    drawline(screen, renderSegment);
    renderScreen(screen);


    std::thread physicsThread(physics, std::ref(syncMutex), std::ref(syncConditionalVariable), std::ref(readyToRender), std::ref(renderSegment));
    std::thread renderThread(render, std::ref(syncMutex), std::ref(syncConditionalVariable), std::ref(readyToRender), std::ref(renderSegment), std::ref(screen));

    physicsThread.join();
    renderThread.join();
}