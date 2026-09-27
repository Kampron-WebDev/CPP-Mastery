#include <iostream>
#include <string>
#include <type_traits>

template <typename T>
void describe(const T& value)
{
    if constexpr (std::is_same_v<T, bool>) {
        std::cout << "bool: " << std::boolalpha << value << '\n';
    } else if constexpr (std::is_integral_v<T>) {
        std::cout << "integer of " << sizeof(T) << " bytes: " << +value << '\n';   // + prints char as a number
    } else if constexpr (std::is_floating_point_v<T>) {
        std::cout << "decimal: " << value << '\n';
    } else if constexpr (std::is_pointer_v<T>) {
        if (value == nullptr) std::cout << "a null pointer\n";
        else std::cout << "pointer to something at " << static_cast<const void*>(value) << '\n';
    } else if constexpr (std::is_same_v<T, std::string>) {
        std::cout << "text of length " << value.size() << ": " << value << '\n';
    } else {
        std::cout << "unknown type\n";
    }
}

struct Point { int x, y; };

int main()
{
    int someInt{7};
    int* nothing{nullptr};
    describe(true);
    describe(42);
    describe('x');
    describe(3.14f);
    describe(2.5);
    describe(&someInt);
    describe(nothing);
    describe(std::string{"templates!"});
    describe(Point{1, 2});
}
