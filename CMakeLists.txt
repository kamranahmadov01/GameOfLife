cmake_minimum_required(VERSION 3.13)
cmake_policy(SET CMP0076 NEW)

project(Game_Of_Life)

add_subdirectory(board)
add_subdirectory(gui)

set(SOURCES main.c)

add_executable(game ${SOURCES})
target_sources(game PUBLIC ${SOURCES})
target_link_libraries(game PUBLIC board gui) 


set(TEST board_tests)
add_executable(${TEST})
target_sources(${TEST} PUBLIC board_tests.c)
target_link_libraries(${TEST} PUBLIC cunit board)