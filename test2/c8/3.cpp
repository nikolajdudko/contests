#include "2.cpp"
#include <vector>
#include <map>
#include <functional>
#include <sstream>
#include <algorithm>
#include <memory>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using std::istringstream;
using std::string;

class F {
    F() {}
public:
    static F* obj;
    std::map<const char, std::function<Figure*(istringstream&)>> func {
            {'R', [](istringstream& s){ string s1, s2; s>>s1>>s2; return Rectangle::make(s1 + " " + s2); }},
            {'C', [](istringstream& s){ string s1; s >> s1; return Circle::make(s1); }},
            {'S', [](istringstream& s){ string s1; s >> s1; return Square::make(s1); }}
    };

    Figure* operator()(const std::string& s) {
        istringstream ist(s);
        char c;
        ist >> c;
        return func[c](ist);
    }

    static F& factory_instance() {
        if (obj) {
            return *obj;
        }
        obj = new F();
        return *obj;
    }

    static void destroy() {
        delete obj;
    }
};

F* F::obj = nullptr;

bool comp(const std::unique_ptr<Figure>& a, const std::unique_ptr<Figure>& b) {
    return a->get_square() < b->get_square();
}

int main() {
    F g = F::factory_instance();
    string s;
    std::vector<std::unique_ptr<Figure>> v;

    while (std::getline(std::cin, s)) {
        v.push_back(std::unique_ptr<Figure>(g(s)));    
    }
    F::destroy();

    std::stable_sort(v.begin(), v.end(), comp);

    for (auto& i : v) {
        std::cout << i->to_string() << std::endl;
    }
}
