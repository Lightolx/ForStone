cmake_minimum_required(VERSION 3.14)
project(ForStone)

set(CMAKE_CXX_STANDARD 14)

find_package(Sophus REQUIRED)
include_directories(${Sophus_INCLUDE_DIRS})

add_executable(triangulate triangulate.cpp)
target_link_libraries(triangulate ${Sophus_LIBRARIES})

add_executable(SortList List.cpp)

add_executable(SortVector SortVector.cpp)