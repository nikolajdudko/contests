#include <iostream>
#include <iomanip>
#include <cmath>

using std::cin;
using std::cout;
using std::hex;
using std::endl;

unsigned long long int*
read_number()
{
    unsigned long long int *x = new unsigned long long int;
    unsigned long long int b = 0;
    *x = 0;
    for (int i = 3; i >= 0; --i) {
        cin >> hex >> b;
        if (cin.eof()) {
            delete x;
            return NULL;
        }
        *x += b << (i * 8);
    }
    return x;
}

int main()
{
    unsigned long long int *ans = 0;
    int x;

    while (1) {
        cin >> x;
        if (cin.eof()) {
            return 0;
        }
        for (int j = 0; j < 4; ++j) {
            ans = read_number();
            if (ans == NULL) {
                return 0;
            } 
            cout << *ans << endl;
            delete ans;
        }
    }
}
