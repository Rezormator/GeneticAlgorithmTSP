#include <iostream>
#include "AdjacencyMatrix/AdjacencyMatrix.h"
#include "GeneticAlgorithm/GeneticAlgorithm.h"

int main() {
    int size = 0;
    int min = 0;
    int max = 0;
    std::cout << "Enter cities count, min and max distance between cities: ";
    std::cin >> size >> min >> max;

    int populationSize = 0;
    int iterationsCount = 0;
    int goal = 0;
    std::cout << "Enter population size, iterations count and distance goal: ";
    std::cin >> populationSize >> iterationsCount >> goal;

    AdjacencyMatrix::generateMatrix(size, min, max, 0.5);
    if (size <= 10) {
        AdjacencyMatrix::printMatrix();
    }
    GeneticAlgorithm::solveTSP(populationSize, 0.5, iterationsCount, goal);
    AdjacencyMatrix::deleteMatrix();

    int stop;
    std::cin >> stop;
    return 0;
}
