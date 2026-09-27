// ⭐⭐ Exercise 02: ProjectionSorting
// struct Book { std::string title; std::string author; int year; double rating; };
// Using std::ranges algorithms WITH PROJECTIONS (no custom comparator lambdas!):
//   1. sort by year (oldest first) and print
//   2. sort by rating (highest first): comparator std::greater{}, projection &Book::rating
//   3. find the book by "Orwell" with ranges::find and projection &Book::author
//   4. the newest book with ranges::max_element + projection
//   5. count books with rating >= 4.5 (ranges::count_if + projection)
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
    // Books: {"1984","Orwell",1949,4.7} {"Dune","Herbert",1965,4.5} {"Clean Code","Martin",2008,4.3}
    //        {"SICP","Abelson",1985,4.6} {"The Hobbit","Tolkien",1937,4.8}
    // TODO
}
