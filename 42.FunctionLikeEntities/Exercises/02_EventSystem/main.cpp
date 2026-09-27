// ⭐⭐⭐ Exercise 02: EventSystem
// Build a tiny event system (the Observer pattern: used in every GUI and game engine):
//   class Button {
//     void onClick(std::function<void(const std::string&)> handler);  // subscribe
//     void click();                                                    // call all handlers
//   };
// Subscribe:
//   1. a lambda printing "Button <label> clicked"
//   2. a lambda that COUNTS clicks in a variable captured BY REFERENCE
//   3. a functor class Logger that keeps its own internal list of messages
//      (hint: store it in a std::shared_ptr<Logger> captured by value, so it stays alive)
//   4. a member function of a class Game via a lambda capturing `this`
// Click 3 times and show every subscriber reacted.
#include <iostream>
#include <functional>
#include <string>
#include <vector>

int main()
{
    // TODO
}
