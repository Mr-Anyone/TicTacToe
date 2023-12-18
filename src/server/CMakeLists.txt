file(GLOB SERVER_SOURCE
    *.cpp
)

add_executable(TicTacToeServer ${SERVER_SOURCE})
target_link_libraries(TicTacToeServer TicTacToeShared sfml-network)