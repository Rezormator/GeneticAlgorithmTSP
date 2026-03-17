#include "AdjacencyMatrix.h"

AdjacencyMatrix::AdjacencyMatrix(const int size, const int min, const int max, const double symmetry) : adjacencyMatrix(nullptr), size(size) {
    GenerateAdjacencyMatrix(min, max, symmetry);
}

AdjacencyMatrix::~AdjacencyMatrix() {
    delete adjacencyMatrix;
}

matrix *AdjacencyMatrix::GetAdjacencyMatrix() const {
    return adjacencyMatrix;
}

int AdjacencyMatrix::GetSize() const {
    return size;
}

void AdjacencyMatrix::GenerateAdjacencyMatrix(const int min, const int max, const double symmetry) {
    adjacencyMatrix = new matrix(size, std::vector(size, 0));
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if ((*adjacencyMatrix)[i][j] != 0) {
                continue;
            }
            const auto length = Utils::GenerateInt(min, max);
            (*adjacencyMatrix)[i][j] = length;
            if ((*adjacencyMatrix)[j][i] != 0) {
                continue;
            }
            if (Utils::GenerateDouble(0, 1) <= symmetry) {
                (*adjacencyMatrix)[j][i] = length;
            }
            else {
                (*adjacencyMatrix)[j][i] = Utils::GenerateInt(min, max);
            }
        }
    }
}

