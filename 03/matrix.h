#pragma once
#include <cstdint>
#include <iostream>

class Proxy
{
    size_t row_idx, cols;
    int64_t *proxy_ptr;
public:
    Proxy(size_t row_index,size_t columns, int64_t *p): row_idx(row_index), 
        cols(columns), proxy_ptr(p) {}
    const int64_t operator[](size_t col_idx) const;
    int64_t &operator[](size_t col_idx);
};

class Matrix
{
    size_t rows, columns;
    int64_t *ptr = nullptr;
public:
    Matrix(size_t n);
    Matrix(size_t rws, size_t cols);
    ~Matrix();
    size_t GetRows();
    size_t GetColumns();
    const Proxy operator[](size_t row_index) const;
    Proxy operator[](size_t row_index);
    Matrix &operator*=(int64_t num);
    Matrix &operator=(const Matrix &other);
    friend bool operator==(const Matrix &m1, const Matrix &m2);
    friend bool operator!=(const Matrix &m1, const Matrix &m2);
    friend Matrix operator+(Matrix &m1, Matrix &m2);
    friend std::ostream& operator<<(std::ostream &ostream, const Matrix &m);
};
