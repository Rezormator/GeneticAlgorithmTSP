#pragma once
#include "../Core/Evaluator/Evaluator.h"
#include "../Core/Population/Population.h"
#include "../Configurations.h"

class GeneticAlgorithm {
private:
    Configurations configuration;
    const Evaluator &evaluator;
    Population population;
public:
    GeneticAlgorithm(Configurations configuration, Evaluator evaluator);
    Chromosome Solve();
};
