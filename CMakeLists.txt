cmake_minimum_required(VERSION 3.14) 

option(MAKE_EXE "exe?" OFF)

project(Blocky)

add_executable(Blocky src/main.cpp)

if(MAKE_EXE)
    message("Compiling for Windows EXE")
    set(CMAKE_SYSTEM_NAME Windows)
    set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
    set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
    set(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)
    set(CMAKE_FIND_ROOT_PATH /usr/x86_64-w64-mingw32)

    set(CMAKE_SYSTEM_PROCESSOR x86_64)
    set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/toolchain-mingw64.cmake)
endif(MAKE_EXE)
unset(MAKE_EXE CACHE)

target_sources(Blocky PRIVATE
    src/zobrist.cpp
    src/bitboard.cpp
    src/attacks.cpp
    src/move.cpp
    src/board.cpp
    src/moveGen.cpp
    src/movePicker.cpp
    src/search.cpp
    src/eval.cpp
    src/timeman.cpp
    src/uci.cpp
)

target_include_directories(Blocky PRIVATE
    src
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")