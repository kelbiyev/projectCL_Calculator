#include <iostream>
#include <sstream>
#include <stack>
#include <cctype>
#include <cmath>
#include <stdexcept>

// Function to check operator precedence
int precedence(char op) {
    if (op == '^') return 3;  // Power has the highest precedence
    if (op == '*' || op == '/') return 2;  // Multiplication and division
    if (op == '+' || op == '-') return 1;  // Addition and subtraction
    return 0;
}

// Function to perform arithmetic operations
double applyOperation(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) {
                throw std::runtime_error("Division by zero!");
            }
            return a / b;
        case '^':
            if (b == 0) return 1; // a^0 = 1 for all a
            return std::pow(a, b);
        default: return 0;
    }
}

// Function to evaluate an expression
double evaluate(const std::string& expression) {
    std::stack<double> values;  // Stack for numbers
    std::stack<char> operators;  // Stack for operators

    for (size_t i = 0; i < expression.length(); i++) {
        // Skip whitespace
        if (std::isspace(expression[i])) {
            continue;
        }

        // If the character is a number or decimal point
        if (std::isdigit(expression[i]) || expression[i] == '.') {
            std::stringstream ss;
            while (i < expression.length() && (std::isdigit(expression[i]) || expression[i] == '.')) {
                ss << expression[i++];
            }
            i--; // Move one character back
            double val;
            ss >> val;
            values.push(val);
        }
        // If the character is an operator
        else if (expression[i] == '+'|| expression[i] == '-' ||expression[i] == '*' || expression[i] == '/' || expression[i] == '^') {
            while (!operators.empty() && precedence(operators.top()) >= precedence(expression[i])) {
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();
                char op = operators.top(); operators.pop();
                values.push(applyOperation(a, b, op));
            }
            operators.push(expression[i]);
        } else {
            throw std::runtime_error("Invalid character in expression!");
        }
    }

    // Process remaining operators
    while (!operators.empty()) {
        double b = values.top(); values.pop();
        double a = values.top(); values.pop();
        char op = operators.top(); operators.pop();
        values.push(applyOperation(a, b, op));
    }

    return values.top();
}

int main() {
    std::cout << "Calculator. Enter an expression (e.g., 25*3/5).\n";
    std::cout << "Type 'q' to exit.\n";

    while (true) {
        try {
            std::string input;
            std::cout << "Enter expression: ";
            std::getline(std::cin, input);

            if (input == "q") {
                std::cout << "Exiting program.\n";
                break;
            }

            double result = evaluate(input);
            std::cout << "Result: " << result << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << ". Try again.\n";
        }
    }

    return 0;
}