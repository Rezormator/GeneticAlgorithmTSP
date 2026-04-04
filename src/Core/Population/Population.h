#pragma once

#include <vector>
#include "../Chromosome/Chromosome.h"
#include "../../Utils/Utils.h"

class Population {
private:
    std::vector<Chromosome> chromosomes;
    int bestChromosome;
    int worstChromosome;
public:
    explicit Population(int size);

    void SetChromosomes(std::vector<Chromosome>&& newChromosomes);
    NODISCARD std::vector<Chromosome>& GetChromosomes();
    NODISCARD const std::vector<Chromosome>& GetChromosomes() const;
    NODISCARD const Chromosome &GetBest() const;

    void IntegrateChild(Chromosome&& child);
};
