#ifndef STRING_H
#define STRING_H
#include <iostream>
#include "M.hpp"

using namespace std;

Vector<string> split(string str, char delimiter) {
    Vector<string> vec;
    int lastSpace = -1;

    for (int i = 0; i < str.size(); i++) {
        if(str[i] == delimiter) {
            vec.pushBack(str.substr(lastSpace+1, i-lastSpace-1));
            lastSpace = i;
        }
    }
    vec.pushBack(str.substr(lastSpace+1, str.size()-lastSpace));

    return vec;
}

string join(const Vector<string>& array, char delimiter) {
    string result;
    for (int i = 0; i < array.size(); i++) {
        result += array.get(i);
        if (i < array.size() - 1) {
            result += delimiter;
        }
    }
    return result;
}

#endif