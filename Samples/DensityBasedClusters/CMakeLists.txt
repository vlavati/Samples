# CMakeList.txt : CMake project for DensityBasedClusters, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (DensityBasedClusters "DensityBasedClusters.cpp" "DensityBasedClusters.h")

target_compile_features(DensityBasedClusters PUBLIC cxx_std_17)
target_link_libraries(DensityBasedClusters libKdTree)

# TODO: Add tests and install targets if needed.
