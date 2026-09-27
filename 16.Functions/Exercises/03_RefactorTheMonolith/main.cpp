// ⭐⭐⭐ Exercise 03: RefactorTheMonolith
// This program WORKS, but everything is crammed into main. Real code often looks like this.
// Refactor it into small, well-named functions, e.g.:
//   readScores, average, highest, letterGrade, printReport
// Rules: same output as before. main should end up ~10 lines and read like a story.
#include <iostream>

int main()
{
    int scores[5]{};
    std::cout << "Enter 5 scores: ";
    for (int i = 0; i < 5; ++i) std::cin >> scores[i];

    int total = 0;
    for (int i = 0; i < 5; ++i) total += scores[i];
    double avg = total / 5.0;

    int best = scores[0];
    for (int i = 1; i < 5; ++i) if (scores[i] > best) best = scores[i];

    char grade;
    if (avg >= 90) grade = 'A';
    else if (avg >= 80) grade = 'B';
    else if (avg >= 70) grade = 'C';
    else grade = 'F';

    std::cout << "Average: " << avg << '\n';
    std::cout << "Best: " << best << '\n';
    std::cout << "Grade: " << grade << '\n';
}
