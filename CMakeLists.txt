cmake_minimum_required(VERSION 3.18)
project(EulerOperation)

set(CMAKE_CXX_STANDARD 14)

AUX_SOURCE_DIRECTORY(src SRC)

add_executable(EulerOperation ${SRC})

target_include_directories(EulerOperation PRIVATE extern/poly2tri/src)

target_link_libraries(EulerOperation
        PRIVATE glfw3 GL dl pthread poly2tri)

add_subdirectory(./extern/poly2tri)