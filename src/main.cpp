#include <iostream>
#include "Core/AdjacencyMatrixGenerator/AdjacencyMatrixGenerator.h"
#include "Core/Evaluator/Evaluator.h"
#include "ParallelGeneticAlgorithm/IslandGeneticAlgorithm/IslandGeneticAlgorithm.h"
#include <chrono>

#include "GeneticAlgorithm/GeneticAlgorithm.h"

int main() {
    Configurations configurations;

    std::vector<std::pair<int, double>> GA;
    std::vector<std::pair<int, double>> PGA;

    std::vector<int> cityCount = {10, 50, 100, 500, 1000};
    std::vector<int> goalFitness = {2800, 9500, 23000, 200000, 400000, 2600000, 5400000};

    // std::vector<int> cityCount = {10000};
    // std::vector<int> goalFitness = {0, 0, 0, 0, 0, 0, 0};

    for (int i = 0; i < cityCount.size(); i++) {
        std::cout << "Calculations for " << cityCount[i] << " cities:"<< std::endl;

        configurations.cityCount = cityCount[i];
        configurations.goalFitness = goalFitness[i];

        GA.emplace_back(0, 0);
        PGA.emplace_back(0, 0);

        const auto adjacencyMatrix = AdjacencyMatrixGenerator::GenerateAdjacencyMatrix(configurations.cityCount);

        const Evaluator evaluator(adjacencyMatrix);
        for (int j = 0; j < configurations.testIterations; j++) {

            {
                auto start = std::chrono::high_resolution_clock::now();
                std::cout << "GA  Starts at: " << std::format("{:%T}", start);
                GeneticAlgorithm geneticAlgorithm(configurations, evaluator);
                const auto chromosome = geneticAlgorithm.Solve();
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> duration = end - start;
                GA[i].first += chromosome.fitness;
                GA[i].second += duration.count();
                std::cout << " Takes seconds: " << duration.count() << " Fitness: " << chromosome.fitness << std::endl;
            }

            {
                auto start = std::chrono::high_resolution_clock::now();
                std::cout << "PGA Starts at: " << std::format("{:%T}", start);
                IslandGeneticAlgorithm islandGeneticAlgorithm(configurations.treads, configurations, evaluator);
                const auto chromosome = islandGeneticAlgorithm.Run();
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> duration = end - start;
                PGA[i].first += chromosome.fitness;
                PGA[i].second += duration.count();
                std::cout << " Takes seconds: " << duration.count() << " Fitness: " << chromosome.fitness << std::endl;
            }
        }
        GA[i].first /= configurations.testIterations;
        GA[i].second /= configurations.testIterations;
        PGA[i].first /= configurations.testIterations;
        PGA[i].second /= configurations.testIterations;

        std::cout << "Calculations for " << cityCount[i] << " cities made..."<< std::endl << std::endl;
    }

    std::cout << "|----------|------------|-------------|-------------|--------------|-----------|--------|\n";
    std::cout << "|   Size   | GA Fitness | GA Time (s) | PGA Fitness | PGA Time (s) | Fitness D | Time d |\n";
    std::cout << "|----------|------------|-------------|-------------|--------------|-----------|--------|\n";
    for (int i = 0; i < cityCount.size(); i++) {
        std::cout << "| " << std::setw(8) << cityCount[i] << " | "
                  << std::setw(10) << GA[i].first << " | "
                  << std::setw(11) << std::fixed << std::setprecision(4) << GA[i].second << " | "
                  << std::setw(11) << PGA[i].first << " | "
                  << std::setw(12) << std::fixed << std::setprecision(4) << PGA[i].second << " |"
                  << std::setw(10) << GA[i].first - PGA[i].first << " | "
                  << std::setw(7) << std::fixed << std::setprecision(2) << GA[i].second / PGA[i].second << "|\n";
    }
    std::cout << "|----------|------------|-------------|-------------|--------------|-----------|--------|\n";

    double avgTimeD = 0;
    int avgFitnessD = 0;
    int avgFitnessGA = 0;
    for (int i = 0; i < configurations.testIterations; i++) {
        avgTimeD += GA[i].second / PGA[i].second;
        avgFitnessD += GA[i].first - PGA[i].first;
        avgFitnessGA += GA[i].first;
    }
    std::cout << "Average time difference: " << avgTimeD / configurations.testIterations << std::endl
              << "Average fitness difference: " << avgFitnessD / configurations.testIterations << std::endl
              << "Average GA fitness: " << avgFitnessD / configurations.testIterations << std::endl;

    return 0;
}