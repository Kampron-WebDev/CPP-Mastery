# Lesson 60: The Senior Developer Roadmap ⭐ NEW

> **In one sentence:** Knowing C++ makes you a C++ programmer. Becoming a **senior developer**
> also takes tools, habits, communication and judgement. This lesson is your map for the journey after this course.

---

## 🧸 The Big Idea: from cook to head chef

A **junior** cook follows recipes. A **mid-level** cook runs a station on their own.
A **head chef** (senior) designs the menu, keeps the kitchen running under pressure, trains others, and knows which shortcuts will poison someone.

| Level | You can… | Typical focus |
|-------|----------|---------------|
| Junior | Complete well-defined tasks with guidance | Language, tools, debugging, asking good questions |
| Mid-level | Own features end-to-end independently | Design within a component, testing, code reviews |
| **Senior** | Own *systems*; make trade-offs; multiply the team | Architecture, reliability, mentoring, communication, saying "no" to bad ideas |

Seniority is **judgement + impact**, not years or clever syntax.

---

## 🛠️ 1. Tools every professional uses

- **Git** (non-negotiable). Learn: `clone, status, add, commit, log, diff, branch, switch, merge, rebase, push, pull`, pull requests, resolving conflicts.
  Habits: small commits, messages that explain *why*, never commit build outputs (see `.gitignore`).
  ```
  git init
  git add .
  git commit -m "Add task persistence with atomic save"
  ```
- **CMake** (Lesson 56) + a package manager (vcpkg/Conan).
- **Debugger** (Lesson 23), **sanitizers**, **clang-tidy**, **clang-format** (Lesson 55).
- **A profiler** (Lesson 58).
- **Linux + the terminal**: most C++ servers run on Linux. Learn bash, `grep`, `find`, `ssh`, `top`, `gdb`, `valgrind`, `perf`. WSL on Windows is an easy start.
- **CI/CD**: GitHub Actions running build + tests + warnings on every push.

## 📖 2. Reading code (a skill of its own)

You'll read 10× more code than you write. Practise on real projects:
- Start from `main()` or a test, follow one feature end to end, and draw what you learn.
- Use "Go to Definition" (F12) and "Find All References" (Shift+F12) in VS Code.
- Good codebases to read: **fmt**, **nlohmann/json**, **spdlog**, **Catch2**, **SerenityOS**, parts of **LLVM**.

## 🧱 3. Design and architecture

- SOLID, patterns, composition over inheritance (Lesson 57).
- **API design**: easy to use correctly, hard to use incorrectly (strong types, `explicit`, `[[nodiscard]]`, RAII).
- **Error-handling strategy**: exceptions vs `expected` vs error codes, and being *consistent*.
- **Layering**: UI → application logic → domain → infrastructure (files, network, DB). Dependencies point inwards.
- Write a short **design doc** before big changes: problem, options, trade-offs, decision.

## 🌍 4. Where C++ is used: pick a direction

| Domain | Learn next |
|--------|------------|
| Games | Unreal Engine, SDL/SFML, raylib, linear algebra, ECS architecture |
| Systems / backends | Linux, networking (sockets, Boost.Asio), databases, gRPC/protobuf |
| Finance (low latency) | Lock-free programming, cache/CPU internals, profiling, kernel bypass |
| Embedded / IoT / automotive | Microcontrollers, no-heap/no-exception C++, RTOS, MISRA/AUTOSAR rules |
| Desktop apps | Qt, Dear ImGui |
| AI / scientific computing | CUDA, Eigen, SIMD, PyTorch C++ internals, Python bindings (pybind11) |
| Tools / compilers | LLVM/Clang, parsing (your Expression Calculator was step one!) |

## 🎯 5. Interview preparation

1. **Data structures & algorithms** (Lesson 54): solve 100–150 problems (easy → medium) on LeetCode in C++; learn the patterns, not the answers.
2. **C++ knowledge questions**: RAII, Rule of 0/3/5, move semantics, virtual dispatch & vtables, smart pointers, `const`, UB, templates vs virtuals, STL container trade-offs, `std::vector` growth, iterator invalidation, exceptions & safety guarantees, threads & data races. Every one is in this course. Use each lesson's *Check yourself* as flashcards.
3. **System design** (for senior roles): caches, queues, load balancing, databases, consistency. Read *Designing Data-Intensive Applications*.
4. **Behavioural**: prepare stories with the STAR format (Situation, Task, Action, Result) about bugs you fixed, conflicts, and projects you finished (your capstones!).
5. Practise **thinking out loud** while coding. Interviewers grade your reasoning.

## 📚 6. Books, from beginner to senior

| Book | Why |
|------|-----|
| *A Tour of C++* (Stroustrup) | Modern C++ overview by its creator |
| *Effective Modern C++* (Meyers) | 42 essential lessons on C++11/14 |
| *C++ Core Guidelines* (free online, isocpp.github.io) | The community rulebook. Look up rules as you code |
| *C++ Concurrency in Action* (Williams) | Threads done right |
| *Clean Code* (Martin) / *The Pragmatic Programmer* | Professional habits |
| *Grokking Algorithms* → *Introduction to Algorithms* | DSA, gentle then deep |
| *Designing Data-Intensive Applications* (Kleppmann) | System design |

Reference websites: **cppreference.com** (the definitive library reference), **Compiler Explorer** (godbolt.org: see the assembly your code produces), **C++ Weekly** (Jason Turner's YouTube channel), **CppCon** talks.

## 🗓️ 7. A 12-month plan (≈ 1–2 hours a day)

| Months | Focus | Output |
|--------|-------|--------|
| 1–2 | Lessons 00–25 + all exercises | Solid fundamentals; DSA easy problems |
| 3–4 | Lessons 26–42 (OOP, templates, move) | Capstones 01 & 03 on GitHub |
| 5–6 | Lessons 43–52 (STL, ranges, files, RAII) | Capstones 02 & 04; 50 LeetCode problems |
| 7–8 | Lessons 53–58 (threads, DSA, testing, CMake, patterns, performance) | Capstones 06 & 07 with CMake + tests + CI |
| 9–10 | Choose a domain (section 4); build something real in it | A project you're proud to demo |
| 11–12 | Contribute to open source (start with docs/tests on a small project); interview prep | Pull requests merged; applications sent |

## 🧠 8. Senior habits

- **Ownership:** you finish things, including tests, docs and the boring 20%.
- **Clarity over cleverness:** the best code is the code a tired teammate understands at 2 a.m.
- **Measure, then decide:** in performance, in estimates, in debates.
- **Communicate early:** "I'm blocked", "this will take longer", "I found a risk" are senior sentences.
- **Review kindly and thoroughly:** explain *why*, suggest alternatives, and praise good work.
- **Teach:** explaining a concept (maybe to a primary school kid!) is the best test of your own understanding.
- **Keep learning:** C++26 is coming (reflection! contracts!). Read the release notes of each standard.

---

## ✅ Final self-assessment

Can you, **without looking**:
- [ ] Explain RAII and write a move-only resource wrapper?
- [ ] Say when to use `unique_ptr` vs `shared_ptr` vs a raw pointer vs a reference?
- [ ] Implement a class with correct Rule-of-Five semantics and explain copy-and-swap?
- [ ] Pick the right STL container for a problem and state its Big-O?
- [ ] Find a data race and fix it; explain how deadlock happens?
- [ ] Write a CMake project with a library, an app and tests?
- [ ] Debug a crash using the call stack?
- [ ] Review code with the Lesson 55 checklist?

Every "no" is simply your next lesson to revisit. Welcome to the journey. **Keep building!** 🚀

**Back to the start:** [Course home](../README.md)
