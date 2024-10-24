#ifndef SET_H
#define SET_H

#include <string>
#include <iostream>
#include <cstdint>
#include "M.hpp"

using namespace std;

struct Set {
private:
    struct Val {
        char value;
        Val* next;

        Val(int v) : value(v), next(nullptr) {}
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

    Set copy() const {
        Set newSet; // создаем новый экземпляр Set
        newSet.cap = cap; // устанавливаем новую емкость равной текущей
        newSet.len = len; // устанавливаем длину нового сета равной текущей
        newSet.loadFactor = loadFactor; // сохраняем текущий load factor

        // Создаем новый массив указателей
        newSet.data = new Val*[cap];
        for (int i = 0; i < cap; i++) {
            newSet.data[i] = nullptr; // инициализируем его нулями
        }

        // Копируем элементы из текущего сета
        for (int i = 0; i < cap; i++) {
            Val* current = data[i];
            while (current != nullptr) {
                // Копируем текущий элемент
                newSet.put(current->value); // используем put для добавления значения
                current = current->next;
            }
        }

        return newSet; // возвращаем новый экземпляр Set
    }

    void put(int value) {
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
                    current->value = value;
                    return;
                }
                current = current->next;
            }

            current->next = new Val(value); //новый элемент
        }

        len++;
    }

    char get(char value) const {
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

    bool contains(char value) {
        try {
            get(value);
            return true;
        } catch (runtime_error& e) {
            return false;
        }
        
    }

    void remove(char value) {
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

    uint32_t hash(int value) const {
        uint32_t hash = 5381;
        hash = ((hash << 5) + hash) + value;
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

    Vector<char> values() const {
        Vector<char> result;

        for (int i = 0; i < cap; i++) {
            Val* node = data[i];

            while (node != nullptr) {
                result.pushBack(node->value);
                node = node->next;
            }
        }

        return result;
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