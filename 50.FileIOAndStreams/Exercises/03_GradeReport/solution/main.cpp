#include <algorithm>
#include <array>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

struct Row {
    std::string name;
    std::array<int, 3> scores{};   // math, english, science
    double average() const { return (scores[0] + scores[1] + scores[2]) / 3.0; }
};

char letter(double avg)
{
    if (avg >= 90) return 'A';
    if (avg >= 80) return 'B';
    if (avg >= 70) return 'C';
    return 'F';
}

// Returns the row, or nothing + a reason
std::optional<Row> parse(const std::string& line, std::string& reason)
{
    std::istringstream fields{line};
    Row row;
    if (!std::getline(fields, row.name, ',') || row.name.empty()) {
        reason = "missing name";
        return std::nullopt;
    }
    for (int& score : row.scores) {
        std::string text;
        if (!std::getline(fields, text, ',')) {
            reason = "missing score";
            return std::nullopt;
        }
        try {
            std::size_t used{};
            score = std::stoi(text, &used);
            if (used != text.size()) throw std::invalid_argument{"trailing text"};
        } catch (const std::exception&) {
            reason = "not a number: '" + text + "'";
            return std::nullopt;
        }
        if (score < 0 || score > 100) {
            reason = "score out of range: " + text;
            return std::nullopt;
        }
    }
    return row;
}

int main()
{
    std::ifstream in{"grades.csv"};
    if (!in) {
        std::cerr << "Cannot open grades.csv\n";
        return 1;
    }

    std::vector<Row> rows;
    int skipped{0};
    std::string line;
    std::getline(in, line);   // header
    for (int lineNo = 2; std::getline(in, line); ++lineNo) {
        std::string reason;
        if (auto row = parse(line, reason)) rows.push_back(*row);
        else {
            ++skipped;
            std::cerr << "warning: line " << lineNo << " skipped (" << reason << ")\n";
        }
    }

    std::sort(rows.begin(), rows.end(), [](const Row& a, const Row& b) { return a.average() > b.average(); });

    std::ofstream out{"report.txt"};
    out << std::fixed << std::setprecision(1);
    out << std::left << std::setw(10) << "Name" << std::right << std::setw(6) << "Math" << std::setw(9) << "English"
        << std::setw(9) << "Science" << std::setw(9) << "Average" << std::setw(7) << "Grade" << '\n';
    out << std::string(50, '-') << '\n';
    std::array<double, 3> subjectTotals{};
    for (const auto& r : rows) {
        out << std::left << std::setw(10) << r.name << std::right << std::setw(6) << r.scores[0] << std::setw(9)
            << r.scores[1] << std::setw(9) << r.scores[2] << std::setw(9) << r.average() << std::setw(7)
            << letter(r.average()) << '\n';
        for (int i = 0; i < 3; ++i) subjectTotals[i] += r.scores[i];
    }
    out << std::string(50, '-') << '\n';
    if (!rows.empty()) {
        out << std::left << std::setw(10) << "Class avg" << std::right;
        const int widths[]{6, 9, 9};
        for (int i = 0; i < 3; ++i) out << std::setw(widths[i]) << subjectTotals[i] / static_cast<double>(rows.size());
        out << '\n';
    }

    std::cout << "Report written: " << rows.size() << " students, " << skipped << " rows skipped\n";
}
