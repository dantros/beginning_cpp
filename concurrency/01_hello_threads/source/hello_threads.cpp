
#include <iostream>
#include <thread>
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

void searchForPrimeNumbers(const std::uint64_t first, const std::uint64_t last, std::vector<std::uint64_t>& primeNumbers, const char monitor)
{
    static constexpr std::uint64_t IterationsToMonitor = static_cast<std::uint64_t>(1e6);

    for (std::uint64_t number = first; number < last; ++number)
    {
        if (isPrime(number))
        {
            primeNumbers.push_back(number);
            //std::cout << " _" << number << "_ " << std::endl;
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
    std::vector<std::uint64_t> primeNumbers1, primeNumbers2, primeNumbers3, primeNumbers4;

    // spawn and start threads
    // each thread has its own local storage. To pass by reference, we need std::ref.
    std::thread thread1(searchForPrimeNumbers, static_cast<std::uint64_t>(0),   static_cast<std::uint64_t>(1e7), std::ref(primeNumbers1), '1');
    std::thread thread2(searchForPrimeNumbers, static_cast<std::uint64_t>(1e7), static_cast<std::uint64_t>(5e7), std::ref(primeNumbers2), '2');
    std::thread thread3(searchForPrimeNumbers, static_cast<std::uint64_t>(5e7), static_cast<std::uint64_t>(1e8), std::ref(primeNumbers3), '3');
    std::thread thread4(searchForPrimeNumbers, static_cast<std::uint64_t>(1e8), static_cast<std::uint64_t>(2e8), std::ref(primeNumbers4), '4');

    // wating for both threads to finish
    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();

    std::cout << "We found: "
        << primeNumbers1.size() << " + " 
        << primeNumbers2.size() << " + " 
        << primeNumbers3.size() << " + " 
        << primeNumbers4.size() << " = "
        << primeNumbers1.size() + primeNumbers2.size() + primeNumbers3.size() + primeNumbers4.size()
        << " prime numbers." << std::endl;
    std::cout << "We are done for today." << std::endl;
}