#ifndef FILEREAD_H
#define FILEREAD_H
#include <iostream>
#include <fstream>
#include <regex>

#include "M.hpp"
#include "help.hpp"
#include "SET.hpp"

using namespace std;

const string FILENAME = "file.data";

Set readSet(string name) {
    Set set;

    ifstream file(FILENAME);

    if (!file.is_open()) {
        throw runtime_error("Error opening file");
    }

    string line;
    
    bool isArray = false;
    while (getline(file, line)) {
        if (line == "Set") {
            isArray = true;
        } else if (line == "" && isArray) {
            break;
        } else if (isArray) {
            Vector<string> splittedLine = split(line, ' ');

            if (splittedLine.size() != 2) {
                continue;
            }

            if (splittedLine.get(0) == name) {
                Vector<string> array = split(splittedLine.get(1), ','); // делим по точке-запятой второй аргумент
                if (array.size() == 1 && array.get(0) == "") { // при пустой строке создаётся массив с пустой строкой, надо удалить эту строку, чтоб сделать пустой массив
                    array.remove(0);
                } else {
                    for (int i = 0; i < array.size(); i++) {
                        string value = array.get(i);
                        set.put(value);
                    }
                }
                
                return set;
            }
        }
    }

    file.close();

    return set;
}

#endif