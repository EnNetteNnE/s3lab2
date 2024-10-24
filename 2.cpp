#include <iostream>
#include "M.hpp"
//#include "SET.hpp"
#include "help.hpp"
#include "_2_.hpp"

using namespace std;

int main() {
    string str;

    while (true) {
        cout << ">> ";
        getline(cin, str);

        Vector<string> splitedStr = split(str, ' ');
        string command = splitedStr.get(0);


        if (command.substr(0, 3) == "SET") {
            try {
                setMenu(splitedStr);
            } 
            catch (runtime_error& e) {
                cerr << e.what() << endl;
            }
        } 
        
        else {
            cerr << "Unknown command" << endl;
        }
    }

    return 0;
}