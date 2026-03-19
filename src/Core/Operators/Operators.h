#pragma once

#include "../Evaluator/Evaluator.h"
#include "../Chromosome/Chromosome.h"
#include <functional>

namespace Operators {
    using Crossover = std::function<Chromosome(const Chromosome &, const Chromosome &, int)>;

    void GenerateRandomGenes(Chromosome &chromosome, int cityCount);

    void ApplyMutation(Chromosome &chromosome, double probability, const Evaluator &evaluator);
    void LocalImprovement(Chromosome &chromosome, double probability, const Evaluator &evaluator);

    std::vector<double> CalculateProbabilityDistribution(std::vector<Chromosome> &chromosomes);
    std::pair<int, int> SelectParentIndices(const std::vector<double> &probabilityDistribution);

    Crossover GetRandomCrossover();
}
