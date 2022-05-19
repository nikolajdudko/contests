#include <iostream>
#include <iomanip>


using std::cout;
using std::endl;

class C
{
    int v;
public:
    C(const int& x)
    {
        v = 2 * x;
    }
    
    C(const C& x)
    {
        v = 2 * x.get();
    }

    int
    get() const
    {
        return v;
    }

    const C operator+(const C& x) 
    {
        return C(v + x.get());
    }
};
