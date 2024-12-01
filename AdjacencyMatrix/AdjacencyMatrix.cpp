#include "AdjacencyMatrix.h"
#include "../RandomGenerator/RandomGenerator.h"
#include <iostream>

matrix *AdjacencyMatrix::adjacencyMatrix;

matrix *AdjacencyMatrix::getAdjacencyMatrixMatrix() {
    return adjacencyMatrix;
}

void AdjacencyMatrix::generateMatrix(const int size, const int min, const int max, const double symmetry) {
    adjacencyMatrix = new matrix(size, std::vector(size, 0));
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if ((*adjacencyMatrix)[i][j] != 0) {
                continue;
            }
            const auto lenth = RandomGenerator::generateInt(min, max);
            (*adjacencyMatrix)[i][j] = lenth;
            if ((*adjacencyMatrix)[j][i] != 0) {
                continue;
            }
            if (RandomGenerator::generateDouble(0, 1) <= symmetry) {
                (*adjacencyMatrix)[j][i] = lenth;
            }
            else {
                (*adjacencyMatrix)[j][i] = RandomGenerator::generateInt(min, max);
            }
        }
    }
}

void AdjacencyMatrix::deleteMatrix() {
    delete adjacencyMatrix;
}

void AdjacencyMatrix::printMatrix() {
    const auto size = (*adjacencyMatrix)[0].size();
    std::cout << std::endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if ((*adjacencyMatrix)[i][j] < 10) {
                std::cout << '[' << (*adjacencyMatrix)[i][j] << "  ]";
            }
            else if ((*adjacencyMatrix)[i][j] < 100) {
                std::cout << '[' << (*adjacencyMatrix)[i][j] << " ]";
            }
            else {
                std::cout << '[' << (*adjacencyMatrix)[i][j] << ']';
            }
        }
        std::cout << std::endl;
    }
}
