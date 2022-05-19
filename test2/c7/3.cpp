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


template <typename InputIt, typename Predicate>
auto myfilter2(InputIt left, InputIt right, Predicate P)
{
    std::vector<std::reference_wrapper<typename std::iterator_traits<InputIt>::value_type>> v;

    while (left != right) {
        if (P(*left)) {
            std::reference_wrapper<typename std::iterator_traits<InputIt>::value_type> tmp(*left);
            v.push_back(tmp);
        }
        left++;
    }
    return v;
}

//template <typename U>
int f(int x)
{
    return x % 2;
}

bool
isPrime(const int number)
{
    if (number < 2) {
        return false;
    }
    if (number == 2) {
        return true;
    }
    if (number % 2 == 0) {
        return false;
    }

    for(int i = 3; (i * i) <= number; i += 2){
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

int
main()
{
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    auto vv = myfilter2(v.begin(), v.end(), isPrime);
    myapply(vv.begin(), vv.end(), f);

    for (auto i : vv) {
        std::cout << i << ' ';
    }
}

