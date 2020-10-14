#include <cstddef>
#include "allocator.h"
#include <iostream>

Allocator::Allocator() = default;

Allocator::~Allocator()
{
    delete [] start;
}

void Allocator::makeAllocator(size_t maxSize)
{
    if (flag) {
        delete [] start;
        std::cout << "The memory was freed" << std::endl;
    }
    start = new char[maxSize];
    offset = start;
    if (start != nullptr) {
        total_size = maxSize;
        flag = true;
    }
}

char* Allocator::alloc(size_t size)
{
    char *res;
    if (start != nullptr && total_size - offset_size >= size) {
        offset_size += size;
        res = offset;
        offset += size;
        return res;
    } else {
        return nullptr;
    }
}

void Allocator::reset()
{
    offset = start;
}
