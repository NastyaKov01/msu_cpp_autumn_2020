#include <string>
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

void TokenParser::SetStringCallback(std::function<void(std::string s)> str)
{
    StringCallback = str;
}

void TokenParser::parse(std::string st, std::vector<uint64_t> &d, std::vector<std::string> &ss)
{
    if (StartCallback != nullptr) {
        StartCallback();
    }

    uint64_t num = 0, cnt = 0;
    bool f = false, n = true;
    std::string tmp;
    std::cout << "The string is: " << st << std::endl;
    for (auto c: st) {
        cnt++;
        if (!(std::isspace(c))) {
            tmp += c;
            f = true;
            if (n && std::isdigit(c)) {
                num *= 10;
                num += c - '0';
            } else {
                n = false;
            }
            if (cnt == st.size()) {
                if (n) {
                    d.push_back(num);
                    if (DigitCallback != nullptr) {
                        DigitCallback(num);
                    } else {
                        std::cout << "DigitCallback was not declared" << std::endl;
                    }
                } else {
                    ss.push_back(tmp);
                    if (StringCallback != nullptr) {
                        StringCallback(tmp);
                    } else {
                        std::cout << "StringCallback was not declared" << std::endl;
                    }
                }
            }
        } else {
            if (f && n) {
                d.push_back(num);
                if (DigitCallback != nullptr) {
                    DigitCallback(num);
                } else {
                    std::cout << "DigitCallback was not declared" << std::endl;
                }
                f = false;
            } else if (f) {
                ss.push_back(tmp);
                if (StringCallback != nullptr) {
                    StringCallback(tmp);
                } else {
                    std::cout << "StringCallback was not declared" << std::endl;
                }
                f = false;
            }
            tmp = "";
            num = 0;
            n = true;
        }
    }

    if (EndCallback != nullptr) {
        EndCallback();
    }
}
