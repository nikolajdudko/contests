#include <iostream>
#include <iomanip> 
#include <vector>
#include <iterator>
#include <functional>
#include <algorithm>
#include <set>

template <typename InputIt, typename InputIt2>
InputIt2
myremove(InputIt x1, InputIt y1, InputIt2 x2, InputIt2 y2) 
{
    if (x1 == y1 or x2 == y2) {
        return y2;
    }
    
    std::vector<int> v(x1, y1);
    std::sort(v.begin(), v.end());
    auto a = std::unique(v.begin(), v.end()) - 1;
    int s = std::distance(x2, y2);

    auto b = v.begin();
    while (*b < 0 && b != a + 1) {
        b++;
    }

    while (*a > s && *a > 0) {
        a--;
    }
    a++;

    auto f = b;
    std::vector<int> copy;;
    for (int i = 0; i < s; i++) {
        if (a - b == 0 || i != *f) {
            copy.insert(copy.end(), i);
        } else if (f <= a) {
            f++;
        }
    }


    auto tmp = x2;
    for (auto i = copy.begin(); i < copy.end(); i++) {
        auto k = x2;
        std::advance(k, *i);
        std::swap(*k, *tmp);
        tmp++;
    }
    return tmp;
}



int
main()
{
    std::vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    std::vector<int> vv = {0, 1, 2, 3, 7};

    myremove(vv.begin(), vv.end(), v.begin(), v.end());
    
    for (auto i : v) {
        std::cout << i << ' ';
    }
}

