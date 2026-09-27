#include <iostream>

int main()
{
    int capacity{2};
    int size{0};
    int* scores = new int[capacity];

    std::cout << "Enter scores (-1 to finish): ";
    int value{};
    while (std::cin >> value && value != -1) {
        if (size == capacity) {
            const int newCapacity = capacity * 2;
            int* bigger = new int[newCapacity];
            for (int i = 0; i < size; ++i) bigger[i] = scores[i];   // copy
            delete[] scores;                                        // free the old block
            scores = bigger;                                        // point at the new one
            capacity = newCapacity;
            std::cout << "Grew to capacity " << capacity << '\n';
        }
        scores[size++] = value;
    }

    if (size > 0) {
        long long sum{0};
        for (int i = 0; i < size; ++i) {
            std::cout << scores[i] << ' ';
            sum += scores[i];
        }
        std::cout << "\nAverage: " << static_cast<double>(sum) / size << '\n';
    }

    delete[] scores;     // exactly one delete[] for the live array
    scores = nullptr;
}
