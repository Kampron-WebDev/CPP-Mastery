#include <iostream>
#include <iterator>
#include <cstring>

bool isPalindrome(const char word[])
{
    int left = 0;
    int right = static_cast<int>(std::strlen(word)) - 1;   // strlen stops before '\0'
    while (left < right) {
        if (word[left] != word[right]) return false;
        ++left;
        --right;
    }
    return true;
}

int main()
{
    int numbers[]{1, 2, 3, 4, 5, 6, 7};
    int left = 0;
    int right = static_cast<int>(std::size(numbers)) - 1;
    while (left < right) {            // meet in the middle
        int temp = numbers[left];
        numbers[left] = numbers[right];
        numbers[right] = temp;
        ++left;
        --right;
    }
    for (int n : numbers) std::cout << n << ' ';
    std::cout << '\n';

    char word1[]{"racecar"};
    char word2[]{"rocket"};
    std::cout << std::boolalpha << word1 << ": " << isPalindrome(word1) << '\n'
              << word2 << ": " << isPalindrome(word2) << '\n';
}
