// Parse a CSV file into structs, skipping and reporting bad lines.
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Student {
    std::string name;
    int age{};
    double score{};
};

int main()
{
    // Create a sample file so the example is self-contained
    {
        std::ofstream out{"students.csv"};
        out << "name,age,score\n"
            << "Ama,19,88.5\n"
            << "Kofi,twenty,70\n"   // bad age
            << "Esi,20,91\n"
            << "Yaw,18\n";          // missing column
    }

    std::ifstream in{"students.csv"};
    std::string line;
    std::getline(in, line);   // skip the header row

    std::vector<Student> students;
    for (int lineNo = 2; std::getline(in, line); ++lineNo) {
        std::istringstream fields{line};
        std::string name, ageText, scoreText;
        if (!std::getline(fields, name, ',') || !std::getline(fields, ageText, ',') || !std::getline(fields, scoreText)) {
            std::cerr << "line " << lineNo << ": wrong number of columns: \"" << line << "\"\n";
            continue;
        }
        try {
            students.push_back({name, std::stoi(ageText), std::stod(scoreText)});
        } catch (const std::exception&) {
            std::cerr << "line " << lineNo << ": bad number in \"" << line << "\"\n";
        }
    }

    std::cout << "Loaded " << students.size() << " students:\n";
    for (const auto& s : students) std::cout << "  " << s.name << " (" << s.age << "): " << s.score << '\n';

    // ostringstream: build text with << and get it as a string
    std::ostringstream summary;
    summary << students.size() << " valid rows";
    std::cout << summary.str() << '\n';
}
