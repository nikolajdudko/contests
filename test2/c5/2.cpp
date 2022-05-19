#include <iostream>
#include <iomanip>
#include <vector>

void
process(std::vector<long long>& a, int64_t x)
{
    if (a.empty()) {
        return;
    }
    int i = 0;
    for (auto it = a.rbegin(); it != a.rend(); ++it) {
        if (*it >= x) {
            a.push_back(*it);
            it = a.rbegin();
            i++;
            it += i;
        }
        i++;
    }
    return;
}
