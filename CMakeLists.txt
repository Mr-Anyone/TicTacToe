cmake_minimum_required(VERSION 3.20.0)
project(TicTacToe VERSION 0.1.0 LANGUAGES CXX)
SET(CMAKE_CXX_STANDARD 20)

enable_testing()

#include dependencies
add_subdirectory(vendor)
add_subdirectory(src)

# Packaging application
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CPACK_GENERATOR NSIS)

install(TARGETS TicTacToe RUNTIME DESTINATION bin)
install(TARGETS TicTacToeServer RUNTIME DESTINATION bin)
install(FILES ${CMAKE_SOURCE_DIR}/Starborn.ttf DESTINATION bin)

include(CPack)