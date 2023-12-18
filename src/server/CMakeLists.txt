file(GLOB SERVER_SOURCE
    *.cpp
)

add_executable(TicTacToeServer ${SERVER_SOURCE})
target_link_libraries(TicTacToeServer TicTacToeShared sfml-network)
target_include_directories(TicTacToeServer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)