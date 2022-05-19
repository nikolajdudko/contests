#include <iomanip>
#include <iostream>


int
main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int i;

    std::cin >> i;

    while (!std::cin.eof()) {
        std::cout << i << std::endl;
        std::cin >> i;
    }
}
