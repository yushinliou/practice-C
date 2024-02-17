#include <iostream>
#include <string>
#include <stack>
#include <cmath>
# include <vector>
using namespace std;

string replaceNegativeOperators(const string& expression) {
    string result = expression;
    size_t pos = result.find("--");
    
    while (pos != std::string::npos) {
        result.replace(pos, 2, "+");  // Replace "--" with "+"
        pos = result.find("--", pos + 1);
    }
    
    return result;
}


string replacePowerOperator(const string& input) {
    string output = input;
    size_t pos = output.find("**");
    
    while (pos != string::npos) {
        output.replace(pos, 2, "^");
        pos = output.find("**", pos + 1);
    }
    
    return output;
}

int getPrecedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')
        return 3;
    if (op == '(' || op == ')')
        return 4;
    return 0;
}

int performOperation(int num1, int num2, char op) {
    switch (op) {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/': return (num2 != 0) ? (num1 / num2) : 0;
        case '^':
            if (num2 > 0) {
                return pow(num1, num2);
            } else if (num2 == 0) {
                return (num1 >= 0) ? 1 : -1;
            } else {
                return 0;
            }
        default: return 0;
    }
}

int evaluateExpression(const string& expression) {
    stack<int> values;
    stack<char> operators;
    int i = 0;
    int value = 0;
    while (i < expression.length()) {
        char ch = expression[i];
        
        if (ch == ' ') {
            i++;
            continue;
        }
        
        if (isdigit(ch) || (ch == '-' && i == 0) || (ch == '-' && !isdigit(expression[i-1]) && (expression[i-1] != ')'))) {
            int num = 0;
            int sign = 1;

            if (ch == '-') {
                sign = -1;
                i++;
            }

            while (i < expression.length() && isdigit(expression[i])) {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            i--;
            values.push(sign * num);
        }
        else if (ch == '(') {
            operators.push(ch);
        }
        else if (ch == ')') {
            while (!operators.empty() && operators.top() != '(') {
                int num2 = values.top();
                values.pop();

                int num1 = values.top();
                values.pop();

                char op = operators.top();
                operators.pop();
                // cout << num1 << " " << num2 << " " << op << endl;
                int result = performOperation(num1, num2, op);
                values.push(result);
            }

            if (!operators.empty() && operators.top() == '(') {
                operators.pop(); // Discard the '('
            }
        }
        else {
            while (!operators.empty() && getPrecedence(operators.top()) >= getPrecedence(ch) && operators.top() != '(') {
                int num2 = values.top();
                values.pop();

                int num1 = values.top();
                values.pop();

                char op = operators.top();
                operators.pop();
                //cout << num1 << " " << num2 << " " << op << endl;
                int result = performOperation(num1, num2, op);
                values.push(result);
            }
            operators.push(ch);
        }
        i++;
    }

    while (!operators.empty()) {
        int num2 = values.top();
        values.pop();

        int num1 = values.top();
        values.pop();

        char op = operators.top();
        operators.pop();
        // cout << num1 << " " << num2 << " " << op << endl;
        int result = performOperation(num1, num2, op);
        values.push(result);
    }

    return values.top();
}

int main() {

    string expression;
    vector<int> results;
    while (cin >> expression) {
        expression = replacePowerOperator(expression);
        expression = replaceNegativeOperators(expression);
        int result = evaluateExpression(expression);
        results.push_back(result);
    }
    // cout outcome
    for (int i = 0; i < results.size(); i++){
        cout << results[i] << endl;
    }

    return 0;
}
