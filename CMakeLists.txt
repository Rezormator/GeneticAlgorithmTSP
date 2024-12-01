cmake_minimum_required(VERSION 3.28)
project(GeneticAlgorithmTSP)

set(CMAKE_CXX_STANDARD 20)

add_executable(GeneticAlgorithmTSP main.cpp
        RandomGenerator/RandomGenerator.h
        RandomGenerator/RandomGenerator.cpp
        Utils.h
        GeneticAlgorithm/GeneticAlgorithm.h
        GeneticAlgorithm/GeneticAlgorithm.cpp
        AdjacencyMatrix/AdjacencyMatrix.h
        AdjacencyMatrix/AdjacencyMatrix.cpp
        Route/Route.h
        Route/Route.cpp
        Population/Population.h
        Population/Population.cpp)
