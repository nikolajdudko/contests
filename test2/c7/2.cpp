#include <iostream>
#include <iomanip> 
#include <vector>
#include <iterator>

template <typename T, typename Predicate>
T myfilter(const T& cont, Predicate P) 
{
    T v;
    for (auto i : cont) {
        if (P(i)) {
            v.insert(v.end(), i);
        }
    }
    return v;
}

/*
bool
isPrime(int number)
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
    std::vector<int> c = myfilter(v, isPrime);

    for (auto i : c) {
        std::cout << i << ' ';
    }
}
*/
