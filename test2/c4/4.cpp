#include <iostream>
int main()
{
    int count;
    std::cin >> count;
    Holder y[count];

    for (int i = 0; i < count / 2; ++i) {
        y[i].swap(y[count - i - 1]);
    }

}
