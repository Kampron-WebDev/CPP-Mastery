#include <iostream>
#include <algorithm>
#include <functional>
#include <string>
#include <vector>

struct Book {
    std::string title;
    std::string author;
    int year;
    double rating;
};

void print(const std::vector<Book>& books)
{
    for (const auto& b : books) std::cout << "  " << b.year << ' ' << b.title << " (" << b.rating << ")\n";
}

int main()
{
    std::vector<Book> books{{"1984", "Orwell", 1949, 4.7},
                            {"Dune", "Herbert", 1965, 4.5},
                            {"Clean Code", "Martin", 2008, 4.3},
                            {"SICP", "Abelson", 1985, 4.6},
                            {"The Hobbit", "Tolkien", 1937, 4.8}};

    std::ranges::sort(books, {}, &Book::year);
    std::cout << "By year:\n";
    print(books);

    std::ranges::sort(books, std::greater{}, &Book::rating);
    std::cout << "By rating:\n";
    print(books);

    if (auto it = std::ranges::find(books, "Orwell", &Book::author); it != books.end())
        std::cout << "Orwell wrote " << it->title << '\n';

    std::cout << "Newest: " << std::ranges::max_element(books, {}, &Book::year)->title << '\n';
    std::cout << "Rated 4.5+: " << std::ranges::count_if(books, [](double r) { return r >= 4.5; }, &Book::rating) << '\n';
}
