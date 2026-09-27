// Three classic sorts, checked against std::sort and timed.
// Build with "Optimized -O2" for fair timings.
#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <span>
#include <vector>

void insertionSort(std::span<int> a)   // O(n²): like sorting playing cards in your hand
{
    for (std::size_t i = 1; i < a.size(); ++i) {
        const int key = a[i];
        std::size_t j = i;
        while (j > 0 && a[j - 1] > key) {
            a[j] = a[j - 1];   // shift bigger cards right
            --j;
        }
        a[j] = key;
    }
}

void mergeSort(std::span<int> a, std::vector<int>& buffer)   // O(n log n): split, sort halves, merge
{
    if (a.size() < 2) return;
    const std::size_t mid = a.size() / 2;
    mergeSort(a.first(mid), buffer);
    mergeSort(a.subspan(mid), buffer);
    buffer.assign(a.begin(), a.end());
    std::size_t i = 0, j = mid, k = 0;
    while (i < mid && j < a.size()) a[k++] = (buffer[j] < buffer[i]) ? buffer[j++] : buffer[i++];
    while (i < mid) a[k++] = buffer[i++];
    while (j < a.size()) a[k++] = buffer[j++];
}

void quickSort(std::span<int> a)   // O(n log n) average: partition around a pivot
{
    if (a.size() < 2) return;
    const int pivot = a[a.size() / 2];
    std::size_t lo = 0, hi = a.size() - 1;
    while (lo <= hi) {                     // Hoare-style partition
        while (a[lo] < pivot) ++lo;
        while (a[hi] > pivot) --hi;
        if (lo <= hi) {
            std::swap(a[lo], a[hi]);
            ++lo;
            if (hi == 0) break;
            --hi;
        }
    }
    quickSort(a.first(hi + 1));
    quickSort(a.subspan(lo));
}

template <typename F>
void test(const char* name, std::vector<int> data, F sorter)
{
    const auto start = std::chrono::steady_clock::now();
    sorter(data);
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start);
    std::cout << name << ": " << ms.count() << " ms, sorted correctly? " << std::boolalpha
              << std::is_sorted(data.begin(), data.end()) << '\n';
}

int main()
{
    std::mt19937 rng{2026};
    std::vector<int> small(20'000), big(1'000'000);
    for (int& x : small) x = static_cast<int>(rng() % 100'000);
    for (int& x : big) x = static_cast<int>(rng() % 1'000'000);

    std::cout << "--- 20 000 items ---\n";
    test("insertion", small, [](std::vector<int>& v) { insertionSort(v); });
    test("merge    ", small, [](std::vector<int>& v) { std::vector<int> buf; mergeSort(v, buf); });
    test("quick    ", small, [](std::vector<int>& v) { quickSort(v); });
    test("std::sort", small, [](std::vector<int>& v) { std::sort(v.begin(), v.end()); });

    std::cout << "--- 1 000 000 items (insertion sort skipped: it would take minutes) ---\n";
    test("merge    ", big, [](std::vector<int>& v) { std::vector<int> buf; mergeSort(v, buf); });
    test("quick    ", big, [](std::vector<int>& v) { quickSort(v); });
    test("std::sort", big, [](std::vector<int>& v) { std::sort(v.begin(), v.end()); });
}
