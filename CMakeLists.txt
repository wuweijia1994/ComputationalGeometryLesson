cmake_minimum_required(VERSION 3.15)
project(unconvex_point_search)

add_definitions("-Wall -g")

add_executable(test_convex_hull
    test.cpp 
    search.cpp
    search.h
    point.h
)