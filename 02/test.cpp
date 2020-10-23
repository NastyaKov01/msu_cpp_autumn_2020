#include <iostream>
#include "parser.h"

void MyStartCallback()
{
    std::cout << "Let's start the parsing." << std::endl;
}

void MyEndCallback()
{
    std::cout << "The parsing is finished." << std::endl;
}

void MyDigitCallback(uint64_t num)
{
    std::cout << "Digit = " << num << std::endl;
}

void MyStringCallback(std::string & st) 
{
    std::cout << "String = " << st << std::endl;
}

void Test1()
{
    std::cout << "Test1" << std::endl;
    TokenParser example;
    std::string s = "123 12ce lgkg12 \t *213 657574 0";
    std::vector<uint64_t> digits;
    std::vector<std::string> strings;
    std::vector<uint64_t> resdigits = {123, 657574, 0};
    std::vector<std::string> resstrings = {"12ce", "lgkg12", "*213"};
    example.SetStartCallback(MyStartCallback);
    example.SetEndCallback(MyEndCallback);
    example.SetDigitCallback(MyDigitCallback);
    example.SetStringCallback(MyStringCallback);
    example.parse(s, digits, strings);
    if (digits.size() == resdigits.size() && strings.size() == resstrings.size()) {
        size_t lend = digits.size(), lens = strings.size();
        std::cout << "Number of digits: " << lend << std::endl;
        std::cout << "Number of strings: " << lens << std::endl;
        for (size_t i = 0; i < lend; ++i) {
            if (digits[i] != resdigits[i]) {
                std::cout << "Wrong digit.";
            }
        }
        for (size_t i = 0; i < lens; ++i) {
            if (strings[i] != resstrings[i]) {
                std::cout << "Wrong string." << std::endl;
            }
        }

    } else {
        std::cout << "Missing or extra objects." << std::endl;
    }
    std::cout << std::endl;
}

void Test2()
{
    std::cout << "Test2" << std::endl;
    TokenParser example;
    std::string s = "fjdkdjgkdgn   178\n abc";
    std::vector<uint64_t> digits;
    std::vector<std::string> strings;
    std::vector<uint64_t> resdigits = {178};
    std::vector<std::string> resstrings = {"fjdkdjgkdgn", "abc"};
    example.SetStringCallback(MyStringCallback);
    example.parse(s, digits, strings);
    if (digits.size() == resdigits.size() && strings.size() == resstrings.size()) {
        size_t lend = digits.size(), lens = strings.size();
        std::cout << "Number of digits: " << lend << std::endl;
        std::cout << "Number of strings: " << lens << std::endl;
        for (size_t i = 0; i < lend; ++i) {
            if (digits[i] != resdigits[i]) {
                std::cout << "Wrong digit.";
            }
        }
        for (size_t i = 0; i < lens; ++i) {
            if (strings[i] != resstrings[i]) {
                 std::cout << "Wrong digit.";
            }
        }
        for (size_t i = 0; i < lens; ++i) {
            if (strings[i] != resstrings[i]) {
                std::cout << "Wrong string." << std::endl;
            }
        }

    } else {
        std::cout << "Missing or extra objects." << std::endl;
    }
    std::cout << std::endl;
}

void Test3()
{
    std::cout << "Test3" << std::endl;
    TokenParser example;
    std::string s = "578      klm ";
    std::vector<uint64_t> digits;
    std::vector<std::string> strings;
    std::vector<uint64_t> resdigits = {578};
    std::vector<std::string> resstrings = {"klm"};
    example.SetStartCallback(MyStartCallback);
    example.SetEndCallback(MyEndCallback);
    example.SetDigitCallback(MyDigitCallback);
    example.parse(s, digits, strings);
    if (digits.size() == resdigits.size() && strings.size() == resstrings.size()) {
        size_t lend = digits.size(), lens = strings.size();
        std::cout << "Number of digits: " << lend << std::endl;
        std::cout << "Number of strings: " << lens << std::endl;
        for (size_t i = 0; i < lend; ++i) {
            if (digits[i] != resdigits[i]) {
                std::cout << "Wrong digit.";
            }
        }
        for (size_t i = 0; i < lens; ++i) {
            if (strings[i] != resstrings[i]) {
                std::cout << "Wrong string." << std::endl;
            }
        }

    } else {
        std::cout << "Missing or extra objects." << std::endl;
    }
    std::cout << std::endl;
}

void Test4()
{
    std::cout << "Test4" << std::endl;
    TokenParser example;
    std::string s = "";
    std::vector<uint64_t> digits;
    std::vector<std::string> strings;
    std::vector<uint64_t> resdigits;
    std::vector<std::string> resstrings;
    example.SetStartCallback(MyStartCallback);
    example.SetEndCallback(MyEndCallback);
    example.SetDigitCallback(MyDigitCallback);
    example.SetStringCallback(MyStringCallback);
    example.parse(s, digits, strings);
    if (digits.size() == resdigits.size() && strings.size() == resstrings.size()) {
        size_t lend = digits.size(), lens = strings.size();
        std::cout << "Number of digits: " << lend << std::endl;
        std::cout << "Number of strings: " << lens << std::endl;
        for (size_t i = 0; i < lend; ++i) {
            if (digits[i] != resdigits[i]) {
                std::cout << "Wrong digit.";
            }
        }
        for (size_t i = 0; i < lens; ++i) {
            if (strings[i] != resstrings[i]) {
                std::cout << "Wrong string." << std::endl;
            }
        }

    } else {
        std::cout << "Missing or extra objects." << std::endl;
    }
    std::cout << std::endl;
}


int main()
{
    Test1();
    Test2();
    Test3();
    Test4();
    return 0;
}
