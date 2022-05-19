#include <iostream>
#include <map>
#include <iomanip> 
#include <sstream>
#include <set> 
class Date {
    int y = 0;
    int m = 0;
    int d = 0;
public:
    Date(std::string& s) 
    {
        sscanf(s.c_str(), "%d/%d/%d", &y, &m, &d);
    }

    std::string to_s() const
    {
        std::stringstream ss;
        ss << y << '/' << std::setfill('0') << std::setw(2) << m << '/' << std::setw(2) << d;
        return ss.str();
    }
};

int
main()
{   
    std::map<std::string, std::map<std::string, int>> m;
    std::set<std::string> v;
    std::string name, date;
    int n;

    std::cin >> name >> date >> n;
    while (!std::cin.eof()) {
        date = Date(date).to_s();
        v.insert(date);
        if (m.count(name)) {
            m[name][date] = n;
        } else {
            std::map<std::string, int> m1 = {{date, n}};
            m[name] = m1;
        }
        std::cin >> name >> date >> n;
    }
    
    std::cout << '.';
    for (auto& q : v) {
        std::cout << ' ' << q;
    } 
    std::cout << std::endl;

    for (auto& k : m) {
        std::cout << k.first;
        for (auto& q : v) {
            if (k.second.count(q)) {
                std::cout << ' ' << k.second[q];
            } else {
                std::cout << " .";
            }
        }
        std::cout << std::endl;
    }
}
