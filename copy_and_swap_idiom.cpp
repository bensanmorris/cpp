#include <iostream>

using namespace std;

template<class T>
class Foo
{
public:
    Foo(size_t size = 0)
    :
        size_(size),
        data_(size == 0 ? nullptr : new T[size])
    {}

    Foo(const Foo& rhs)
    :
        size_(rhs.size_),
        data_(rhs.size_ == 0 ? nullptr : new T[rhs.size_])
    {
        std::copy(rhs.data_, rhs.data_+size_, data_);
    }

    ~Foo()
    {
        delete [] data_;
    }

    void swap(Foo& lhs, Foo& rhs)
    {
        std::swap(lhs.size_, rhs.size_);
        std::swap(lhs.data_, rhs.data_);
    }

    Foo& operator = (Foo rhs) // nb. Foo passed in by value (creates copy)
    {
        swap(*this, rhs);     // this's data copied into rhs, rhs's data copied into this
        return *this;         // when this function return's rhs is destroyed which contains our old data
    }

private:
    size_t size_;
    T*     data_;
};

int main()
{
    Foo<int> a(10);
    Foo<int> b(20);
    a = b;
    return 0;
}
