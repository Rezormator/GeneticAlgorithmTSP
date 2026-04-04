#include <iostream>
#include "Core/AdjacencyMatrixGenerator/AdjacencyMatrixGenerator.h"
#include "Core/Evaluator/Evaluator.h"
#include "ParallelGeneticAlgorithm/IslandGeneticAlgorithm/IslandGeneticAlgorithm.h"
#include <chrono>

#include "GeneticAlgorithm/GeneticAlgorithm.h"

int main() {
    constexpr Configurations configurations;

    std::vector<std::pair<int, double>> GA;
    std::vector<std::pair<int, double>> PGA;

    for (int i = 0; i < configurations.testIterations; i++) {
        const auto adjacencyMatrix = AdjacencyMatrixGenerator::GenerateAdjacencyMatrix(configurations.cityCount);

        const Evaluator evaluator(adjacencyMatrix);

        {
            auto start = std::chrono::high_resolution_clock::now();
            GeneticAlgorithm geneticAlgorithm(configurations, evaluator);
            const auto chromosome = geneticAlgorithm.Solve();
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;
            GA.emplace_back(chromosome.fitness, duration.count());
        }

        {
            auto start = std::chrono::high_resolution_clock::now();
            IslandGeneticAlgorithm islandGeneticAlgorithm(configurations.treads, configurations, evaluator);
            const auto chromosome = islandGeneticAlgorithm.Run();
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;
            PGA.emplace_back(chromosome.fitness, duration.count());
        }
        std::cout << std::fixed << std::setprecision(2) << 100 / configurations.testIterations * (i + 1) << "% made..."<< std::endl;
    }

    std::cout << "|-----------|------------|-------------|-------------|--------------|-----------|--------|\n";
    std::cout << "| Iteration | GA Fitness | GA Time (s) | PGA Fitness | PGA Time (s) | Fitness D | Time d |\n";
    std::cout << "|-----------|------------|-------------|-------------|--------------|-----------|--------|\n";
    for (int i = 0; i < configurations.testIterations; i++) {
        std::cout << "| " << std::setw(9) << (i + 1) << " | "
                  << std::setw(10) << GA[i].first << " | "
                  << std::setw(11) << std::fixed << std::setprecision(4) << GA[i].second << " | "
                  << std::setw(11) << PGA[i].first << " | "
                  << std::setw(12) << std::fixed << std::setprecision(4) << PGA[i].second << " |"
                  << std::setw(10) << GA[i].first - PGA[i].first << " | "
                  << std::setw(7) << std::fixed << std::setprecision(2) << GA[i].second / PGA[i].second << "|\n";
    }
    std::cout << "|-----------|------------|-------------|-------------|--------------|-----------|--------|\n";

    double avgTimeD = 0;
    int avgFitnessD = 0;
    for (int i = 0; i < configurations.testIterations; i++) {
        avgTimeD += GA[i].second / PGA[i].second;
        avgFitnessD += GA[i].first - PGA[i].first;
    }
    std::cout << "Average time difference: " << avgTimeD / configurations.testIterations << std::endl
              << "Average fitness difference: " << avgFitnessD / configurations.testIterations << std::endl;

    // for (int i = 0; i < chromosome.genes.size() - 1; i++) {
    //     std::cout << chromosome.genes[i] << " -> ";
    // }
    // std::cout << chromosome.genes[chromosome.genes.size() - 1] << std::endl;
    // std::cout << chromosome.fitness;

    return 0;
}
