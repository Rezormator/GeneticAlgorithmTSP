#include <iostream>
#include "Core/AdjacencyMatrixGenerator/AdjacencyMatrixGenerator.h"
#include "Core/Evaluator/Evaluator.h"
#include "ParallelGeneticAlgorithm/IslandGeneticAlgorithm/IslandGeneticAlgorithm.h"
#include <chrono>

int main() {
    constexpr Configurations configurations;

    const auto adjacencyMatrix = AdjacencyMatrixGenerator::GenerateAdjacencyMatrix(configurations.cityCount);

    const Evaluator evaluator(adjacencyMatrix);

    IslandGeneticAlgorithm islandGeneticAlgorithm(4, configurations, evaluator);
    const auto chromosome = islandGeneticAlgorithm.Run();

    for (int i = 0; i < chromosome.genes.size() - 1; i++) {
    std::cout << chromosome.genes[i] << " -> ";
    }
    std::cout << chromosome.genes[chromosome.genes.size() - 1] << std::endl;
    std::cout << chromosome.fitness;

    return 0;
}
