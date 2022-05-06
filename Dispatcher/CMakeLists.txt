cmake_minimum_required(VERSION 2.8)

project(Dispatcher)

set(CMAKE_CXX_STANDARD 17)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
