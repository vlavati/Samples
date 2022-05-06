# CMakeList.txt : CMake project for KMeans, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (BreadthestSearch "BreadthestSearch.cpp" "BreadthestSearch.h")

target_compile_features(BreadthestSearch PUBLIC cxx_std_17)

target_link_libraries(BreadthestSearch libGraph)


add_library(libGraph INTERFACE "Graph.h" "WeightGraph.h")

target_compile_features(libGraph INTERFACE cxx_std_17)

target_include_directories(libGraph INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> )