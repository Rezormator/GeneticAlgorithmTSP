#pragma once
#include "../Utils/Utils.h"
#include "../AdjacencyMatrix/AdjacencyMatrix.h"
#include "../Chromosome/Chromosome.h"

namespace GeneticAlgorithm {
    void SetAdjacencyMatrix(AdjacencyMatrix *adjacencyMatrix);
    NODISCARD matrix *GetMatrix();
    NODISCARD AdjacencyMatrix *GetAdjacencyMatrix();

    int GetGeneIndex(const std::vector<double> &probabilityDistribution);
    Chromosome *OrderCrossover(const Chromosome *firstParent, const Chromosome *secondParent, int genesCount);
    Chromosome *HalfCrossover(const Chromosome *firstParent, const Chromosome *secondParent, int genesCount);
    Chromosome *CycleCrossover(const Chromosome *firstParent, const Chromosome *secondParent, int genesCount);

    Chromosome SolveTSP(int populationSize, double mutationProbability, double improvementProbability, int iterationsCount, int goal = 0);
}
