#include <iostream>
#include <iomanip>

using std::cin;
using std::cout;
using std::hex;
using std::endl;
using std::string;

class BinaryNumber
{
    string x;
public:
    BinaryNumber(const string &s)
    {
        x = string(s);
    }

    string get() 
    {
        return x;
    }


    operator string () const 
    {
        return x;
    }


    const BinaryNumber &operator++()
    {
        int j = 1, i = x.size() - 1;
        while (j && i >= 0) {
            if (x[i] == '1') {
                x[i] = '0';
            } else {
                x[i] = '1';
                j--;
            }
            i--;
        }
        if (i == -1) {
            x.insert(x.begin(), '1');
        }
        return *this;
    }
};
