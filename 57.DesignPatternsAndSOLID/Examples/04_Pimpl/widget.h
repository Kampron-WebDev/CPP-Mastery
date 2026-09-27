#pragma once
#include <memory>
#include <string>

// PIMPL: the header shows only the public API. No private members, no heavy #includes.
// Changing the implementation does NOT force every user of widget.h to recompile.
class Widget {
public:
    explicit Widget(std::string name);
    ~Widget();                              // must be defined in the .cpp (where Impl is complete)
    Widget(Widget&&) noexcept;
    Widget& operator=(Widget&&) noexcept;

    void click();
    std::string describe() const;

private:
    struct Impl;                            // forward declaration only
    std::unique_ptr<Impl> impl;
};
