#include <iostream>
#include <string>
#include <string_view>
#include <cctype>

// Returns an empty string when strong, otherwise a list of problems.
std::string problems(std::string_view pw)
{
    bool upper{}, lower{}, digit{}, symbol{}, space{};
    std::string lowered;
    for (char ch : pw) {
        const auto c = static_cast<unsigned char>(ch);
        upper  = upper  || std::isupper(c);
        lower  = lower  || std::islower(c);
        digit  = digit  || std::isdigit(c);
        symbol = symbol || std::ispunct(c);
        space  = space  || std::isspace(c);
        lowered += static_cast<char>(std::tolower(c));
    }

    std::string out;
    if (pw.size() < 10) out += "  - at least 10 characters\n";
    if (!upper)  out += "  - an uppercase letter\n";
    if (!lower)  out += "  - a lowercase letter\n";
    if (!digit)  out += "  - a digit\n";
    if (!symbol) out += "  - a symbol\n";
    if (space)   out += "  - no spaces allowed\n";
    if (lowered.find("password") != std::string::npos) out += "  - must not contain 'password'\n";
    return out;
}

bool isStrong(std::string_view pw) { return problems(pw).empty(); }

int main()
{
    std::string pw;
    while (true) {
        std::cout << "Choose a password: ";
        if (!std::getline(std::cin, pw)) return 1;
        if (isStrong(pw)) break;
        std::cout << "Too weak. Missing:\n" << problems(pw);
    }
    std::cout << "Strong password accepted.\n";
}
