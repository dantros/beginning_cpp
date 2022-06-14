
#include <iostream>
#include <thread>
#include <mutex>
#include <iomanip>
#include <iso646.h>
#include <cstdint>
#include <vector>
#include <functional>

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

void searchForPrimeNumbers(std::mutex& storageMutex, const std::uint64_t first, const std::uint64_t last, std::vector<std::uint64_t>& primeNumbers, const char monitor)
{
    static constexpr std::uint64_t IterationsToMonitor = static_cast<std::uint64_t>(1e6);

    for (std::uint64_t number = first; number < last; ++number)
    {
        if (isPrime(number))
        {
            storageMutex.lock();
            // critical section
            primeNumbers.push_back(number);
            // end of critical section
            storageMutex.unlock();
        }
        if ((number - first) % IterationsToMonitor == 0)
        {
            std::cout << monitor;
        }
    }

    std::cout << std::endl
        << "\tRange [" << first << ", " << last << "[ inspected. " << primeNumbers.size() << " prime numbers found." << std::endl;
}

void main() 
{
    std::mutex storageMutex;

    std::vector<std::uint64_t> primeNumbers;

    // spawn and start threads
    // each thread has its own local storage. To pass by reference, we need std::ref.
    std::thread thread1(searchForPrimeNumbers, std::ref(storageMutex), static_cast<std::uint64_t>(0),   static_cast<std::uint64_t>(1e7), std::ref(primeNumbers), '1');
    std::thread thread2(searchForPrimeNumbers, std::ref(storageMutex), static_cast<std::uint64_t>(1e7), static_cast<std::uint64_t>(5e7), std::ref(primeNumbers), '2');
    std::thread thread3(searchForPrimeNumbers, std::ref(storageMutex), static_cast<std::uint64_t>(5e7), static_cast<std::uint64_t>(1e8), std::ref(primeNumbers), '3');
    std::thread thread4(searchForPrimeNumbers, std::ref(storageMutex), static_cast<std::uint64_t>(1e8), static_cast<std::uint64_t>(2e8), std::ref(primeNumbers), '4');

    // wating for both threads to finish
    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();

    std::cout << "We found: "
        << primeNumbers.size()
        << " prime numbers." << std::endl;
    std::cout << "We are done for today." << std::endl;
}