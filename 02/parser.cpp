#include <string>
#include <vector>
#include <stdint.h>
#include <iostream>
#include "parser.h"

void TokenParser::SetStartCallback(std::function<void()> start)
{
    StartCallback = start;
}

void TokenParser::SetEndCallback(std::function<void()> fin)
{
    EndCallback = fin;
}

void TokenParser::SetDigitCallback(std::function<void(uint64_t num)> dig)
{
    DigitCallback = dig;
}

void TokenParser::SetStringCallback(std::function<void(std::string &s)> str)
{
    StringCallback = str;
}

void TokenParser::CallDigitCallback(uint64_t num, std::vector<uint64_t> &digits) 
{
    digits.push_back(num);
    if (DigitCallback != nullptr) {
        DigitCallback(num);
    } else {
        std::cout << "DigitCallback was not declared" << std::endl;
    }
}

void TokenParser::CallStringCallback(std::string &s, std::vector<std::string> &ss)
{
    ss.push_back(s);
    if (StringCallback != nullptr) {
        StringCallback(s);
    } else {
        std::cout << "StringCallback was not declared" << std::endl;
    }
}   

void TokenParser::parse(std::string &st, std::vector<uint64_t> &digits, std::vector<std::string> &ss)
{
    if (StartCallback != nullptr) {
        StartCallback();
    }

    uint64_t num = 0, cnt = 0;
    bool isword = false, isnumber = true;
    std::string tmp;
    std::cout << "The string is: " << st << std::endl;
    for (auto c: st) {
        cnt++;
        if (!(std::isspace(c))) {
            tmp += c;
            isword = true;
            if (isnumber && std::isdigit(c)) {
                num *= 10;
                num += c - '0';
            } else {
                isnumber = false;
            }
            if (cnt == st.size()) {
                if (isnumber) {
                    CallDigitCallback(num, digits);
                } else {
                    CallStringCallback(tmp, ss);
                }
            }
        } else {
            if (isword && isnumber) {
                CallDigitCallback(num, digits);
                isword = false;
            } else if (isword) {
                CallStringCallback(tmp, ss);
                isword = false;
            }
            tmp = "";
            num = 0;
            isnumber = true;
        }
    }

    if (EndCallback != nullptr) {
        EndCallback();
    }
}
