#include <iostream>
#include <algorithm>

#include "H.hpp"

using namespace std;


bool izo(string s1, string s2) {
    Map<char> hash;

    for (int i = 0; i < s1.size(); i++) {
        string k;
        k.push_back(s1[i]);
        hash.put(k, s2[i]);
    }

    string sTry;
    for (int i = 0; i < s1.size(); i++) {
        string k;
        k.push_back(s1[i]);
        sTry.push_back(hash.get(k));
    }

    if (s2 == sTry) {
        return true;
    }
    return false;
}


int main() {
    string str1 = "fall";
    string str2 = "redd";

    if (str1.size() != str2.size()) {
        cout << "не изоморфны\n";
    }
    else {
        if (izo(str1, str2) and izo(str2, str1)) {
            cout << "изоморфны\n";
        }
        else cout << "не изоморфны\n";
    }

    return 0;
}