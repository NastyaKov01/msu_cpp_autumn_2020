#pragma once
#include <functional>
#include <string>
#include <vector>
#include <cstdint>

class TokenParser
{
    std::function <void()> StartCallback;
    std::function <void()> EndCallback;
    std::function <void(uint64_t num)> DigitCallback;
    std::function <void(std::string &str)> StringCallback;
public:
    TokenParser():
        StartCallback(nullptr), EndCallback(nullptr),
        DigitCallback(nullptr), StringCallback(nullptr) {}
    ~TokenParser() {}
    void SetStartCallback(std::function<void()> start);
    void SetEndCallback(std::function<void()> fin);
    void SetDigitCallback(std::function<void(uint64_t num)> dig);
    void SetStringCallback(std::function<void(std::string &s)> str);
    void CallDigitCallback(uint64_t num, std::vector<uint64_t> &digits);
    void CallStringCallback(std::string &s, std::vector<std::string> &ss);
    void parse(std::string &st, std::vector<uint64_t> &d, std::vector<std::string> &ss);
};
