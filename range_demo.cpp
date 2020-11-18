#include <iostream>
#include <vector>
#include "range.hpp"

int main()
{
    // range supports any value_type that implements operator+(const difference_type&)
    // and operator<(const value_type&) and supports value_type{0}
    // Examples: all integer and floating-point types, iterators

    // Usage with explicit step
    std::vector<int> vec{1, 7, 6, 3, 4};
    std::cout << "Explicit step:" << std::endl;
    for (auto x : range(vec.begin() + 1, vec.end(), 2u))
    {
        std::cout << *x << std::endl;
    }

    // Usage with implicit step
    // The step type can not be deduced and must be specified
    // Supports any difference_type that supports difference_type{1}
    std::cout << "Implicit step:" << std::endl;
    for (int x : range<int, int>(0, 5))
    {
        std::cout << x << std::endl;
    }
    return 0;
}
