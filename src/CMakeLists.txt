project(my_logsystem)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++11 ") 
set(CMAKE_INSTALL_RPATH "$ORIGIN;$ORIGIN/lib")
set(OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../output" CACHE PATH "Speciry the output path.")
set(SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR})

OPTION(DEBUG_MODE "Set the compile mode" OFF)
if(DEBUG_MODE)
    set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -O0 -g ") 
else()
    set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -O3 ") 
endif(DEBUG_MODE)


OPTION(ENABLE_ASAN "Enable asan" OFF)
if(ENABLE_ASAN)
    set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -fsanitize=address ") 
endif(ENABLE_ASAN)


OPTION(ENABLE_GCOV "Enable gcov" OFF)
if(ENABLE_GCOV)
    set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage ") 
endif(ENABLE_GCOV)

add_subdirectory(lib)
add_subdirectory(unittest)

