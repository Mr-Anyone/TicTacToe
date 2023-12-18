add_library(TicTacToeShared STATIC shared.cpp)
target_include_directories(TicTacToeShared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)