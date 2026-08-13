#include "RPN.hpp"

static bool isOperator(char c)
{
    if (c == '-' || c == '+' || c == '*' || c == '/')
        return true;
    return false;
}

static int calcul(int a, int b, char op)
{
    if (op == '-')
        return a - b;
    if (op == '+')
        return a + b;
    if (op == '*')
        return a * b;
    if (b == 0) // division by zero
        throw std::runtime_error("Division by zero.");
    return a / b;
}

int RPN(const char *s)
{
    std::stack<int> stk;
    int i = 0;

    for (; s[i] == ' '; i++);
    if (!s[i])
        throw std::runtime_error("Invalid input.");
    for (; s[i]; i++)
    {
        if (isdigit(s[i]))
            stk.push(s[i] - '0');
        else if (isOperator(s[i]))
        {
            if (stk.size() < 2)
                throw std::runtime_error("Invalid input.");
            int b = stk.top();
            stk.pop();
            int a = stk.top();
            stk.pop();
            stk.push(calcul(a, b, s[i]));
        }
        else if (s[i] == ' ')
            for (; s[i + 1] == ' '; i++);
        else
            throw std::runtime_error("Invalid input.");
    }
    if (stk.size() > 1)
        throw std::runtime_error("Invalid input.");
    return stk.top();
}
