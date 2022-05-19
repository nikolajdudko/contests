#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>

using std::string;
using std::cout;
using std::cin;
using std::endl;

string s;

bool
comp(std::pair<std::string::iterator, int> x, std::pair<std::string::iterator, int> y)
{
    auto a = x.first;
    auto b = y.first;

    /*
    auto n = x;
    while (n.first != s.end()) {
        cout << *(n.first)++;
    }
    cout << "  :  ";
    n = y;
    while (n.first != s.end()) {
        cout << *(n.first)++;
    }

    cout << endl;
    */
    while (a != s.end()  && b != s.end()) {
        if (*a > *b) {
            return false;
        } else if (*a < *b) {
            return true;
        } else {
            a++;
            b++;
        }
    }
    return b != s.end();
}

int main()
{
    std::getline(std::cin, s);
    size_t i, strEnd = s.find_last_not_of(' ');
    if (strEnd == std::string::npos) {
        return 0;
    }   
    while ((i = s.find(' ', strEnd)) != std::string::npos) {
        s.erase(i);
    }

    std::vector<std::pair<std::string::iterator, int>> v;
    string::iterator it = s.begin();
    int j = 0;
    while (it != s.end()) {
        v.emplace_back(make_pair(it++, j++));
    }

    
    
    for (auto n : v) {
        while (n.first != s.end()) {
            cout << *(n.first)++;
        }
        cout << endl;
    }
    

    std::sort(v.begin(), v.end(), comp);    

    
    cout << endl;
    for (auto n : v) {
        while (n.first != s.end()) {
            cout << *(n.first)++;
        }
        cout << endl;
    }
    cout << endl;


    for (auto n : v) {
        cout << n.second << endl;
    }   

}
