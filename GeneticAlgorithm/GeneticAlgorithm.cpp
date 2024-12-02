#include "GeneticAlgorithm.h"
#include <iostream>
#include "../Population/Population.h"

Route GeneticAlgorithm::solveTSP(const int populationSize, const double mutationProbability, int iterationsCount, const int goal) {
    const auto population = new Population(populationSize);
    std::cout << std::endl << "First population: " << std::endl;
    population->print();
    int iteration = 0;
    do {
        const auto parents = population->selectParents();
        const auto child = population->crossover(parents);
        // child->print();
        child->mutation(mutationProbability);
        child->localImprovement();
        // std::cout << std::endl;
        population->addChromosome(child);
        population->deleteWorst();
        // population->print();
        iterationsCount--;
        iteration++;
    } while (goal < population->getBestRoute()->getDistance() && iterationsCount != 0);
    std::cout << "Last population: " << std::endl;
    population->print();
    const auto route = *population->getBestRoute();
    delete population;
    std::cout << "Result: " << std::endl;
    route.print(true);
    std::cout << iteration;
    return route;
}
