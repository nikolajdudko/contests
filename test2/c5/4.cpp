#include <iostream>
#include <iomanip>
#include <vector>
#include <iterator>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::endl;

int
main()
{

    vector<double> v(std::istream_iterator<double>{cin}, std::istream_iterator<double>{});

    int n = v.size() / 100.0 * 10;
    for (int i = 0; i < n; ++i) {
        v.erase(v.begin());
        v.pop_back();
    }

    n = v.size() / 100.0 * 10;
    for (int i = 0; i < n; ++i) {
        v.erase(std::max_element(v.begin(), v.end()));
        v.erase(std::min_element(v.begin(), v.end()));
    }

    struct Sum {
        Sum() { sum = 0; }
        void operator()(double n) { sum += n; }
        double sum;
    };

    cout << std::setprecision(10) << for_each(v.begin(), v.end(), Sum()).sum / v.size();




}
