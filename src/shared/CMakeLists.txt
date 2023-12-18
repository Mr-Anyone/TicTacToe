add_library(TicTacToeShared STATIC shared.cpp)
target_link_libraries(TicTacToeShared sfml-network)
target_include_directories(TicTacToeShared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(network_test shared_test.cpp)
target_link_libraries(network_test TicTacToeShared sfml-network)
target_include_directories(network_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# adding a test to make sure we can send packets
add_test(
    NAME network_test 
    COMMAND $<TARGET_FILE:network_test>
)