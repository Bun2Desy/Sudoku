cmake_minimum_required(VERSION 3.16)

project(Sudoku VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Boost_USE_STATIC_LIBS ON) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH C:/Qt/6.6.3/mingw_64/lib/cmake)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/form/data/file_easy.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/form/data/file_normal.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/form/data/file_hard.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

qt_standard_project_setup()

include_directories(C:/boost_1_84_0)
add_subdirectory(form/network)
add_subdirectory(form/sudoku)
add_subdirectory(form/graphic)

add_executable(main main.cpp)

target_link_libraries(main network)
target_link_libraries(main sudoku)
target_link_libraries(main graphic)
target_link_libraries(main Qt6::Widgets Qt6::Core Qt6::Gui)

include_directories(form/sudoku)
add_executable(test_sudoku form/sudoku/sudoku.cpp form/test/test_sudoku.cpp)
enable_testing()
add_test(NAME test_sudoku COMMAND test_sudoku --force-colors -d)