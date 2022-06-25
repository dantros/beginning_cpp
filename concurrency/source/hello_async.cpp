
#include <iostream>
#include <future>
#include <iomanip>
#include <iso646.h>
#include <cstdint>
#include <vector>
#include <array>
#include <functional>
#include <chrono>

bool isPrime(const std::uint64_t number)
{
    // extracted from https://en.wikipedia.org/wiki/Primality_test
    if (number == 2 || number == 3)
        return true;

    if (number <= 1 || number % 2 == 0 || number % 3 == 0)
        return false;

    for (std::uint64_t i = 5; i * i <= number; i += 6)
    {
        if (number % i == 0 || number % (i + 2) == 0)
            return false;
    }

    return true;
}

void searchForPrimeNumbers(const std::uint64_t first, const std::uint64_t last, std::vector<std::uint64_t>& primeNumbers, const char monitor)
{
    static constexpr std::uint64_t IterationsToMonitor = static_cast<std::uint64_t>(1e6);

    auto startTime = std::chrono::steady_clock::now();

    for (std::uint64_t number = first; number < last; ++number)
    {
        if (isPrime(number))
        {
            primeNumbers.push_back(number);
        }
        if ((number - first) % IterationsToMonitor == 0)
        {
            std::cout << monitor;
        }
    }

    auto endTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = endTime - startTime;

    std::cout << std::endl
        << "\tRange [" << first << ", " << last << "[ inspected by thread " << monitor << " in " << duration.count() << " seconds. " << primeNumbers.size() << " prime numbers found." << std::endl;
}

void main() 
{
    auto startTime = std::chrono::steady_clock::now();

    std::vector<std::uint64_t> primeNumbers1, primeNumbers2, primeNumbers3, primeNumbers4;

    // Note about the static_cast: we dont want warnings in our code, so we avoid the automatic conversion double to integer
    constexpr std::array<std::uint64_t, 5> limits{
        static_cast<std::uint64_t>(0),
        static_cast<std::uint64_t>(3e7),
        static_cast<std::uint64_t>(5e7),
        static_cast<std::uint64_t>(8e7),
        static_cast<std::uint64_t>(1e8)};

    constexpr std::uint64_t LimitsScale = 3;

    // we can launch another thread (if possible) with async, and continue working in the current thread.
    // each thread has its own local storage. To pass by reference, we need std::ref.
    auto asyncThread = std::async(searchForPrimeNumbers, LimitsScale * limits[0], LimitsScale * limits[1], std::ref(primeNumbers1), '1');

    // we do some work in this thread.
    searchForPrimeNumbers(LimitsScale * limits[1], LimitsScale * limits[2], std::ref(primeNumbers2), '2');

    // at this point, the async thread should be done, if it is not ready yet, it will be completed.
    asyncThread.get();

    // here we have all the info that we need.

    // Note: we can add execution preferences as policies, to prefer async calls to be executed in a different thread,
    // in the same thread when calling get, or just let runtime decides. Check the documentation!.

    auto endTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = endTime - startTime;

    std::cout << "We found: "
        << primeNumbers1.size() << " + " 
        << primeNumbers2.size() << " = "
        << primeNumbers1.size() + primeNumbers2.size()
        << " prime numbers in " << duration.count() << " seconds." << std::endl;
    std::cout << "We are done for today." << std::endl;
}