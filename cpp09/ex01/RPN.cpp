#include "RPN.hpp"

RPN::RPN():result(0){}

RPN::RPN(const char *s):result(calcul(s)){}

RPN::RPN(const RPN &other): result(other.result){}

RPN::~RPN(){};

RPN &RPN::operator=(const RPN& other)
{
    if (this != &other)
    {
        this->result = other.result;
    }
    return *this;
}

static bool isOperator(char c)
{
    if (c == '-' || c == '+' || c == '*' || c == '/')
        return true;
    return false;
}
static int aplicOperator(int a, int b, char op)
{
    if (op == '-')
        return a - b;
    if (op == '+')
        return a + b;
    if (op == '*')
        return a * b;
    if (b == 0)
        throw std::runtime_error("Division by zero!!!");
    return a / b;
}

int RPN::getResult() const
{
    return result;
}

int RPN::calcul(const char *s)
{
    std::stack<int> stk;
    int i = 0;

    for (; s[i] == ' '; i++);
    for (; s[i]; i++)
    {
        if (isdigit(s[i]))
            stk.push(s[i] - '0');
        else if (isOperator(s[i]))
        {
            if (stk.size() < 2)
                throw std::runtime_error("Invalid input");
            int b = stk.top();
            stk.pop();
            int a = stk.top();
            stk.pop();
            stk.push(aplicOperator(a, b, s[i]));
        }
        else if (s[i] == ' ')
            for (; s[i + 1] == ' '; i++);
        else
            throw std::runtime_error("Invalid input");
    }
    if (stk.size() > 1)
        throw std::runtime_error("Invalid input");
    return stk.top();
}