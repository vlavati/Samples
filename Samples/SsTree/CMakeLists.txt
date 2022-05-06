# CMakeList.txt : CMake project for SsTree, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (SsTree "SsTree.cpp" "SsTree.h")

target_compile_features(SsTree PUBLIC cxx_std_17)
