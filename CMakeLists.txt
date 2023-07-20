cmake_minimum_required(VERSION 3.23)
project(minesweeper)

set(CMAKE_CXX_STANDARD 14)

add_executable(minesweeper main.cpp globalConsts.h cell.h board.h board.cpp cell.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/Users/alexe/SFML64/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/Users/alexe/SFML64/include)
target_link_libraries(minesweeper sfml-system sfml-window sfml-graphics sfml-audio sfml-network)