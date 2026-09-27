// ⭐⭐ Exercise 01: Pipelines
// Using ONLY std::views pipelines (no raw loops except the final range-for to print):
//   1. The first 5 multiples of 7 greater than 50            -> 56 63 70 77 84
//   2. The squares of the odd numbers from 1..20, backwards   -> 361 289 ... 1
//   3. From the words below: the lengths of words longer than 3 letters
//   4. The sum of 1..100 that are divisible by 3 or 5 (hint: std::ranges::fold_left is C++23,
//      so print it by adding in the range-for)            -> 2418
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> words{"a", "tree", "is", "lovely", "and", "green", "!"};
    // TODO
}
