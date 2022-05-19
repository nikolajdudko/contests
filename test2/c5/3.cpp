#include <iostream>
#include <iomanip>
#include <vector>
#include <iterator>
#include <algorithm>

void
process(const std::vector<int>& x, std::vector<int>& y)
{
    if (x.empty() || y.empty()) {
        return;
    }
    
    std::vector<int> v(x);
    std::sort(v.begin(), v.end());
    auto a = std::unique(v.begin(), v.end()) - 1;
    int s = y.size();

    auto b = v.begin();
    while (*b < 0 && b != a + 1) {
        b++;
    }

    while (*a > s && *a > 0) {
        a--;
    }
    a++;

    auto f = b;
    std::vector<int> copy;
    for (int i = 0; i < s; i++) {
        if (a - b == 0 || i != *f) {
            copy.push_back(i);
        } else if (f <= a) {
            f++;
        }
    }

    std::vector<int> ans;
    for (auto i = copy.begin(); i < copy.end(); i++) {
        ans.push_back(*(y.begin() + *i));
    }
    y.swap(ans);
}

/*
int
main()
{
    std::vector<int> a = {-1, -2, -3};
    std::vector<int> b = {1, 0, 2, 3};

   // a.swap(b);

    process(a, b);

    for (auto n : b) {
        std::cout << n << std::endl;
    }
}
*/
