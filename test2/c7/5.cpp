#include <iostream>
#include <iomanip> 
#include <vector>
#include <iterator>
#include <functional>
#include <algorithm>
#include <set>

template <typename InputIt, typename Comp = std::less<typename std::iterator_traits<InputIt>::value_type>>
void
selection_sort(InputIt x, InputIt y, Comp P = Comp()) 
{
    if (x == y) {
        return;
    }
    for (auto i = x; i < y - 1; i++) {
        auto min = i;
        for (auto j = i + 1; j < y; j++) {
            if (P(*j, *min)) {
                min = j;
            }
        }
        std::swap(*i, *min);
    }
}

/*
int
main()
{
    std::vector<int> v = {};

    selection_sort(v.begin(), v.end());
    
    for (auto i : v) {
        std::cout << i << ' ';
    }
}
*/
