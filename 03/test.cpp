#include "matrix.h"
#include <cassert>

void TestCreation()
{  
    try { 
        Matrix m(2,3);
        assert(m.GetRows() == 2);
        assert(m.GetColumns() == 3);
    }
    catch (std::logic_error &s) {
        std::cout << "Exception: " << s.what() << std::endl;
    }
    std::cout << "Test 1 passed successfully" << std::endl;
}

void TestArithmetic()
{
    try {
        Matrix m1(3, 2), m2(3, 2);
        size_t rws = m1.GetRows();
        size_t cols = m2.GetColumns();
        for (size_t i = 0; i < rws; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                m1[i][j] = 2;
                m2[i][j] = 3;
            }
        }
        m1 *= 3;
        try {
            Matrix m3(3, 2);
            m3 = m1 + m2;
            for (size_t i = 0; i < rws; ++i) {
                for (size_t j = 0; j < cols; ++j) {
                    assert(m1[i][j] == 6);
                    assert(m3[i][j] == 9);
                }
            }
        }
        catch (std::logic_error &s) {
            std::cout << "Exception: " << s.what() << std::endl;
        }
    }
    catch (std::logic_error &s) {
        std::cout << "Exception: " << s.what() << std::endl;
    }
    std::cout << "Test 2 passed successfully" << std::endl;
}

void TestEquals()
{
    try {
        Matrix m1(3, 5);
        Matrix m2(3, 5);
        Matrix m3(2, 4);
        Matrix m4(3, 5);
        size_t rws = m1.GetRows();
        size_t cols = m1.GetColumns();
        for (size_t i = 0; i < rws; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                m1[i][j] = 2;
                m2[i][j] = 2;
                m4[i][j] = 1;
            }
        }
        assert((m1 == m2) == true);
        assert((m1 == m3) == false);
        assert((m2 != m3) == true);
        assert((m2 != m4) == true);
    }
    catch (std::logic_error &s) {
        std::cout << "Exception: " << s.what() << std::endl;
    }
    std::cout << "Test 3 passed successfully" << std::endl;
}

void TestOutOfRange1() 
{
    try {
        Matrix m(3, 4);
        try {
            m[-1][2];
        }
        catch (std::out_of_range &s) {
            std::cout << "Exception: " << s.what() << std::endl;
        }
    }
    catch (std::logic_error &s) {
        std::cout << "Exception: " << s.what() << std::endl;
    }
    std::cout << "Test 4 passed successfully" << std::endl;
}

void TestOutOfRange2() 
{
    try {
        Matrix m(3, 4);
        try {
            m[2][-1];
        }
        catch (std::out_of_range &s) {
            std::cout << "Exception: " << s.what() << std::endl;
        }
    }
    catch (std::logic_error &s) {
        std::cout << "Exception: " << s.what() << std::endl;
    }
    std::cout << "Test 5 passed successfully" << std::endl;
}

void TestOutOfRange3() 
{
    try {
        Matrix m(3, 4);
        try {
            m[5][2];
        }
        catch (std::out_of_range &s) {
            std::cout << "Exception: " << s.what() << std::endl;
        }
    }
    catch (std::logic_error &s) {
        std::cout << "Exception: " << s.what() << std::endl;
    }
    std::cout << "Test 6 passed successfully" << std::endl;
}

void TestPrint() 
{
    try {
        Matrix m(4,6);
        size_t rws = m.GetRows();
        size_t cols = m.GetColumns();
        for (size_t i = 0; i < rws; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                m[i][j] = i + j + 10 * i;
            }
        }
        std::cout << m << std::endl;
    }
    catch (std::logic_error &s) {
        std::cout << "Exception: " << s.what() << std::endl;
    }
    std::cout << "Test 7 passed successfully" << std::endl;

}

int main()
{
    TestCreation();
    TestArithmetic();
    TestEquals();
    TestOutOfRange1();
    TestOutOfRange2();
    TestOutOfRange3();
    TestPrint();
    return 0;
}
