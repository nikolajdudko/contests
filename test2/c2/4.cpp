#include <iostream>
#include <iomanip>

using std::cin;
using std::cout;
using std::hex;
using std::endl;


void
print(const char& s, int& qw) {
    if (qw <= 4 && s != '#') {
        while (qw-- != 0) {
            cout << s;
        }
    } else {
        cout << '#' << s << hex << qw << '#';
    }
    qw = 1;
}

int
main(void) {
    int i = 1;
    char x = 'a';
    char y = 'b';
    cin.get(y);
    if (cin.eof()) {
        return 0;
    }
    while (cin.get(x) && !cin.eof()) {
        if (x == y) {
            ++i;
        } else {
            print(y, i);
        }
        y = x;  
    }
    print(y, i);

    return 0;
}
