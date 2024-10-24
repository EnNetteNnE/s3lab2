#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

struct TreeNode {
    int value;
    int height;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const int val) : value(val), height(1), left(nullptr), right(nullptr) {}
};

struct Tree {
    TreeNode* head;
    Tree() : head(nullptr) {}

    // Функция для получения высоты узла
    int height(TreeNode* node) {
        return node == nullptr ? 0 : node->height;
    }

    // Функция для обновления высоты узла
    void updateHeight(TreeNode* node) {
        if (node != nullptr) {
            node->height = max(height(node->left), height(node->right)) + 1;
        }
    }

    // Вставка узла
    TreeNode* insert(TreeNode* node, int value) {
        if (node == nullptr) {
            return new TreeNode(value);
        }

        if (value < node->value) {
            node->left = insert(node->left, value);
        } else if (value > node->value) {
            node->right = insert(node->right, value);
        } else {
            return node;
        }
        return node;

    }

    // Метод вставки нового значения
    void insertNum(int value) {
        head = insert(head, value);
    }

    // Удаление узла
    TreeNode* remove(TreeNode* node, int value) {
        if (node == nullptr) {
            return node;
        }

        // Находим узел для удаления
        if (value < node->value) {
            node->left = remove(node->left, value);
        } else if (value > node->value) {
            node->right = remove(node->right, value);
        } else {
            // Узел найден
            if (node->left == nullptr || node->right == nullptr) {
                TreeNode* temp = node->left ? node->left : node->right;
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                TreeNode* temp = getMinValueNode(node->right);
                node->value = temp->value;
                node->right = remove(node->right, temp->value);
            }
        }

        if (node == nullptr) {
            return node;
        }
        return node;

    }

    // Получение минимального значения узла
    TreeNode* getMinValueNode(TreeNode* node) {
        TreeNode* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    // Метод удаления узла по значению
    void removeNum(int value) {
        head = remove(head, value);
    }

    // Поиск узла по значению
    TreeNode* search(TreeNode* node, int value) {
        if (node == nullptr || node->value == value) {
            return node;
        }

        if (value < node->value) {
            return search(node->left, value);
        } else {
            return search(node->right, value);
        }
    }

    // Метод поиска узла по значению
    TreeNode* find(int value) {
        return search(head, value);
    }

    void serializeNode(TreeNode* node, string& result) {
        if (node == nullptr) {
            result += "#-";  // символ для обозначения null
            return;
        }
        result += to_string(node->value) + "-";  // записываем значение узла
        serializeNode(node->left, result);           // левое поддерево
        serializeNode(node->right, result);          // правое поддерево
    }

    string serialize() {
        string result;
        serializeNode(head, result);
        return result;
    }

    void unserialize(const string& data) {
        istringstream ss(data);  // используем строковый поток для работы с данными
        head = unserializeSS(ss);  // восстанавливаем дерево из потока
    }

    // Рекурсивная функция для восстановления дерева
    TreeNode* unserializeSS(istringstream& ss) {
        string val;
        getline(ss, val, '-');

        if (val == "#") {
            return nullptr;  // если встречаем символ пустого узла, возвращаем nullptr
        }

        TreeNode* node = new TreeNode(stoi(val));  // создаём новый узел
        node->left = unserializeSS(ss);              // восстанавливаем левое поддерево
        node->right = unserializeSS(ss);             // восстанавливаем правое поддерево

        return node;
    }
};

// Функция для печати дерева
void printTree(string& result, TreeNode* tree, int depth = 0, string prefix = "") {
    if (tree == nullptr) {
        return;
    }

    // Выводим правое поддерево (расположено выше в консоли)
    if (tree->right != nullptr) {
        printTree(result, tree->right, depth + 1, prefix + "\t");
    }

    // Выводим текущий узел с отступом
    result += prefix;
    if (depth > 0) {
        result += "───";
    }
    result += "[" + to_string(tree->value) + "]\n";

    // Выводим левое поддерево (расположено ниже в консоли)
    if (tree->left != nullptr) {
        printTree(result, tree->left, depth + 1, prefix + "\t");
    }
}

ostream& operator<<(ostream& os, const Tree& tree) {
    string stringTree = "";
    printTree(stringTree, tree.head);
    os << stringTree;
    return os;
}

#endif