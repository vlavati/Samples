# CMakeList.txt : CMake project for Disjointed, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (Disjointed "Disjointed.cpp" "Disjointed.h")

target_compile_features(Disjointed PUBLIC cxx_std_17)
# TODO: Add tests and install targets if needed.
