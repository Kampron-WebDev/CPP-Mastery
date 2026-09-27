# Lesson 01 Exercises

| # | Exercise | Level | Skill |
|---|----------|-------|-------|
| 01 | [BinaryByHand](01_BinaryByHand/main.cpp) | ⭐ | Counting in binary |
| 02 | [MemoryDetective](02_MemoryDetective/main.cpp) | ⭐⭐ | sizeof and addresses |

<details><summary>Hint for 01</summary>

Write the place values `128 64 32 16 8 4 2 1` above the bits, then add up the places where the bit is 1.
</details>

<details><summary>Hint for 02</summary>

Subtract two addresses by printing them, then look at the last hex digits. Two `int` variables
declared next to each other are often 4 bytes apart, but the compiler is free to arrange them however it likes.
</details>
