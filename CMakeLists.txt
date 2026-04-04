cmake_minimum_required(VERSION 3.30)
project(GeneticAlgorithmTSP)

set(CMAKE_CXX_STANDARD 20)

add_executable(GeneticAlgorithmTSP src/main.cpp
        src/Utils/Utils.cpp
        src/Utils/Utils.h
        src/Core/Chromosome/Chromosome.cpp
        src/Core/Chromosome/Chromosome.h
        src/Core/Population/Population.cpp
        src/Core/Population/Population.h
        src/Core/AdjacencyMatrixGenerator/AdjacencyMatrixGenerator.cpp
        src/Core/AdjacencyMatrixGenerator/AdjacencyMatrixGenerator.h
        src/Core/Evaluator/Evaluator.cpp
        src/Core/Evaluator/Evaluator.h
        src/Core/Operators/Operators.cpp
        src/Core/Operators/Operators.h
        src/ParallelGeneticAlgorithm/IslandThread/IslandThread.cpp
        src/ParallelGeneticAlgorithm/IslandThread/IslandThread.h
        src/ParallelGeneticAlgorithm/Configurations.h
        src/ParallelGeneticAlgorithm/MigrationManager/MigrationManager.cpp
        src/ParallelGeneticAlgorithm/MigrationManager/MigrationManager.h
        src/ParallelGeneticAlgorithm/IslandGeneticAlgorithm/IslandGeneticAlgorithm.cpp
        src/ParallelGeneticAlgorithm/IslandGeneticAlgorithm/IslandGeneticAlgorithm.h
        src/GeneticAlgorithm/GeneticAlgorithm.cpp
        src/GeneticAlgorithm/GeneticAlgorithm.h)
