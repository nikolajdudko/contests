#include <iostream>
#include <vector>
#include <algorithm>
#include <map>


using std::cin;
using std::cout;
using std::endl;
using std::string;

int
main()
{   
    std::map<string, std::vector<int>> m;
    string s;
    int n;
    cin >> s;
    cin >> n;
    while (!cin.eof()) {
        if (m.count(s)) {
            m[s][0] += n;
            m[s].push_back(n);
        } else {
            std::vector<int> v = {n, n};
            m[s] = v;
        }
        cin >> s;
        cin >> n;
    }

    for (auto g : m) {
        cout << g.first << ' ' << (double)g.second[0] / (g.second.size() - 1) << endl;
    }
}
