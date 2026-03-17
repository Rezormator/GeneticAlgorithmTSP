#pragma once
#include "../Utils/Utils.h"

class AdjacencyMatrix {
    static constexpr int DEFAULT_SIZE = 10;
    static constexpr int DEFAULT_MIN = 100;
    static constexpr int DEFAULT_MAX = 1000;
    static constexpr double DEFAULT_SYMMETRY = 0.5;
private:
    matrix *adjacencyMatrix;
    int size;
    void GenerateAdjacencyMatrix(int min, int max, double symmetry);
public:
    explicit AdjacencyMatrix(int size = DEFAULT_SIZE, int min = DEFAULT_MIN, int max = DEFAULT_MAX, double symmetry = DEFAULT_SYMMETRY);
    ~AdjacencyMatrix();

    NODISCARD matrix *GetAdjacencyMatrix() const;
    NODISCARD int GetSize() const;
};
