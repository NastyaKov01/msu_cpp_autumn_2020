#include "serializer.hpp"
#include <cassert>
#include <iostream>

struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b, c);
    }
};

struct MuchData
{
    uint64_t a, b, c, d;
    bool e;
    uint64_t f, g, h, i;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c, d, e, f, g, h, i);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b, c, d, e, f, g, h, i);
    }
};


void Test1()
{
    std::cout << "Test 1" << std::endl;
    Data x {1, true, 2};
    std::stringstream ss;
    Serializer ser(ss);
    ser.save(x);
    Data y {0, false, 0};
    Deserializer deser(ss);
    const Error err = deser.load(y);
    assert(err == Error::NoError);
    assert(x.a == y.a && x.b == y.b && x.c == y.c);
    std::cout << "Test 1 passed successfully\n" << std::endl;
}

void Test2()
{
    std::cout << "Test 2" << std::endl;
    std::stringstream s1, s2;
    Data x {25, true, 12};
    Data y {0, false, 0};
    Serializer ser(s1);
    Deserializer deser(s2);
    const Error err1 = ser.save(x);
    const Error err2 = deser.load(y);
    assert(err1 == Error::NoError);
    assert(err2 == Error::CorruptedArchive);
    std::cout << "Test 2 passed successfully\n" << std::endl;
}

void Test3() 
{
    std::cout << "Test 3" << std::endl;
    MuchData x {349583479, 8345953497, 957405705, 98349473968, false, 9852959049, 120312832, 3948349, 398369};
    MuchData y {0, 0, 0, 0, true, 0, 0, 0, 0};
    std::stringstream ss;
    Serializer ser(ss);
    Deserializer deser(ss);
    ser.save(x);
    ser.save(y);
    deser.load(y);
    assert(x.a == y.a && x.b == y.b && x.c == y.c && x.d == y.d);
    assert(x.e == y.e && x.f == y.f && x.g == y.g && x.h == y.h && x.i == y.i);
    deser.load(y);
    assert(x.a != y.a && x.b != y.b && x.c != y.c && x.d != y.d);
    assert(x.e != y.e && x.f != y.f && x.g != y.g && x.h != y.h && x.i != y.i);
    std::cout << "Test 3 passed successfully\n" << std::endl;
}

int main()
{
    Test1();
    Test2();
    Test3();
    return 0;
}
