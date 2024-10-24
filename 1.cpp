#include <iostream>
//#include <stack>
#include <sstream>
#include <cctype>
//#include <unordered_map>

#include "S.hpp"

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*') return 2;
    return 0;
}

int applyOperation(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        //case '/': return a / b; // Предполагается, что деление на ноль не произойдет
    }
    return 0;
}

int evaluate(const std::string& expression) {
    Stack<int> values;
    Stack<char> ops;

    int dig = 0;
    for (char i : expression) {
        if (isdigit(i)) {
            dig++;
            break;
        }
    }
    if (dig == 0) {
        std::cout << "Нет чисел\n";
        return 0;
    }
    
    for (int i = 0; i < expression.length(); i++) {       
        int in = 0;
        while (i < expression.length()) {
            if (isspace(expression[i]) and in == 1) in = 2;
            else if (isdigit(expression[i]) and in == 0) in = 1;
            else if (isdigit(expression[i]) and in == 2) {
                std::cout << "Пробел в числе\n";
                return 0;
            }
            else {
                in = 0;
                break;
            }
            i++;
        }     
    }

    int op = 0;
    int cl = 0;
    for (char i : expression) {
        if (i == '(') op++;
        if (i == ')') cl++;
    }
    if (op != cl) {
        std::cout << "Лишние скобки\n";
        return 0;
    }


    for (size_t i = 0; i < expression.length(); ++i) {
        // Пропускаем пробелы
        if (isspace(expression[i])) continue;

        // Если текущий символ - число
        if (isdigit(expression[i])) {
            int value = 0;
            while (i < expression.length() && isdigit(expression[i])) {
                value = value * 10 + (expression[i] - '0');
                i++;
            }
            values.push(value);
            i--; // Уменьшаем индекс, чтобы учесть последний инкремент
        }
        // Если текущий символ - открывающая скобка
        else if (expression[i] == '(') {
            ops.push(expression[i]);
        }
        // Если текущий символ - закрывающая скобка
        else if (expression[i] == ')') {
            while (!ops.empty() && ops.get(0) != '(') {
                int val2 = values.get(0); values.pop();
                int val1 = values.get(0); values.pop();
                char op = ops.get(0); ops.pop();
                values.push(applyOperation(val1, val2, op));
            }
            ops.pop(); // Удаляем '(' из стека
        }
        // Если текущий символ - оператор
        else if (expression[i] == '+' or expression[i] == '-' or expression[i] == '*'){
            while (!ops.empty() && precedence(ops.get(0)) >= precedence(expression[i])) {
                int val2 = values.get(0); values.pop();
                int val1 = values.get(0); values.pop();
                char op = ops.get(0); ops.pop();
                values.push(applyOperation(val1, val2, op));
            }
            ops.push(expression[i]);
        }
        else {
            std::cout << "Неизвестные символы\n";
            return 0;
        }
    }

    // Обрабатываем оставшиеся операции в стеке
    while (!ops.empty()) {
        int val2 = values.get(0); values.pop();
        int val1 = values.get(0); values.pop();
        char op = ops.get(0); ops.pop();
        values.push(applyOperation(val1, val2, op));
    }

    return values.get(0);
}

int main() {
    std::string expression;
    std::cout << "Введите числовое выражение: ";
    std::getline(std::cin, expression);

    try {
        int result = evaluate(expression);
        std::cout << "Результат: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
