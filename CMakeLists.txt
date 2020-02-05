cmake_minimum_required(VERSION 3.14)
project(lab1_graphs_algo)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab1_graphs_algo main.cpp stress_tests.h stress_tests.cpp Graph.h check_bridge.h find_bridges.h weights_sort.h real_graph.h experiments.h)