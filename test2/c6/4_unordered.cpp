#include <iostream>
#include <iomanip> 
#include <sstream>
#include <set>
#include <utility>
#include <unordered_map>

struct pair_hash
{
    std::size_t operator() (const std::pair<unsigned int, unsigned int> &pair) const
    {
        return std::hash<unsigned int>()(pair.first + pair.second);
    }
};


int
main()
{   
    std::set<std::pair<unsigned int, unsigned int>> s;
    std::unordered_map<std::pair<unsigned int, unsigned int>, long long, pair_hash> m1;
    unsigned int R;
    unsigned int C;
    long long V;

    std::cin >> R >> C >> V;
    while (R or C or V != 4294967161) {
        V = V % 4294967161;
        std::pair<unsigned int, unsigned int> j = std::make_pair(R, C);
        s.insert(j);
        m1[j] = V;
        std::cin >> R >> C >> V;
    }

    std::unordered_map<std::pair<unsigned int, unsigned int>, long long, pair_hash> m2;
    std::cin >> R >> C >> V;
    while (not std::cin.eof()) {
        V = V % 4294967161;
        std::pair<unsigned int, unsigned int> j = std::make_pair(R, C);
        s.insert(j);
        m2[j] = V;
        std::cin >> R >> C >> V;
    }


    long long ans = 0;
    for (auto n : s) { 
        if (m1.find(n) != m1.end()) {
            ans += m1[n];
        }
        if (m2.find(n) != m2.end()) {
            ans += m2[n];
        }
        ans = ans % 4294967161;
        if (ans) {
            std::cout << n.first << ' ' << n.second << ' ' << ans << std::endl;
        }
        ans = 0;
    }
}
