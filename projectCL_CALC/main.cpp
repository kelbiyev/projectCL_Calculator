#include <iostream>
#include <sstream>
#include <stack>
#include <cctype>
#include <string>

using namespace std;

// Проверка приоритета операций
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Выполнение арифметической операции
double applyOperation(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) {
                throw runtime_error("Деление на ноль!");
            }
            return a / b;
    }
    return 0;
}

// Вычисление выражения
double evaluate(const string& expression) {
    stack<double> values; // Стек для чисел
    stack<char> operators; // Стек для операторов

    for (size_t i = 0; i < expression.length(); i++) {
        // Пропускаем пробелы
        if (isspace(expression[i])) {
            continue;
        }

        // Если текущий символ — число
        if (isdigit(expression[i]) || expression[i] == '.') {
            stringstream ss;
            while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.')) {
                ss << expression[i++];
            }
            i--; // Вернуться назад на один символ
            double val;
            ss >> val;
            values.push(val);
        }
        // Если текущий символ — оператор
        else if (expression[i] == '+' || expression[i] == '*' || expression[i] == '/') {
            while (!operators.empty() && precedence(operators.top()) >= precedence(expression[i])) {
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();
                char op = operators.top(); operators.pop();
                values.push(applyOperation(a, b, op));
            }
            operators.push(expression[i]);
        } else {
            throw runtime_error("Неверный символ в выражении!");
        }
    }

    // Обработка оставшихся операторов
    while (!operators.empty()) {
        double b = values.top(); values.pop();
        double a = values.top(); values.pop();
        char op = operators.top(); operators.pop();
        values.push(applyOperation(a, b, op));
    }

    return values.top();
}

int main() {
    cout << "Калькулятор. Вводите выражение по символу (например, 25*3/5).\n";
    cout << "Для выхода введите 'q'.\n";

    while (true) {
        try {
            string input;
            cout << "Введите выражение: ";
            getline(cin, input);

            if (input == "q") {
                cout << "Выход из программы.\n";
                break;
            }

            double result = evaluate(input);
            cout << "Результат: " << result << endl;
        } catch (const exception& e) {
            cerr << "Ошибка: " << e.what() << ". Попробуйте снова." << endl;
        }
    }

    return 0;
}
