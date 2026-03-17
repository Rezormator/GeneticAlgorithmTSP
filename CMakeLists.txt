cmake_minimum_required(VERSION 3.30)
project(GeneticAlgorithmTSP)

set(CMAKE_CXX_STANDARD 20)

add_executable(GeneticAlgorithmTSP src/main.cpp
        src/Utils/Utils.cpp
        src/Utils/Utils.h
        src/Chromosome/Chromosome.cpp
        src/Chromosome/Chromosome.h
        src/Population/Population.cpp
        src/Population/Population.h
        src/AdjacencyMatrix/AdjacencyMatrix.cpp
        src/AdjacencyMatrix/AdjacencyMatrix.h
        src/GeneticAlgorithm/GeneticAlgorithm.cpp
        src/GeneticAlgorithm/GeneticAlgorithm.h)
