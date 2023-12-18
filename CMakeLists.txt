cmake_minimum_required(VERSION 3.0.0)
project(TicTacToe VERSION 0.1.0 LANGUAGES CXX)
SET(CMAKE_CXX_STANDARD 17)
#include dependencies
add_subdirectory(vendor)

file(GLOB TICTACTOE_SOURCE_FILES
    src/*.cpp
)

add_executable(TicTacToe ${TICTACTOE_SOURCE_FILES})
target_include_directories(TicTacToe PRIVATE ${PROJECT_SOURCE_DIR}/include)

# CPACK Stuff
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
