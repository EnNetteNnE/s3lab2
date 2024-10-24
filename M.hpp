#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

using namespace std;

template <typename T>
struct Vector {
private:
    T* data;           
    int len;           
    int cap;           
    float loadFactor;  

public:
    Vector(int initCap = 16, int initLen = 0) {
        cap = initCap;
        len = 0;
        data = new T[cap];
        loadFactor = 0.5;
    }

    int size() const {
        return len;
    }

    void extend() {
        int newCap = cap * 2;
        T* newData = new T[newCap];
        for (int i = 0; i < cap; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        cap = newCap;
    }

    void pushBack(T value) {
        if (static_cast<float>(len)/cap >= loadFactor) {
            extend();
        }
        data[len] = value;
        len++;
    }

    void insert(int index, T value) {
        if (static_cast<float>(len)/cap >= loadFactor) {
            extend();
        }
        for (int i = len; i > index; i--) {
            data[i] = data[i - 1]; 
        }
        data[index] = value;
        len++;
    }

    void remove(int index) {
        if (index < 0 || index >= len) {
            throw invalid_argument("invalid index");
        }
        
        for (int i = index; i < len - 1; i++) {
            data[i] = data[i + 1];
        }
        len--;
    }

    void set(int index, T value) {
        if (index < 0 || index >= len) {
            throw invalid_argument("invalid index");
        }
        data[index] = value;
    }

    void reverse() {
        for (int i = 0; i < len / 2; i++) {
            T temp = data[i];
            data[i] = data[len - i - 1];
            data[len - i - 1] = temp;
        }
    }

    void sort() {
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                if (data[i] < data[j]) {
                    T temp = data[i];
                    data[i] = data[j];
                    data[j] = temp;
                }
            }
        }
    }

    T get(int index) const {
        if (index < 0 || index >= len) {
            throw invalid_argument("invalid index");
        }

        return data[index];
    }
};

template <typename T>
ostream& operator<<(ostream& os, const Vector<T>& vec) {
    for (int i = 0; i < vec.size(); i++) {
        os << vec.get(i);
        if (i != vec.size() - 1) {
            os << ",";
        }
    }
    //os << endl;
    return os;
}

#endif