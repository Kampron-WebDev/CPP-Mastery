// A tiny string class implementing the full Rule of Five with copy-and-swap.
// Every special member prints, so you can SEE which one runs.
#include <cstring>
#include <iostream>
#include <utility>

class MyString {
public:
    MyString(const char* s = "") : size{std::strlen(s)}, data{new char[size + 1]}
    {
        std::memcpy(data, s, size + 1);
        std::cout << "  ctor(\"" << data << "\")\n";
    }
    ~MyString()                                   // 1. destructor
    {
        std::cout << "  dtor(" << (data ? data : "<moved-from>") << ")\n";
        delete[] data;
    }
    MyString(const MyString& o) : size{o.size}, data{new char[o.size + 1]}   // 2. copy ctor
    {
        std::memcpy(data, o.data, size + 1);
        std::cout << "  copy ctor(\"" << data << "\")\n";
    }
    MyString(MyString&& o) noexcept                                          // 3. move ctor
        : size{std::exchange(o.size, 0)}, data{std::exchange(o.data, nullptr)}
    {
        std::cout << "  move ctor(\"" << data << "\")\n";
    }
    MyString& operator=(MyString other) noexcept  // 4 + 5. copy AND move assignment (copy-and-swap)
    {
        std::cout << "  assign via swap\n";
        swap(*this, other);
        return *this;
    }
    friend void swap(MyString& a, MyString& b) noexcept
    {
        std::swap(a.size, b.size);
        std::swap(a.data, b.data);
    }
    const char* c_str() const { return data ? data : ""; }

private:
    std::size_t size;
    char* data;
};

int main()
{
    std::cout << "a:\n";           MyString a{"hello"};
    std::cout << "b = copy of a:\n"; MyString b{a};
    std::cout << "c = move of a:\n"; MyString c{std::move(a)};
    std::cout << "b = c (copy-assign):\n"; b = c;
    std::cout << "b = temp (move-assign):\n"; b = MyString{"world"};
    std::cout << "result: b=" << b.c_str() << ", c=" << c.c_str() << "\nend of main:\n";
}
// The Rule-of-ZERO version of this class is simply:  struct MyString { std::string text; };
