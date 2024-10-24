#ifndef SET_H
#define SET_H

#include <string>
#include <iostream>
#include <cstdint>

using namespace std;

struct Set {
private:
    struct Val {
        string value;
        Val* next;

        Val(string v) : value(v), next(nullptr) {}
    };

    Val** data;// указатель на массив указателей
    int cap;
    int len;
    double loadFactor;

public:
    Set() {
        cap = 16;
        len = 0;
        loadFactor = 0.50;

        data = new Val*[cap];

        for (int i = 0; i < cap; i++) {
            data[i] = nullptr;
        }
    }

    Val** getData() const {
        return data;
    }

    int getLen() const {
        return len;
    }

    int getCap() const {
        return cap;
    }

    void put(string value) {
        if (static_cast<double>(len) / cap >= loadFactor) {
            rehash(cap * 2);
        }

        uint32_t index = hash(value) % cap;

        if (data[index] == nullptr) { // бакета нет
            data[index] = new Val(value);// создается новый элемент
        } else { // бакет есть -> добавляем в него
            Val* current = data[index];
            if (current->value == value) {
                current->value = value; // обновление значения
                return;
            }

            while (current->next != nullptr) {
                if (current->value == value) {
                    return;
                }
                current = current->next;
            }

            current->next = new Val(value); //новый элемент
        }

        len++;
    }

    string get(string value) const {
        uint32_t index = hash(value) % cap;

        Val* current = data[index];
        while (current != nullptr) {
            if (current->value == value) {
                return current->value;
            }
            current = current->next;
        }

        throw runtime_error("Value not found");
    }

    bool contains(string value) {
        try {
            get(value);
            return true;
        } catch (runtime_error& e) {
            return false;
        }
        
    }

    void remove(string value) {
        uint32_t index = hash(value) % cap;

        Val* prev = nullptr;
        Val* current = data[index];

        while (current != nullptr) {
            if (current->value == value) {
                if (prev == nullptr) {
                    data[index] = current->next;
                    delete current;
                    len--;
                    return;
                } else {
                    prev = current->next;
                    delete current;
                    len--;
                    return;
                }
            }
            prev = current;
            current = current->next;
        }

        throw runtime_error("Value not found");
    }

    uint32_t hash(string key) const {
        uint32_t hash = 5381;
        for (char c : key) {
            hash = ((hash << 5) + hash) + c;
        }
        return hash;
    }

    void rehash(int newcap) {
        Val** newSet = new Val*[newcap]; // новый массив бакетов увеличенного размера

        for (int i = 0; i < newcap; i++) {
            newSet[i] = nullptr;
        }

        for (int i = 0; i < cap; i++) {
            Val* current = data[i];
            while (current != nullptr) {
                Val* next = current->next;
                uint32_t newIndex = hash(current->value) % newcap;
                
                if (newSet[newIndex] == nullptr) { // бакета нет
                    current->next = nullptr;
                    newSet[newIndex] = current;
                } else { // бакет есть -> добавляем в него
                    Val* currentNewSet = newSet[newIndex];

                    while (currentNewSet->next != nullptr) {
                        currentNewSet = currentNewSet->next;
                    }
                    current->next = nullptr;
                    currentNewSet->next = current;
                }
                current = next;
            }
        }

        delete[] data;
        data = newSet;
        cap = newcap;
    }

    string join() {
        string result = "";

        for (int i = 0; i < cap; i++) {
            Val* current = data[i];
            while (current != nullptr) {
                result += current->value + ",";
                current = current->next;
            }
        }
        result = result.substr(0, result.size() - 1);
        return result;
    }
};

ostream& operator<<(ostream& os, const Set& set) {
    auto data = set.getData();
    for (int i = 0; i < set.getCap(); i++) {
        if (data[i] != nullptr) {
            auto current = data[i];
            while (current != nullptr) {
                os << current->value << ", ";
                current = current->next;
            }
        }
    }
    return os;
}

#endif