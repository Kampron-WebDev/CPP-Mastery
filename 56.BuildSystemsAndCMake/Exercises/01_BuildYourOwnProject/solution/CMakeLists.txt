cmake_minimum_required(VERSION 3.20)
project(TextTools VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(texttools src/texttools.cpp)
target_include_directories(texttools PUBLIC include)
target_compile_options(texttools PRIVATE -Wall -Wextra -Wpedantic)

add_executable(texttools_app app/main.cpp)
target_link_libraries(texttools_app PRIVATE texttools)

enable_testing()
add_executable(texttools_tests tests/test_texttools.cpp)
target_link_libraries(texttools_tests PRIVATE texttools)
add_test(NAME texttools_tests COMMAND texttools_tests)
