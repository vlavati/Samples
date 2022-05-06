# CMakeList.txt : CMake project for RandomTreap, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (RandomTreap "RandomTreap.cpp" "RandomTreap.h")

target_compile_features(RandomTreap PUBLIC cxx_std_17)
# TODO: Add tests and install targets if needed.
