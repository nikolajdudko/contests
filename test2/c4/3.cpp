#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::cin;
using std::abs;

int
f(int m, int n, int x1, int y1, int x2, int y2)
{
    std::vector<int> v = {
        abs(x1 - x2) + abs(y1 - y2),
        abs(x1 - x2) + abs(m - abs(y1 - y2)),
        abs(n - abs(x1 - x2)) + abs(y1 - y2),
        abs(n - abs(x1 - x2)) + abs(m - abs(y1 - y2))
    };

    return *(std::min_element(v.begin(), v.end()));
}

int
main()
{
    int m, n;
    int x1, y1;
    int x2, y2;
    cin >> m >> n;

    cin >> x1 >> y1 >> x2 >> y2;
    while (!cin.eof()) {
        cout << f(m, n, x1, y1, x2, y2) << endl;
        cin >> x1 >> y1 >> x2 >> y2;
    }
    return 0;
}


