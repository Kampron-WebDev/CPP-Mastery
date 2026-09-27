# Lesson 48: Coroutines (C++20)

> **In one sentence:** A coroutine is a function that can **pause** in the middle (`co_yield`,
> `co_await`) and later **resume** exactly where it left off, keeping all its local variables.

(Sub-folders are numbered `47.x` from the original course recording. They belong to this lesson.)

---

## 🎯 You will learn

- What makes a function a coroutine: `co_await`, `co_yield`, `co_return`.
- The promise type, coroutine handle, and awaiters (`std::suspend_always`, `std::suspend_never`).
- Writing a generator.
- Why most people use a coroutine *library* (or C++23 `std::generator`).

---

## 🧸 The Big Idea: a bookmark

A normal function is like reading a whole book in one sitting: start → end, no stopping.
A coroutine is reading with a **bookmark**: read a chapter, put the bookmark in (`co_yield`),
go do something else, come back and **continue from the bookmark**. Your place and your notes
(local variables) are still there.

```cpp
Generator countTo(int n)
{
    for (int i = 1; i <= n; ++i)
        co_yield i;        // hand out i, then PAUSE here
}
for (int x : countTo(3)) std::cout << x;   // 1 2 3, each value produced only when asked
```

---

## 📚 The moving parts (simplified)

```
 caller                                coroutine frame (on the heap)
 ──────                                ─────────────────────────────
 auto gen = countTo(3);   ─create──►   locals (i), the promise, the resume point
 gen.next()               ─resume──►   runs until co_yield 1 → pauses
 reads the value          ◄─value───   promise.current = 1
 gen.next()               ─resume──►   continues after co_yield ... yields 2
 ...                                   co_return / end → final_suspend
 gen destroyed            ─destroy─►   frame freed
```

| Piece | Role |
|-------|------|
| **Return type** (e.g. `Generator`) | What the caller holds. Must contain a nested `promise_type` |
| **`promise_type`** | The coroutine's "control panel": `get_return_object`, `initial_suspend`, `final_suspend`, `yield_value`, `return_void`/`return_value`, `unhandled_exception` |
| **`std::coroutine_handle<promise_type>`** | A remote control: `resume()`, `done()`, `destroy()`, `promise()` |
| **Awaiter** | Decides whether to pause: `std::suspend_always` (pause) / `std::suspend_never` (don't) |

- `co_yield x` → calls `promise.yield_value(x)` then usually suspends.
- `co_return x` → calls `promise.return_value(x)` (or `return_void()` for plain `co_return;`).
- `co_await expr` → asks an awaiter whether/how to suspend (used for async I/O).

## 🗂️ Code in this folder

| Folder | Topic |
|--------|-------|
| [47.5CoAwait](47.5CoAwait/main.cpp) | `co_await` and suspension |
| [47.6CoYield](47.6CoYield/main.cpp) | `co_yield` values (fixed: added the required `return_void()`) |
| [47.7CoReturn](47.7CoReturn/main.cpp) | Returning a final value |
| [47.8CustomGenerator](47.8CustomGenerator/main.cpp) | A reusable generator type |
| [47.9ThirdPartyCorotineTypes](47.9ThirdPartyCorotineTypes/main.cpp) | Using library coroutine types |

## ⚠️ Common mistakes

- `co_return;` without `return_void()` in the promise (a compile error; that was the bug fixed in 47.6).
- Forgetting to `destroy()` the handle → leak. Wrap it in an RAII class (destructor calls `destroy`).
- Resuming a coroutine that is `done()` → undefined behaviour.
- Coroutines capturing references to locals of the caller that die first.

## 🧠 Senior developer notes

- C++20 gives the *machinery*, not ready-made types. In practice use **C++23 `std::generator`** or libraries
  (cppcoro, folly, Boost.Asio, libunifex) for generators and async tasks.
- Coroutines shine for **async I/O** (network servers handling thousands of connections), **lazy sequences**, and **state machines**.

## ✅ Check yourself

1. What makes a function a coroutine?
2. What does `co_yield` do?
3. Why wrap the coroutine handle in a class?

<details><summary>Answers</summary>

1. Using `co_await`, `co_yield` or `co_return` in its body.
2. Passes a value to the promise (`yield_value`) and suspends the coroutine.
3. So the destructor calls `destroy()` automatically (RAII), preventing leaks.
</details>

## 🏋️ Exercises → [Exercises/README.md](Exercises/README.md)

**Next:** [Lesson 49: Modules](../49.Modules/README.md)
