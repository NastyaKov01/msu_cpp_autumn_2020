#include "bigint.h"

int32_t *resize(int32_t *ptr, size_t num, size_t newnum)
{
    int32_t *newptr = new int32_t [newnum];
    for (size_t i = 0; i < newnum; ++i) {
        if (num < newnum) {
            if (i < num) {
                newptr[i] = ptr[i];
            } else {
                newptr[i] = 0;
            }
        } else {
            newptr[i] = ptr[i];
        }
    }
    delete [] ptr;
    return newptr;
}

int32_t *remove_zeros(int32_t *ptr, size_t *len)
{
    int cnt = 0;
    while (*len - cnt > 1 && ptr[*len - cnt - 1] == 0) {
        cnt ++;
    }
    if (cnt != 0) {
        int32_t *newptr = resize(ptr, *len, *len - cnt);
        *len -= cnt;
        ptr = newptr;
    }
    return ptr;
}

BigInt::BigInt()
{
    len = 1;
    digit = new int32_t;
    digit[0] = 0;
}

BigInt::BigInt(const std::string &str)
{
    std::string dig = str;
    if (dig.size() == 0) {
        digit = new int32_t;
        *digit = 0;
        len = 1;
    } else {
        if (dig[0] == '-') {
            is_negative = true;
            dig.erase(0, 1);
        }
        size_t num = dig.size() / 9 + (dig.size() % 9 != 0);
        digit = new int32_t [num];
        int cnt = 0;
        for (int i = dig.size(); i > 0; i -= 9, cnt++) {
            std::stringstream ss;
            if (i < 9) {
                ss << dig.substr(0, i);
            } else {
                ss << dig.substr(i - 9, 9);
            }
            ss >> digit[cnt];
        }
        digit = remove_zeros(digit, &num);
        len = num;
    }
}

BigInt::BigInt(int64_t dig) 
{
    if (dig < 0) {
        is_negative = true;
        dig = -dig;
    }
    size_t num = 1;
    digit = new int32_t [num];
    do {
        digit[num - 1] = dig % base;
        dig /= base;
        if (dig != 0) {
            num++;
            int32_t *newptr = resize(digit, num -1, num);
            digit = newptr;
        }
    } while (dig != 0);
    len = num;
}

BigInt::BigInt(const BigInt &other): base(other.base), len(other.len), 
        is_negative(other.is_negative)
{
    digit = new int32_t [len];
    for (size_t i = 0; i < len; ++i) {
        digit[i] = other.digit[i];
    }
}

BigInt::BigInt(BigInt &&other): base(std::move(other.base)), len(std::move(other.len)),
        is_negative(std::move(other.is_negative))
{
    digit = other.digit;
    other.digit = nullptr;
    other.len = -1;
}

BigInt::~BigInt() 
{
    delete [] digit;
}

BigInt &BigInt::operator=(const BigInt &other)
{
    if (this == &other) {
        return *this;
    }
    if (digit != nullptr) {
        delete [] digit;
    }
    base = other.base;
    is_negative = other.is_negative;
    len = other.len;
    digit = new int32_t [len];
    for (size_t i = 0; i < len; ++i) {
        digit[i] = other.digit[i];
    }
    return *this;
}

BigInt &BigInt::operator=(BigInt &&other)
{
    if (this == &other) {
        return *this;
    }
    if (digit != nullptr) {
        delete [] digit;
    }
    base = std::move(other.base);
    is_negative = std::move(other.is_negative);
    len = std::move(other.len);
    digit = other.digit;
    other.digit = nullptr;
    other.len = -1;
    return *this;
}

BigInt BigInt::operator-() const 
{
    BigInt tmp = BigInt(*this);
    tmp.is_negative = !tmp.is_negative;
    return tmp;
}

std::ostream &operator<<(std::ostream &ostream, const BigInt &dig)
{
    if (dig.digit == nullptr) {
        ostream << 0;
    } else {
        if (dig.is_negative) {
            ostream << '-';
        }
        for (int i = dig.len - 1; i >= 0; --i) {
            int32_t tmp = dig.digit[i];
            int cnt = 0;
            while (tmp != 0) {
                cnt++;
                tmp /= 10;
            }
            if (i != int(dig.len - 1)) {
                for (int k = 0; k < 9 - cnt; ++k) {
                    ostream << 0;
                }
            }
            ostream << dig.digit[i];
        }
    }
    return ostream;
}

bool operator==(const BigInt &first, const BigInt &second)
{
    if (first.is_negative != second.is_negative) {
        return false;
    }
    if (first.len != second.len) {
        return false;
    }
    for (size_t i = 0; i < first.len; ++i) {
        if (first.digit[i] != second.digit[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const BigInt &first, const BigInt &second)
{
    return !(first == second);
}

bool operator<(const BigInt &first, const BigInt &second)
{
    if (first == second) {
        return false;
    }
    if (first.is_negative) {
        if (!second.is_negative) {
            return true;
        } else {
            return (-second) < (-first);
        }
    } else if (second.is_negative) {
        return false;
    } else {
        if (first.len != second.len) {
            return first.len < second.len;
        } else {
            for (int i = first.len - 1; i >= 0; --i) {
                if (first.digit[i] != second.digit[i]) {
                    return first.digit[i] < second.digit[i];
                }
            }
            return false;
        }
    }
}

bool operator<=(const BigInt &first, const BigInt &second)
{
    return (first < second || first == second);
}

bool operator>(const BigInt &first, const BigInt &second)
{
    return !(first <= second);
}

bool operator>=(const BigInt &first, const BigInt &second)
{
    return !(first < second);
}

BigInt operator+(const BigInt &left, const BigInt &right)
{
    if (left.is_negative) {
        if (right.is_negative) {
            return -((-right) + (-left));
        }
        return right - (-left);
    } else if (right.is_negative) {
        return left - (-right);
    }
    bool carry = 0;
    BigInt sum = BigInt(left);
    size_t size = left.len > right.len? left.len: right.len;
    size++;
    if (size > sum.len) {
        int32_t *newptr = resize(sum.digit, sum.len, size);
        sum.digit = newptr;
        sum.len = size;
    }
    for (size_t i = 0; i < size || carry != 0; ++i) {
        sum.digit[i] += carry;
        if (i < right.len) {
            sum.digit[i] += right.digit[i];   
        }
        carry = sum.digit[i] >= sum.base;
        if (carry) {
            sum.digit[i] -= sum.base;
        }
    }
    sum.digit = remove_zeros(sum.digit, &sum.len);
    return sum;
}

BigInt operator-(const BigInt &left, const BigInt &right)
{
    if (left.is_negative) {
        if (right.is_negative) {
            return (-right) - (-left);
        } else {
            return -((-left) + right);
        }
    } else if (right.is_negative) {
        return left + (-right);
    } else if (left < right) {
        return -(right - left);
    } else {
        BigInt sub(left);
        int32_t carry = 0;
        for (size_t i = 0; i < right.len || carry != 0; ++i) {
            sub.digit[i] -= carry;
            if (i < right.len) {
                sub.digit[i] -= right.digit[i];
            }
            carry = sub.digit[i] < 0;
            if (carry) {
                sub.digit[i] += sub.base;
            }
        }
        sub.digit = remove_zeros(sub.digit, &sub.len);
        return sub;
    }
}

BigInt operator*(const BigInt &left, const BigInt &right)
{
    BigInt res = BigInt(0);
    int32_t *newptr = resize(res.digit, 1, left.len + right.len);
    res.digit = newptr;
    res.len = left.len + right.len;
    if (left.is_negative != right.is_negative) {
        res.is_negative = true;
    }
    for (size_t i = 0; i < left.len; ++i) {
        for (size_t j = 0; j < right.len; ++j) {
            int64_t tmp = int64_t(left.digit[i]) * int64_t(right.digit[j]);
            if (res.digit[i + j] + tmp >= left.base) {
                res.digit[i + j + 1] += (res.digit[i + j] + tmp) / left.base;
                res.digit[i + j] = (res.digit[i + j] + tmp) % left.base;
            } else {
                res.digit[i + j] += tmp;
            }
        }
    }
    res.digit = remove_zeros(res.digit, &res.len);
    return res;
}
