cmake_minimum_required(VERSION 3.28)
project(GeneticAlgorithmTSP)

set(CMAKE_CXX_STANDARD 20)

add_executable(GeneticAlgorithmTSP main.cpp
        RandomGenerator/RandomGenerator.h
        RandomGenerator/RandomGenerator.cpp
        Graph/Graph.h
        Graph/Graph.cpp
        Utils.h)
