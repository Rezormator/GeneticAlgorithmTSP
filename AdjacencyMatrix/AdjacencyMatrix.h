#pragma once

#include <vector>
#include "../Utils.h"

class AdjacencyMatrix {
private:
    static matrix *adjacencyMatrix;
public:
    static matrix *getAdjacencyMatrixMatrix();
    static void generateMatrix(int size, int min, int max, double symmetry);
    static void deleteMatrix();
    static void printMatrix();
};
