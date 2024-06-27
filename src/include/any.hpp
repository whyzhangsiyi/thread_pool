#pragma once

#include <memory>
class any
{
private:
    class base_
    {
    public:
        virtual ~base_() {}
    };

    template <typename T>
    class derived_ : public base_
    {
    public:
        derived_(T data)
        {
            data_ = data;
        }
        T data_;
    };

private:
    std::unique_ptr<base_> base_ptr;

public:
    template <typename T>
    any(T data);

    template <typename T>
    T cast_()
    {

        derived_<T> *realType = dynamic_cast<derived_<T> *>(base_ptr.get());

        try
        {
            if (realType)
            {
                return realType->data_;
            }

            throw "dynamic_cast fail,type err";
        }
        catch (const char *str)
        {
            std::cerr << str << '\n';
        }
    }

    virtual ~any();
};

template <typename T>
any::any(T data) : base_ptr(std::make_unique<derived_<T>>(data))
{
}

any::~any()
{
}
