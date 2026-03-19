#pragma once

#include "../../Utils/Utils.h"

namespace AdjacencyMatrixGenerator {
    static constexpr int DEFAULT_SIZE = 10;
    static constexpr int DEFAULT_MIN = 100;
    static constexpr int DEFAULT_MAX = 1000;
    static constexpr double DEFAULT_SYMMETRY = 0.5;
    matrix GenerateAdjacencyMatrix(int size = DEFAULT_SIZE, int min = DEFAULT_MIN, int max = DEFAULT_MAX,
                                   double symmetry = DEFAULT_SYMMETRY);
}
