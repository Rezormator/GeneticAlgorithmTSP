#pragma once

#include "../Route/Route.h"

class GeneticAlgorithm {
public:
    static Route solveTSP(int populationSize, double mutationProbability, int iterationsCount, int goal = 0);
};
