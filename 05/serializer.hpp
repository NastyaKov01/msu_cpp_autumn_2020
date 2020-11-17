#pragma once
///#include "serializer.tpp"
#include <cstdint>
#include <sstream>

enum class Error
{
    NoError,
    CorruptedArchive
};

class Serializer
{
    static constexpr char Separator = ' ';
    std::ostream &out_;
public:
    explicit Serializer(std::ostream& out): out_(out) {}

    template <class T>
    Error save(T& obj);

    template <class... ArgsT>
    Error operator()(ArgsT&&... args);

private:
    template <class T>
    Error process(T&& arg);

    template <class T, class... ArgsT>
    Error process(T&& arg, ArgsT&&... args);

    Error upload(bool num);

    Error upload(uint64_t num);
};

class Deserializer
{
    std::istream &in_;
public:
    explicit Deserializer(std::istream& in): in_{in} {}

    template <class T>
    Error load(T& obj);

    template <class... ArgsT>
    Error operator()(ArgsT&&... args);

private:
    template <class T>
    Error process(T&& arg);

    template <class T, class... ArgsT>
    Error process(T&& arg, ArgsT&&... args);

    Error download(bool& num);
    Error download(uint64_t& num);
};

#include "serializer.tpp"
