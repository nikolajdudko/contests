#include <iomanip>
#include <iostream>
#include <boost/date_time.hpp>


using namespace boost::gregorian;
using boost::gregorian::greg_month;

template<typename T>
T my_abs(const T& a) {
    if (a.is_negative()) {
        return -a;
    } else {
        return a;
    }
}

date my_from_string(std::string& s) {
    int y, m, d;
    sscanf(s.c_str(), "%d-%d-%d", &y, &m, &d);
    return date(y, m, d);
}


int
main()
{
    std::string s;
    std::cin >> s;
    if (std::cin.eof()) {
        return 0;
    }
    date tmp1 = my_from_string(s);
    date tmp2;
    date_duration ans;

    std::cin >> s;
    while (!std::cin.eof()) {
        tmp2 = my_from_string(s);
        ans += my_abs(tmp1 - tmp2);
        tmp1 = tmp2;
        std::cin >> s;
    }

    std::cout << ans << std::endl;

}
