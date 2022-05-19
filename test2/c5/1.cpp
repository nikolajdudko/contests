#include <iostream>
#include <iomanip>
#include <vector>

void
process(const std::vector<unsigned long long int>& a, std::vector<unsigned long long int>& b, int x)
{
    if (a.empty() || b.empty()) {
        return;
    }

    auto it1 = a.cbegin();

    for (auto it2 = b.rbegin(); it2 != b.rend(); ++it2)
    {
        *it2 = (*it2) + (*it1);
        if ((it1 += x) >= a.cend()) {
            return;
        }
    }
    return;
}
