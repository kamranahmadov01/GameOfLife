cmake_minimum_required(VERSION 3.0)

project(gui LANGUAGES C)

set(SOURCES gui.c)
set(HEADERS gui.h)


set(CMAKE_BUILD_TYPE Release)

include_directories(${SDL2_INCLUDE_DIRS})

add_library(gui)

target_sources(gui PRIVATE ${SOURCES} ${HEADERS})
target_include_directories(board INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(gui PUBLIC ${SDL2_LIBRARIES} board)