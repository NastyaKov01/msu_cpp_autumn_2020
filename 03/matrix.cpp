#include "matrix.h"

const int64_t Proxy::operator[](size_t col_idx) const
{
    if (col_idx < 0 || col_idx >= cols) {
        throw std::out_of_range("Column index is out of range");
    }
    return proxy_ptr[row_idx * cols + col_idx];
}

int64_t &Proxy::operator[](size_t col_idx) 
{
    if (col_idx < 0 || col_idx >= cols) {
        throw std::out_of_range("Column index is out of range");
    }
    return proxy_ptr[row_idx * cols + col_idx];
}


Matrix::Matrix(size_t n): rows(n), columns(n)
{
    ptr = new int64_t[rows * columns];
    if (ptr != nullptr) {
        std::fill(ptr, ptr + rows * columns, 0);
    } else {
        throw std::logic_error("Memory allocation error");
    }
}

Matrix::Matrix(size_t rws, size_t cols): rows(rws), columns(cols)
{
    ptr = new int64_t[rows * columns];
    if (ptr != nullptr) {
        std::fill(ptr, ptr + rows * columns, 0);
    } else {
        throw std::logic_error("Memory allocation error");
    }
}

Matrix::~Matrix()
{
    delete [] ptr;
}

size_t Matrix::GetRows()
{
    return rows;
}

size_t Matrix::GetColumns()
{
    return columns;
}
    
const Proxy Matrix::operator[](size_t row_index) const
{
    if (row_index < 0 || row_index >= rows) {
        throw std::out_of_range("Row index is out of range");
    }
    return Proxy(row_index, columns, ptr);
}

Proxy Matrix::operator[](size_t row_index)
{
    if (row_index < 0 || row_index >= rows) {
        throw std::out_of_range("Row index is out of range");
    }
    return Proxy(row_index, columns, ptr);
}

Matrix &Matrix::operator*=(int64_t num)
{
    size_t totsize = rows * columns;
    for (size_t i = 0; i < totsize; ++i) {
        ptr[i] *= num;
    }
    return *this;
}

Matrix &Matrix::operator=(const Matrix &other)
{
    if (rows * columns != other.rows * other.columns) {
        delete [] ptr;
        ptr = new int64_t[other.rows * other.columns];
    }
    rows = other.rows;
    columns = other.columns;
    size_t totsize = rows * columns;
    for (size_t i = 0; i < totsize; ++i) {
        ptr[i] = other.ptr[i];
    }
    return *this;
}

bool operator==(const Matrix &m1, const Matrix &m2) 
{
    if ((m1.rows == m2.rows) && (m1.columns == m2.columns)) {
        size_t rws = m1.rows;
        size_t cols = m2.columns;
        for (size_t i = 0; i < rws; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                if (m1[i][j] != m2[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

bool operator!=(const Matrix &m1, const Matrix &m2) 
{
    return !(m1 == m2);
}


std::ostream& operator<<(std::ostream& ostream, const Matrix &m) 
{
    size_t rows = m.rows;
    size_t columns = m.columns;
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            ostream << m[i][j] << "\t";
        }
        ostream << std::endl;
    }
    return ostream;
}

Matrix operator+(Matrix &m1, Matrix &m2)
{
    if (m1.rows != m2.rows || m1.columns != m2.columns) {
        throw std::logic_error("Different dimensions");
    }
    size_t rows = m1.rows;
    size_t cols = m1.columns;
    Matrix tmp(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            tmp[i][j] = m1[i][j] + m2[i][j];
        }
    }
    return tmp;
}
