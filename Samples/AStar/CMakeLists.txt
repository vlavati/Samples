# CMakeList.txt : CMake project for KMeans, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (AStar "AStar.cpp" "AStar.h")

target_compile_features(AStar PUBLIC cxx_std_17)

target_link_libraries(AStar libGraph)
