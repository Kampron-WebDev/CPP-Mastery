// A generic scope guard + std::unique_ptr with a custom deleter.
#include <cstdio>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

template <typename F>
class ScopeGuard {
public:
    explicit ScopeGuard(F f) : action{std::move(f)} {}
    ~ScopeGuard()
    {
        if (active) action();
    }
    void dismiss() { active = false; }   // "we succeeded, don't run the cleanup"
    ScopeGuard(const ScopeGuard&) = delete;
    ScopeGuard& operator=(const ScopeGuard&) = delete;

private:
    F action;
    bool active{true};
};

// Add items to TWO lists. If the second step fails, undo the first (all-or-nothing).
bool addToBoth(std::vector<int>& a, std::vector<int>& b, int value, bool failSecondStep)
{
    a.push_back(value);
    ScopeGuard undo{[&] { a.pop_back(); std::cout << "  rolled back a\n"; }};
    if (failSecondStep) return false;   // guard fires: a is restored
    b.push_back(value);
    undo.dismiss();                     // success: keep the change
    return true;
}

int main()
{
    std::vector<int> a, b;
    addToBoth(a, b, 1, false);
    addToBoth(a, b, 2, true);
    std::cout << "a has " << a.size() << " item(s), b has " << b.size() << '\n';   // 1 and 1

    // unique_ptr + custom deleter: RAII for a C API in one line
    auto closer = [](std::FILE* f) {
        if (f) {
            std::fclose(f);
            std::cout << "  file closed by the deleter\n";
        }
    };
    std::unique_ptr<std::FILE, decltype(closer)> file{std::fopen("guard.txt", "w"), closer};
    if (file) std::fputs("hi\n", file.get());
}
