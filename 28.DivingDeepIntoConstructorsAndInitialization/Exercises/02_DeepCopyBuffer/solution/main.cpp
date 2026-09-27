#include <iostream>

class IntBuffer {
public:
    explicit IntBuffer(int size) : size{size}, data{new int[size]{}} {}

    // Deep copy: allocate OUR OWN block and copy the values into it.
    IntBuffer(const IntBuffer& other) : size{other.size}, data{new int[other.size]}
    {
        for (int i = 0; i < size; ++i) data[i] = other.data[i];
        std::cout << "(deep copy made)\n";
    }

    IntBuffer& operator=(const IntBuffer&) = delete;   // until Lesson 34

    ~IntBuffer() { delete[] data; }

    int& operator[](int i) { return data[i]; }
    int getSize() const { return size; }

private:
    int size;
    int* data;
};

int main()
{
    IntBuffer original{3};
    original[0] = 42;
    {
        IntBuffer copy{original};
        copy[0] = 99;
        std::cout << "copy[0] = " << copy[0] << '\n';   // 99
    }                                                   // frees ITS OWN memory only
    std::cout << "original[0] = " << original[0] << '\n';   // still 42
    // Modern C++: store std::vector<int> instead of int*, and you need none of this (Rule of Zero).
}
