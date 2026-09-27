// ⭐⭐⭐ Exercise 01: FibonacciGenerator
// Write a class template Generator<T> with a promise_type so that this works:
//
//   Generator<long long> fibonacci() {
//       long long a = 0, b = 1;
//       while (true) { co_yield a; auto next = a + b; a = b; b = next; }   // INFINITE, but lazy!
//   }
//   auto gen = fibonacci();
//   for (int i = 0; i < 10 && gen.next(); ++i) std::cout << gen.value() << ' ';
//
// Requirements:
//   - bool next()  resumes the coroutine, returns false when it's finished
//   - T value() const  returns the last yielded value
//   - the destructor destroys the handle (RAII); copying is deleted, moving allowed
// Bonus: also write a finite generator  range(from, to)  and use it.
#include <iostream>
#include <coroutine>

int main()
{
    // TODO
}
