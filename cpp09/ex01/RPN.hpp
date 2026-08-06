#pragma once
#include <stack>
#include <iostream>
#include <stdexcept>

class RPN
{
    private:
        int result;
        public:
        RPN();
        RPN(const char *s);
        RPN(const RPN &other);
        ~RPN();
        RPN &operator=(const RPN &other);
        int getResult() const;
        static int calcul(const char *s);
};

