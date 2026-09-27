#include <iostream>

constexpr int scoreCount{5};

void readScores(int scores[], int size)
{
    std::cout << "Enter " << size << " scores: ";
    for (int i = 0; i < size; ++i) std::cin >> scores[i];
}

double average(const int scores[], int size)
{
    int total{0};
    for (int i = 0; i < size; ++i) total += scores[i];
    return static_cast<double>(total) / size;
}

int highest(const int scores[], int size)
{
    int best = scores[0];
    for (int i = 1; i < size; ++i)
        if (scores[i] > best) best = scores[i];
    return best;
}

char letterGrade(double avg)
{
    if (avg >= 90) return 'A';   // early returns: no temporary variable needed
    if (avg >= 80) return 'B';
    if (avg >= 70) return 'C';
    return 'F';
}

void printReport(double avg, int best, char grade)
{
    std::cout << "Average: " << avg << "\nBest: " << best << "\nGrade: " << grade << '\n';
}

int main()
{
    int scores[scoreCount]{};
    readScores(scores, scoreCount);

    const double avg = average(scores, scoreCount);
    printReport(avg, highest(scores, scoreCount), letterGrade(avg));
}
