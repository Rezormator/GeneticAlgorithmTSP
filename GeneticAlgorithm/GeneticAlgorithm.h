#pragma once

#include "../Route/Route.h"

class GeneticAlgorithm {
public:
    static Route solveTSP(int populationSize, int iterationsCount, double mutationProbability);
};
