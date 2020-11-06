#pragma once
#include <iostream>
#include <sstream>
#include <cstdint>
#include <string>

class BigInt
{
    int32_t base = 1000000000;
    int32_t *digit = nullptr;
    size_t len = 0;
    bool is_negative = false;
public:
    BigInt();
    BigInt(const std::string &str);
    BigInt(int64_t dig);
    BigInt(const BigInt &other);
    BigInt(BigInt &&other);
    ~BigInt();
    BigInt &operator=(const BigInt &other);
    BigInt &operator=(BigInt &&other);
    BigInt operator-() const;
    friend std::ostream &operator<<(std::ostream &ostream, const BigInt &dig);
    friend bool operator==(const BigInt &first, const BigInt &second);
    friend bool operator!=(const BigInt &first, const BigInt &second);
    friend bool operator<(const BigInt &first, const BigInt &second);
    friend bool operator<=(const BigInt &first, const BigInt &second);
    friend bool operator>(const BigInt &first, const BigInt &second);
    friend bool operator>=(const BigInt &first, const BigInt &second);
    friend BigInt operator+(const BigInt &left, const BigInt &right);
    friend BigInt operator-(const BigInt &left, const BigInt &right);
    friend BigInt operator*(const BigInt &left, const BigInt &right);
};
