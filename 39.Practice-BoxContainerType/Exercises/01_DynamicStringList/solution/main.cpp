#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

class StringList {
public:
    StringList() : items{new std::string[2]}, count{0}, cap{2} {}

    ~StringList() { delete[] items; }

    StringList(const StringList& other) : items{new std::string[other.cap]}, count{other.count}, cap{other.cap}
    {
        for (std::size_t i = 0; i < count; ++i) items[i] = other.items[i];
    }

    StringList& operator=(const StringList& other)
    {
        if (this == &other) return *this;        // self-assignment: nothing to do
        StringList copy{other};                  // copy first: if it throws, *this is untouched
        std::swap(items, copy.items);            // then swap in the new data (copy-and-swap idiom)
        std::swap(count, copy.count);
        std::swap(cap, copy.cap);
        return *this;                            // copy's destructor frees our OLD array
    }

    void add(const std::string& s)
    {
        if (count == cap) grow(cap * 2);
        items[count++] = s;
    }

    bool removeFirst(const std::string& s)
    {
        for (std::size_t i = 0; i < count; ++i) {
            if (items[i] == s) {
                for (std::size_t j = i; j + 1 < count; ++j) items[j] = std::move(items[j + 1]);   // shift left
                --count;
                return true;
            }
        }
        return false;
    }

    const std::string& operator[](std::size_t i) const
    {
        if (i >= count) throw std::out_of_range{"StringList index " + std::to_string(i)};
        return items[i];
    }

    std::size_t size() const { return count; }
    std::size_t capacity() const { return cap; }

    friend std::ostream& operator<<(std::ostream& os, const StringList& list)
    {
        os << '[';
        for (std::size_t i = 0; i < list.count; ++i) os << (i ? ", " : "") << list.items[i];
        return os << ']';
    }

private:
    void grow(std::size_t newCap)
    {
        auto* bigger = new std::string[newCap];
        for (std::size_t i = 0; i < count; ++i) bigger[i] = std::move(items[i]);
        delete[] items;
        items = bigger;
        cap = newCap;
    }

    std::string* items;
    std::size_t count;
    std::size_t cap;
};

int main()
{
    StringList fruits;
    for (const char* f : {"apple", "banana", "cherry", "date", "elderberry"}) {
        fruits.add(f);
        std::cout << "size " << fruits.size() << ", capacity " << fruits.capacity() << '\n';
    }

    StringList copy{fruits};
    copy.removeFirst("banana");
    copy.add("fig");

    StringList assigned;
    assigned = copy;
    assigned = assigned;   // self-assignment is safe

    std::cout << "original: " << fruits << '\n';
    std::cout << "copy:     " << copy << '\n';
    std::cout << "assigned: " << assigned << '\n';

    try {
        std::cout << fruits[99] << '\n';
    } catch (const std::out_of_range& e) {
        std::cout << "caught: " << e.what() << '\n';
    }
}
