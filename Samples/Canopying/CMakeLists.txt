# CMakeList.txt : CMake project for KMeans, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (Canopying "Canopying.cpp" "Canopying.h")

target_compile_features(Canopying PUBLIC cxx_std_17)

# TODO: Add tests and install targets if needed.
