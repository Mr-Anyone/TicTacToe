cmake_minimum_required(VERSION 3.0.0)
project(TicTacToe VERSION 0.1.0 LANGUAGES CXX)
SET(CMAKE_CXX_STANDARD 20)

enable_testing()

#include dependencies
add_subdirectory(vendor)
add_subdirectory(src)

# CPACK Stuff
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
