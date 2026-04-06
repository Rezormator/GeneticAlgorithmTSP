#include "Tests.h"
#include "../Core/AdjacencyMatrixGenerator/AdjacencyMatrixGenerator.h"
#include "../Core/Evaluator/Evaluator.h"
#include "../ParallelGeneticAlgorithm/IslandGeneticAlgorithm/IslandGeneticAlgorithm.h"
#include "../GeneticAlgorithm/GeneticAlgorithm.h"
#include <chrono>
#include <iostream>

namespace Tests {
    void GeneticAlgorithmIterationsTest() {
        Configurations configurations;

        std::vector<std::pair<int, double> > GA;
        const std::vector<int> iterations = {10000, 50000, 100000};

        configurations.cityCount = 1000;
        for (int i = 0; i < iterations.size(); i++) {
            configurations.iterations = iterations[i];
            std::cout << "Generating adjacency matrix for " << configurations.cityCount << " cities";
            std::chrono::time_point<std::chrono::system_clock> start = std::chrono::high_resolution_clock::now();

            const auto adjacencyMatrix = AdjacencyMatrixGenerator::GenerateAdjacencyMatrix(configurations.cityCount);
            const Evaluator evaluator(adjacencyMatrix);

            std::chrono::time_point<std::chrono::system_clock> end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;
            std::cout << " Takes seconds: " << duration.count() << std::endl;

            std::cout << "Calculations with " << iterations[i] << " iterations:" << std::endl;
            for (int j = 0; j < configurations.testIterations; j++) {
                std::cout << "Iteration number: " << j + 1 << std::endl;

                start = std::chrono::high_resolution_clock::now();
                std::cout << "GA Starts at: " << std::format("{:%T}", start);

                GeneticAlgorithm geneticAlgorithm(configurations, evaluator);
                auto chromosome = geneticAlgorithm.Solve();

                end = std::chrono::high_resolution_clock::now();
                duration = end - start;

                GA[i].first += chromosome.fitness;
                GA[i].second += duration.count();

                std::cout << " Takes seconds: " << std::setw(8) << std::fixed << std::setprecision(4) << duration.count()
                          << " Fitness: " << chromosome.fitness << std::endl;
            }

            GA[i].first /= configurations.testIterations;
            GA[i].second /= configurations.testIterations;

            std::cout << "Calculations with " << iterations[i] << " made..." << std::endl;
        }

        std::cout << "|------------|------------|-------------|" << std::endl;
        std::cout << "| Iterations |  Time (s)  |   Fitness   |" << std::endl;
        std::cout << "|------------|------------|-------------|" << std::endl;
        for (int i = 0; i < iterations.size(); i++) {
            std::cout << "| " << std::setw(10) << iterations[i] << " | "
                    << std::setw(10) << std::setprecision(4) << GA[i].second << " | "
                    << std::setw(11) << GA[i].first << " |\n";
        }
        std::cout << "|------------|------------|-------------|" << std::endl;
        std::cout << std::endl;
    }

    void ParallelGeneticAlgorithmIterationsTest() {
        Configurations configurations;

        std::vector<std::pair<int, double> > PGA2;
        std::vector<std::pair<int, double> > PGA5;
        std::vector<std::pair<int, double> > PGA10;
        std::vector<std::vector<std::pair<int, double>>*> All_GA = {&PGA2, &PGA5, &PGA10};
        const std::vector<int> threadsCount = {2, 5, 10};
        const std::vector<int> iterations = {10000, 50000, 100000};

        configurations.cityCount = 1000;
        for (int i = 0; i < iterations.size(); i++) {
            configurations.iterations = iterations[i];
            std::cout << "Generating adjacency matrix for " << configurations.cityCount << " cities";
            std::chrono::time_point<std::chrono::system_clock> start = std::chrono::high_resolution_clock::now();

            const auto adjacencyMatrix = AdjacencyMatrixGenerator::GenerateAdjacencyMatrix(configurations.cityCount);
            const Evaluator evaluator(adjacencyMatrix);

            std::chrono::time_point<std::chrono::system_clock> end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;
            std::cout << " Takes seconds: " << duration.count() << std::endl;

            std::cout << "Calculations with " << iterations[i] << " iterations:" << std::endl;
            for (int j = 0; j < configurations.testIterations; j++) {
                std::cout << "Iteration number: " << j + 1 << std::endl;
                for (int k = 0; k < All_GA.size(); k++) {
                    configurations.treads = threadsCount[k];
                    start = std::chrono::high_resolution_clock::now();
                    std::cout << "PGA" << std::setw(2) << configurations.treads << "Starts at: " << std::format("{:%T}", start);

                    IslandGeneticAlgorithm islandGeneticAlgorithm(configurations, evaluator);
                    auto chromosome = islandGeneticAlgorithm.Run();

                    end = std::chrono::high_resolution_clock::now();
                    duration = end - start;

                    (*All_GA[k])[i].first += chromosome.fitness;
                    (*All_GA[k])[i].second += duration.count();

                    std::cout << " Takes seconds: " << std::setw(8) << std::fixed << std::setprecision(4) << duration.count()
                          << " Fitness: " << chromosome.fitness << std::endl;
                }
            }

            for (auto ga : All_GA) {
                (*ga)[i].first /= configurations.testIterations;
                (*ga)[i].second /= configurations.testIterations;
            }

            std::cout << "Calculations with " << iterations[i] << " made..." << std::endl;
        }

        std::cout << "|------------|---------------|--------------|---------------|--------------|----------------|---------------|" << std::endl;
        std::cout << "| Iterations | PGA2 Time (s) | PGA2 Fitness | PGA2 Time (s) | PGA2 Fitness | PGA10 Time (s) | PGA10 Fitness |" << std::endl;
        std::cout << "|------------|---------------|--------------|---------------|--------------|----------------|---------------|" << std::endl;
        for (int i = 0; i < iterations.size(); i++) {
            std::cout << "| " << std::setw(10) << iterations[i] << " | "
                    << std::setw(13) << std::setprecision(4) << PGA2[i].second << " | "
                    << std::setw(12) << PGA2[i].first << " | "
                    << std::setw(13) << std::setprecision(4) << PGA5[i].second << " | "
                    << std::setw(12) << PGA5[i].first << " | "
                    << std::setw(14) << std::setprecision(4) << PGA10[i].second << " | "
                    << std::setw(13) << PGA10[i].first << " |\n";
        }
        std::cout << "|------------|---------------|--------------|---------------|--------------|----------------|---------------|" << std::endl;
        std::cout << std::endl;
    }

    void CompareTest() {
        Configurations configurations;

        std::vector<std::pair<int, double> > GA;
        std::vector<std::pair<int, double> > PGA2;
        std::vector<std::pair<int, double> > PGA5;
        std::vector<std::pair<int, double> > PGA10;
        std::vector<std::vector<std::pair<int, double>>*> All_GA = {&GA, &PGA2, &PGA5, &PGA10};

        const std::vector<int> cityCount = {10, 50, 100, 500, 1000, 5000};
        const std::vector<int> threadsCount = {2, 5, 10};

        std::chrono::time_point<std::chrono::system_clock> start;
        std::chrono::time_point<std::chrono::system_clock> end ;
        std::chrono::duration<double> duration;

        for (int i = 0; i < cityCount.size(); i++) {
            std::cout << "Generating adjacency matrix for " << cityCount[i] << " cities";
            start = std::chrono::high_resolution_clock::now();

            configurations.cityCount = cityCount[i];
            const auto adjacencyMatrix = AdjacencyMatrixGenerator::GenerateAdjacencyMatrix(configurations.cityCount);
            const Evaluator evaluator(adjacencyMatrix);

            end = std::chrono::high_resolution_clock::now();
            duration = end - start;
            std::cout << " Takes seconds: " << duration.count() << std::endl;

            for (auto ga: All_GA) {
                ga->emplace_back(0, 0);
            }

            std::cout << "Calculations for " << cityCount[i] << " cities:" << std::endl;
            for (int j = 0; j < configurations.testIterations; j++) {
                std::cout << "Iteration number: " << j + 1 << std::endl;
                configurations.goalFitness = 0;

                start = std::chrono::high_resolution_clock::now();
                std::cout << "GA    Starts at: " << std::format("{:%T}", start);

                GeneticAlgorithm geneticAlgorithm(configurations, evaluator);
                auto chromosome = geneticAlgorithm.Solve();

                end = std::chrono::high_resolution_clock::now();
                duration = end - start;

                GA[i].first += chromosome.fitness;
                GA[i].second += duration.count();
                configurations.goalFitness = chromosome.fitness;

                std::cout << " Takes seconds: " << std::setw(8) << std::fixed << std::setprecision(4) << duration.count()
                          << " Fitness: " << chromosome.fitness << std::endl;

                for (int k = 1; k < All_GA.size(); k++) {
                    configurations.treads = threadsCount[k - 1];
                    configurations.parallelPopulationSize = configurations.populationSize / configurations.treads;
                    configurations.totalEpochs = configurations.iterations / configurations.epochIterations / configurations.treads;

                    start = std::chrono::high_resolution_clock::now();
                    std::cout << "PGA" << std::setw(2) << configurations.treads << " Starts at: " << std::format("{:%T}", start);

                    IslandGeneticAlgorithm islandGeneticAlgorithm(configurations, evaluator);
                    chromosome = islandGeneticAlgorithm.Run();

                    end = std::chrono::high_resolution_clock::now();
                    duration = end - start;

                    (*All_GA[k])[i].first += chromosome.fitness;
                    (*All_GA[k])[i].second += duration.count();

                    std::cout << " Takes seconds: " << std::setw(8) << std::fixed << std::setprecision(4) << duration.count()
                          << " Fitness: " << chromosome.fitness << std::endl;
                }
            }

            for (auto ga : All_GA) {
                (*ga)[i].first /= configurations.testIterations;
                (*ga)[i].second /= configurations.testIterations;
            }

            std::cout << "Calculations for " << cityCount[i] << " cities made..." << std::endl << std::endl;
        }

        std::cout << "|----------|-------------|---------------|---------------|----------------|" << std::endl;
        std::cout << "|   Size   | GA Time (s) | PGA2 Time (s) | PGA5 Time (s) | PGA10 Time (s) |" << std::endl;
        std::cout << "|----------|-------------|---------------|---------------|----------------|" << std::endl;
        for (int i = 0; i < cityCount.size(); i++) {
            std::cout << "| " << std::setw(8) << cityCount[i] << " | "
                    << std::setw(11) << std::setprecision(4) << GA[i].second << " | "
                    << std::setw(13) << std::setprecision(4) << PGA2[i].second << " | "
                    << std::setw(13) << std::setprecision(4) << PGA5[i].second << " | "
                    << std::setw(14) << std::setprecision(4) << PGA10[i].second << " |\n";
        }
        std::cout << "|----------|-------------|---------------|---------------|----------------|" << std::endl;
        std::cout << std::endl;

        std::cout << "|----------|-----------|-------------|-------------|--------------|" << std::endl;
        std::cout << "|   Size   | GA Time d | PGA2 Time d | PGA5 Time d | PGA10 Time d |" << std::endl;
        std::cout << "|----------|-----------|-------------|-------------|--------------|" << std::endl;
        for (int i = 0; i < cityCount.size(); i++) {
            std::cout << "| " << std::setw(8) << cityCount[i] << " | "
                    << std::setw(9) << std::setprecision(2) << GA[i].second / GA[i].second << " | "
                    << std::setw(11) << std::setprecision(2) << GA[i].second / PGA2[i].second << " | "
                    << std::setw(11) << std::setprecision(2) << GA[i].second / PGA5[i].second << " | "
                    << std::setw(12) << std::setprecision(2) << GA[i].second / PGA10[i].second << " |\n";
        }
        std::cout << "|----------|-----------|-------------|-------------|--------------|" << std::endl;
    }
}
