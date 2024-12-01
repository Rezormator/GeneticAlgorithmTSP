#pragma once

#include "../Route/Route.h"

class Population {
private:
    int size;
    std::vector<Route *> chromosomes;
    void sort();
    void generatePopulation();
    NODISCARD std::vector<double> calculateProbabilityDistribution() const;
    NODISCARD static int getGeneIndex(const std::vector<double> &probabilityDistribution);
public:
    explicit Population(int size);
    ~Population();
    Route *getBestRoute();
    NODISCARD std::pair<int, int> selectParents() const;
    NODISCARD Route *crossover(const std::pair<int, int> &parents) const;
    void addChromosome(Route *chromosome);
    void deleteWorst();
    void print() const;
};
