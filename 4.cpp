#include <iostream>
#include <algorithm>

#include "M.hpp"

void generateSubsets(const Vector<int>& arr, Vector<int>& current, int index, Vector<Vector<int>>& subsets) {
    // Добавляем текущий набор в множество
    subsets.pushBack(current);
    std::cout << "{ ";
    for (int i = 0; i < current.size(); i++) std::cout << current.get(i) << " ";
    std::cout << "}  ";

    for (int i = index; i < arr.size(); ++i) {
        // Добавляем элемент в текущий набор
        current.pushBack(arr.get(i));
        // Рекурсивно генерируем подмножества с добавленным элементом
        generateSubsets(arr, current, i + 1, subsets);
        // Убираем последний добавленный элемент для генерации других наборов
        current.remove(current.size() - 1);
    }
}

int main() {
    Vector<int> arr; // Пример массива
    arr.pushBack(1);
    arr.pushBack(2);
    arr.pushBack(3);
    arr.pushBack(4);
    Vector<Vector<int>> subsets; // Множество для хранения различных наборов
    Vector<int> current; // Текущий набор

    std::cout << "Различные наборы элементов:\n";
    generateSubsets(arr, current, 0, subsets);
    std::cout << "\n";

    return 0;
}