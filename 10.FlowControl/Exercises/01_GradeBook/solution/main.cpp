#include <iostream>

int main()
{
    int score{};
    std::cout << "Score: ";
    std::cin >> score;

    // Guard clause: reject bad input first, then the main logic stays simple.
    if (!std::cin || score < 0 || score > 100) {
        std::cout << "Invalid score\n";
        return 1;
    }

    char grade{};
    if (score >= 90)      grade = 'A';
    else if (score >= 80) grade = 'B';
    else if (score >= 70) grade = 'C';
    else if (score >= 60) grade = 'D';
    else                  grade = 'F';

    std::cout << "Grade: " << grade << '\n';
}
