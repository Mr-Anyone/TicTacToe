file(GLOB TICTACTOE_SOURCE_FILES
    *.cpp
)

add_executable(TicTacToe ${TICTACTOE_SOURCE_FILES})
target_link_libraries(TicTacToe sfml-graphics sfml-system sfml-network TicTacToeShared)
target_include_directories(TicTacToe PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
