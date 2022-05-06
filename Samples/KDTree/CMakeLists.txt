# CMakeList.txt : CMake project for KDTree, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (KdTreeTest "KdTreeTest.cpp")

target_link_libraries(KdTreeTest libKdTree)

target_compile_features(KdTreeTest PUBLIC cxx_std_17)

add_library(libKdTree "KdTree.cpp" "KdTree.h")

target_compile_features(libKdTree PUBLIC cxx_std_17)

target_include_directories(libKdTree PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> )

# TODO: Add tests and install targets if needed.
