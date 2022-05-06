# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("Samples")

# Include sub-projects.
add_subdirectory ("SimulatedAnnealing")
add_subdirectory (Blooming)
add_subdirectory (DensityBasedClusters)
add_subdirectory (Disjointed)
add_subdirectory (Heapify)
add_subdirectory (KDTree)
add_subdirectory (KMeans)
add_subdirectory (RandomTreap)
add_subdirectory (SsTree)
add_subdirectory (Canopying)
add_subdirectory (BreadthestSearch)
add_subdirectory (DeepestSearch)
add_subdirectory (Dijkstra)
add_subdirectory (AStar)
add_subdirectory (Genetic)
