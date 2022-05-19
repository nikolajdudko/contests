#include <iostream>
#include <map>
#include <utility>
#include <algorithm>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <set>

int
main()
{
    std::string s = "bbbbbbbbbbbbbbbaaaaaaaaaaaaaaa";
    std::sort(s.begin(), s.end());
    s.erase(std::unique(s.begin(), s.end()), s.end());

    for (auto n : s) {
        std::cout << n << std::endl;
    }
}
