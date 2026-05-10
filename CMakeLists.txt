cmake_minimum_required(VERSION 3.16)
project(time_wheel LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

include_directories(include)

file(GLOB_RECURSE SRC src/*.cpp)

add_executable(time_wheel_demo ${SRC})
