#include "GeneticAlgorithm.h"
#include "../Population/Population.h"

Route GeneticAlgorithm::solveTSP(const int populationSize, const int iterationsCount, const double mutationProbability) {
    const auto population = new Population(populationSize);
    population->print();
    for (int i = 0; i < iterationsCount; i++) {
        const auto parents = population->selectParents();
        const auto child = population->crossover(parents);
        // child->print();
        child->mutation(mutationProbability);
        child->localImprovement();
        // std::cout << std::endl;
        population->addChromosome(child);
        population->deleteWorst();
        // population->print();
    }
    const auto route = *population->getBestRoute();
    delete population;
    route.print();
    return route;
}
