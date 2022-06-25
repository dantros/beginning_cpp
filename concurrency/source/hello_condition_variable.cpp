
#include <iso646.h>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <array>
#include <chrono>
#include <cmath>
#include "tgraphics.h"

constexpr std::size_t ScreenWidth = 30;
constexpr std::size_t ScreenHeight = 10;

using ScreenBuffer = ScreenBufferT<ScreenWidth, ScreenHeight>;

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