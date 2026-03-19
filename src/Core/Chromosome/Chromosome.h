#pragma once

#include <vector>

struct Chromosome {
    std::vector<int> genes;
    int fitness = 0;

    Chromosome() = default;
    explicit Chromosome(const std::vector<int> &genes);
};
