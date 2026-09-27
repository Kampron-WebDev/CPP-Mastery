cmake_minimum_required(VERSION 3.20)
project(StatsDemo VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---- the library ----
add_library(stats src/stats.cpp)
target_include_directories(stats PUBLIC include)
target_compile_options(stats PRIVATE -Wall -Wextra -Wpedantic)

# ---- the application ----
add_executable(stats_app app/main.cpp)
target_link_libraries(stats_app PRIVATE stats)

# ---- the tests ----
enable_testing()
add_executable(stats_tests tests/test_stats.cpp)
target_link_libraries(stats_tests PRIVATE stats)
add_test(NAME stats_tests COMMAND stats_tests)
