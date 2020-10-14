#pragma once

class Allocator
{
    char *start, *offset;
    size_t total_size, offset_size = 0;
    bool flag = false;
public:
    Allocator();
    ~Allocator();
    void makeAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();
};
