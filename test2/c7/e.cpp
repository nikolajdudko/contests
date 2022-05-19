#include <iostream>
#include <iomanip> 
#include <vector>
#include <iterator>
#include <functional>

template <typename InputIt, typename Predicate>
void myapply(InputIt left, InputIt right, Predicate P) 
{
     while (left != right) {
        P(*left++);
    }
}


template <typename U>
U f(U x)
{
    return x % 2;
}

int
main()
{
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    myapply(v.begin(), v.end(), f<int>);

    for (auto i : v) {
        std::cout << i << ' ';
    }
}
