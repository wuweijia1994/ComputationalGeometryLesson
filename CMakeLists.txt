cmake_minimum_required(VERSION 3.15)
project(ComputationalGeometryLib)

include_directories(
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/third_party
)

add_library(${PROJECT_NAME} 
  ${CMAKE_SOURCE_DIR}/src/point.cpp
  ${CMAKE_SOURCE_DIR}/src/convex_hull.cpp
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_range_for)

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

message(${PYTHON_INCLUDE_DIRS})

add_definitions("-Wall -g")

# add_executable(test_convex_hull ${CMAKE_SOURCE_DIR}/test/test.cpp)

# target_link_libraries(test_convex_hull INTERFACE
# ${PYTHON_LIBRARIES}
#   ${PROJECT_NAME}
# )