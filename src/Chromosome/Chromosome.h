#pragma once

#include "../AdjacencyMatrix/AdjacencyMatrix.h"
#include "../Utils/Utils.h"

class Chromosome {
private:
    std::vector<int> genes;
    int fitness;
    void GenerateGenes();
    void UpdateFitness();
    void OneGeneMutation();
    void ReverseMutation();
    void SwapOneGeneLocalImprovement();
    void SwapTwoGenesLocalImprovement();
public:
    explicit Chromosome();
    explicit Chromosome(const std::vector<int> &genes);

    void SetGenes(const std::vector<int> &genes);
    NODISCARD std::vector<int> GetGenes() const;
    NODISCARD int GetFitness() const;

    void Mutation(double probability);
    void LocalImprovement(double probability);
};
