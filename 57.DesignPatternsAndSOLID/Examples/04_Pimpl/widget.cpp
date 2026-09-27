#include "widget.h"

#include <vector>

struct Widget::Impl {                       // all the private details live here
    std::string name;
    int clicks{0};
    std::vector<std::string> log;
};

Widget::Widget(std::string name) : impl{std::make_unique<Impl>()} { impl->name = std::move(name); }
Widget::~Widget() = default;
Widget::Widget(Widget&&) noexcept = default;
Widget& Widget::operator=(Widget&&) noexcept = default;

void Widget::click()
{
    ++impl->clicks;
    impl->log.push_back("click #" + std::to_string(impl->clicks));
}

std::string Widget::describe() const
{
    return impl->name + " clicked " + std::to_string(impl->clicks) + " times (last: " +
           (impl->log.empty() ? "never" : impl->log.back()) + ")";
}
