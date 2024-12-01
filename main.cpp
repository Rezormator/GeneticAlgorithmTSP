#include <iostream>
#include "AdjacencyMatrix/AdjacencyMatrix.h"
#include "GeneticAlgorithm/GeneticAlgorithm.h"

int main() {
    AdjacencyMatrix::generateMatrix(300, 5, 150, 0.5);
    // AdjacencyMatrix::printMatrix();
    GeneticAlgorithm::solveTSP(10, 1000, 0.5);
    AdjacencyMatrix::deleteMatrix();
    int stop;
    std::cin >> stop;
    return 0;
}
