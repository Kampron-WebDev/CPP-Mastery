#include <iostream>
#include <string>
#include <cctype>

std::string encrypt(const std::string& text, int shift)
{
    shift = ((shift % 26) + 26) % 26;   // make any shift (even negative) 0..25
    std::string result = text;
    for (char& c : result) {
        const auto uc = static_cast<unsigned char>(c);
        if (std::isupper(uc))      c = static_cast<char>('A' + (c - 'A' + shift) % 26);
        else if (std::islower(uc)) c = static_cast<char>('a' + (c - 'a' + shift) % 26);
    }
    return result;
}

std::string decrypt(const std::string& text, int shift)
{
    return encrypt(text, -shift);   // shifting back = shifting forward by the negative
}

int main()
{
    const std::string secret = encrypt("Hello, World!", 3);
    std::cout << secret << '\n';                 // Khoor, Zruog!
    std::cout << decrypt(secret, 3) << '\n';     // Hello, World!
    std::cout << std::boolalpha << (secret == "Khoor, Zruog!") << '\n';
}
