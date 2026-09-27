// ⭐⭐⭐ Exercise 02: DeepCopyBuffer
// This IntBuffer owns heap memory. It has NO copy constructor, so the compiler's default
// one does a SHALLOW copy. Run it: it will likely crash or print garbage at the end
// (double delete). Understand why, then:
//   1. Write a DEEP copy constructor:  IntBuffer(const IntBuffer& other)
//   2. Forbid copy ASSIGNMENT for now:  IntBuffer& operator=(const IntBuffer&) = delete;
//      (Lesson 34 teaches how to write it properly.)
//   3. Prove the copy is independent: change copy[0] and show original[0] is unchanged.
#include <iostream>

class IntBuffer {
public:
    explicit IntBuffer(int size) : size{size}, data{new int[size]{}} {}
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
        IntBuffer copy{original};   // shallow copy: copy.data == original.data
        copy[0] = 99;
    }                               // copy's destructor deletes the SHARED memory!
    std::cout << original[0] << '\n';   // use-after-free: undefined behaviour
}
