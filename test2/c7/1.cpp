#include <iostream>
#include <iomanip> 
#include <vector>


template <typename T>
auto process(const T& cont) 
{
    auto left = cont.begin();
    auto right = cont.end();
    if (cont.empty()) {
        typename T::value_type s = {};
        return s;
    }
    typename T::value_type ans = *(--right);
    right--;
    if (right == left) {
        return ans;
    }
    right--;
    if (right == left) {
        return ans += *right;
    }

    ans += *right;
    right--;
    if (right == left) {
        return ans;
    }
    right--;
    ans += *right;  
    return ans;
}


/*
int
main()
{
    std::vector<int> v;
    int a = process(v);
    std::cout << a;
}
*/
