cmake_minimum_required(VERSION 3.14)
project(BLOCKY-CHESS-ENGINE)

option(MAKE_EXE "exe?" ON)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


enable_testing()
add_executable(
    allTests
    testBitBoard.cpp
    testBoard.cpp
    testMoveGen.cpp
    ../src/zobrist.cpp
    ../src/bitboard.cpp
    ../src/attacks.cpp
    ../src/move.cpp
    ../src/board.cpp
    ../src/moveGen.cpp
    ../src/movePicker.cpp
    ../src/timeman.cpp
    ../src/search.cpp
    ../src/eval.cpp
)
target_include_directories(
    allTests PUBLIC "../src/"
)
target_link_libraries(
    allTests
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(allTests)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wfloat-equal -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow -Woverloaded-virtual")