#include "Graph.h"
#include "../RandomGenerator/RandomGenerator.h"
#include <iostream>

Graph::Graph(const int size, const int minLenth, const int maxLenth)
: size(size), minLenth(minLenth), maxLenth(maxLenth) {
    const auto matrix = generateGraphMatrix(0.5, 0.5);
    printGraphMatrix(matrix);
}

matrixi *Graph::generateGraphMatrix(const double connection, const double symmetry) const {
    const auto matrix = new matrixi(size, std::vector(size, 0));
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if ((*matrix)[i][j] != 0 || RandomGenerator::generateDouble(0, 1) > connection) {
                continue;
            }
            const auto lenth = RandomGenerator::generateInt(minLenth, maxLenth);
            (*matrix)[i][j] = lenth;
            if ((*matrix)[j][i] != 0) {
                continue;
            }
            if (RandomGenerator::generateDouble(0, 1) <= symmetry) {
                (*matrix)[j][i] = lenth;
            }
            else {
                (*matrix)[j][i] = RandomGenerator::generateInt(minLenth, maxLenth);
            }
        }
    }
    return matrix;
}

void Graph::printGraphMatrix(const matrixi *matrix) const {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << (*matrix)[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

