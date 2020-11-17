
template <class T>
Error Serializer::save(T& obj)
{
    return obj.serialize(*this);
}

template <class... ArgsT>
Error Serializer::operator()(ArgsT&&... args)
{
    return Serializer::process(args...);
}

template <class T>
Error Serializer::process(T&& arg)
{
    return Serializer::upload(arg);
}

template <class T, class... ArgsT>
Error Serializer::process(T&& arg, ArgsT&&... args)
{
    if (Serializer::upload(arg) != Error::NoError) {
        return Error::CorruptedArchive;
    } else {
        return Serializer::process(std::forward<ArgsT>(args)...);
    }
}

Error Serializer::upload(bool num)
{
    try {
        if (num) {
            out_ << "true" << Separator;
        } else {
            out_ << "false" << Separator;
        }
        return Error::NoError;
    } catch (const std::exception& e) {
        return Error::CorruptedArchive;
    }
}

Error Serializer::upload(uint64_t num)
{
    try {
        out_ << num << Separator;
        return Error::NoError;
    } catch (const std::exception& e) {
        return Error::CorruptedArchive;
    }
}

template <class T>
Error Deserializer::load(T& obj)
{
    return obj.deserialize(*this);
}

template <class... ArgsT>
Error Deserializer::operator()(ArgsT&&... args)
{
    return Deserializer::process(args...);
}

template <class T>
Error Deserializer::process(T&& arg)
{
    return Deserializer::download(arg);
}

template <class T, class... ArgsT>
Error Deserializer::process(T&& arg, ArgsT&&... args)
{
    if (Deserializer::download(arg) != Error::NoError) {
        return Error::CorruptedArchive;
    } else {
        return Deserializer::process(std::forward<ArgsT>(args)...);
    }
}

Error Deserializer::download(bool& num)
{
    try {
        std::string tmp;
        in_ >> tmp;
        if (tmp == "true") {
            num = true;
            return Error::NoError;
        } else if (tmp == "false") {
            num = false;
            return Error::NoError;
        } else {
            return Error::CorruptedArchive;
        }
    } catch (const std::exception& e) {
        return Error::CorruptedArchive;
    }
}

Error Deserializer::download(uint64_t& num)
{
    try {
        in_ >> num;
        return Error::NoError;
    } catch (const std::exception& e) {
        return Error::CorruptedArchive;
    }
}
