#ifndef SETMENU_H
#define SETMENU_H

#include "SET.hpp"
#include "FR.hpp"
#include "FW.hpp"

const string SET_SECTION = "Set";

void setMenu(Vector<string> arguments) {
    string command = arguments.get(0);

    if (command == "SETADD") {
        if (arguments.size() != 3) {
            throw runtime_error("incorrect count of arguments");
        }
        string name = arguments.get(1);
        string value = arguments.get(2);

        Set set = readSet(name);
        set.put(value);
        save(SET_SECTION, name, name + " " + set.join());
    } 
    else if (command == "SETDEL") {
        if (arguments.size() != 3) {
            throw invalid_argument("incorrect count of arguments");
        }
        string name = arguments.get(1);
        string value = arguments.get(2);

        Set set = readSet(name);
        set.remove(value);
        save(SET_SECTION, name, name + " " + set.join());
    } 
    else if (command == "SET_AT") {
        if (arguments.size() != 3) {
            throw invalid_argument("incorrect count of arguments");
        }
        string name = arguments.get(1);
        string value = arguments.get(2);

        Set set = readSet(name);
        cout << set.contains(value) << endl;
        save(SET_SECTION, name, name + " " + set.join());
    } 
    else if (command == "SETPRINT") {
        if (arguments.size() != 2) {
            throw invalid_argument("incorrect count of arguments");
        }
        string name = arguments.get(1);

        Set set = readSet(name);
        cout << set << endl;
    }
}

#endif