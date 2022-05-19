#include <iostream>
#include <iomanip>
#include <vector>
#include <iterator>
#include <algorithm>
#include <list>

using std::vector;
using std::cin;
using std::cout;
using std::endl;

int
main()
{
    std::list<unsigned long long> l;
    unsigned long long int n;

    cin >> n;
    while (!cin.eof() && n != 0) {
        l.push_back(n);
        cin >> n;
    }

    long long int a;
    long long int b;    
    cin >> a;
    while (!cin.eof()) {
        if (a > 0) {
            cin >> b;
            //вставка
            auto it = l.begin();
            std::advance(it, a - 1);
            if (l.size() > a - 1) {
                l.insert(it, b);
            } else {
                l.push_back(b);
            }
        } else {
            auto it = l.begin();
            std::advance(it, -a - 1);
            if (l.size() > -a - 1) {
                l.erase(it);
            }
        }
        cin >> a;
    }

    for (auto n : l) {
        cout << n << endl;
    }
}
