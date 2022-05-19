#include <iostream>
#include <vector>
#include <algorithm>


using std::cin;
using std::cout;
using std::endl;

bool
comp(int a, int b)
{
    unsigned int c1 = 0;
    int n = a;
    for (; n; c1++) {
        n &= (n - 1);   
    }

    unsigned int c2 = 0;
    n = b;
    for (; n; c2++) {
        n &= (n - 1);   
    }

    
    return c1 < c2;
}

int
main()
{   
    std::vector<int> v(std::istream_iterator<int>{cin}, std::istream_iterator<int >{});

    std::stable_sort(v.begin(), v.end(), comp);

    for (auto n : v) {
        cout << n << endl;
    }   

}
