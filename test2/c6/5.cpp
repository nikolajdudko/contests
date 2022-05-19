#include <iostream>
#include <map>
#include <utility>
#include <algorithm>
#include <vector>
#include <sstream>
#include <unordered_map>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::unordered_map;
using std::pair;
using std::vector;


int
main()
{  
    uint64_t Z = 4294967161;

    unordered_map<uint32_t, vector<uint32_t>> s1;
    auto it1 = s1.begin();
    map<pair<uint32_t, uint32_t>, uint64_t> m1;

    uint32_t R;
    uint32_t C;
    uint64_t V;

    cin >> R >> C >> V;
    while (R or C or V != Z) {
        V %= Z;
        pair<uint32_t, uint32_t> j = {R, C};
        m1[j] = V;
        if ((it1 = s1.find(C)) != s1.end()) {
            (it1->second).push_back(R);
        } else {
            vector<uint32_t> l = {R};
            s1[C] = l;
        }
        cin >> R >> C >> V;
    }

    map<pair<uint32_t, uint32_t>, uint64_t> ans;
    auto it = ans.begin();
    cin >> R >> C >> V;
    while (not cin.eof()) {
        V %= Z;

        if (s1.find(R) != s1.end()) {
            for (auto k : s1[R]) {

                uint64_t a = (V * m1[{k, R}]) % Z;
                if ((it = ans.find({k, C})) != ans.end()) {
                    it->second += a;
                    it->second %= Z;   
                } else {
                    ans[{k, C}] = a;
                }
            }
        }
        cin >> R >> C >> V;
    }   

    std::stringstream ss;
    for (auto i : ans) {
        if (i.second) {
            ss << i.first.first << ' ' << i.first.second << ' ' << i.second << endl;
        }
    }
    cout << ss.str();
}
