#include <cassert>
#include <cstddef>
#include "allocator.h"

void SimplePosTest()
{
    Allocator allocator;
    allocator.makeAllocator(50);
    char *p = allocator.alloc(20);
    assert(p != nullptr);
}

void SimpleNegTest()
{
    Allocator allocator;
    allocator.makeAllocator(50);
    char *p = allocator.alloc(100);
    assert(p == nullptr);
}

void TwoAlloc()
{
    Allocator allocator;
    allocator.makeAllocator(50);
    char *p = allocator.alloc(10);
    char *q = allocator.alloc(20);
    assert(q == p + 10);
}

void ResetTest()
{
    Allocator allocator;
    allocator.makeAllocator(50);
    char *p = allocator.alloc(10);
    allocator.reset();
    char *q = allocator.alloc(20);
    assert(p == q && p != nullptr);
}

void TwoMakeAllocTest()
{
    Allocator allocator;
    allocator.makeAllocator(50);
    char *p = allocator.alloc(10);
    allocator.makeAllocator(30);
    char *q = allocator.alloc(20);
    assert(q != nullptr);
}

int main()
{
    SimplePosTest();
    SimpleNegTest();
    TwoAlloc();
    ResetTest();
    TwoMakeAllocTest();
    return 0;
}
