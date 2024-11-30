#include "Graph.h"
#include "../RandomGenerator/RandomGenerator.h"
#include <iostream>

Graph::Graph(const int size, const int minLenth, const int maxLenth)
: size(size), minLenth(minLenth), maxLenth(maxLenth) {
    matrix = generateGraphMatrix(1, 0.5);
    printGraphMatrix(matrix);
}

std::vector<std::vector<int> > *Graph::getMatrix() const {
    return matrix;
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
            if ((*matrix)[i][j] < 10) {
                std::cout << '[' << (*matrix)[i][j] << "  ]";
            }
            else if ((*matrix)[i][j] < 100) {
                std::cout << '[' << (*matrix)[i][j] << " ]";
            }
            else {
                std::cout << '[' << (*matrix)[i][j] << ']';
            }
        }
        std::cout << std::endl;
    }
}

