#pragma once
#include <functional>

class TokenParser
{
    std::function <void()> StartCallback;
    std::function <void()> EndCallback;
    std::function <void(uint64_t num)> DigitCallback;
    std::function <void(std::string str)> StringCallback;
public:
    TokenParser():
        StartCallback(nullptr), EndCallback(nullptr),
        DigitCallback(nullptr), StringCallback(nullptr) {}
    ~TokenParser() {}
    void SetStartCallback(std::function<void()> start);
    void SetEndCallback(std::function<void()> fin);
    void SetDigitCallback(std::function<void(uint64_t num)> dig);
    void SetStringCallback(std::function<void(std::string s)> str);
    void parse(std::string st, std::vector<uint64_t> &d, std::vector<std::string> &ss);
};
