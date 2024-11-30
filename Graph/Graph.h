#pragma once

#include <vector>
#include "../Utils.h"

class Graph {
private:
    int size;
    int minLenth;
    int maxLenth;
public:
    Graph(int size, int minLenth, int maxLenth);
    NODISCARD matrixi *generateGraphMatrix(double connection, double symmetry) const;
    void printGraphMatrix(const matrixi *matrix) const;
};
