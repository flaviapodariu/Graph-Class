cmake_minimum_required(VERSION 3.17)
project(Graph-Class)

set(CMAKE_CXX_STANDARD 14)

add_executable(Graph-Class main.cpp Graph.cpp Graph.h DirectedGraph.cpp DirectedGraph.h UndirectedGraph.cpp UndirectedGraph.h biconex.in)