#include "IslandGeneticAlgorithm.h"
#include <limits>

IslandGeneticAlgorithm::IslandGeneticAlgorithm(const int islandCount, const Configurations &configurations, const Evaluator &evaluator)
    : evaluator(evaluator), migrationManager(islandCount, configurations.populationSize) {
    islands.reserve(islandCount);
    for (int i = 0; i < islandCount; i++) {
        islands.push_back(std::make_unique<IslandThread>(i, configurations, evaluator, migrationManager));
    }
}

Chromosome IslandGeneticAlgorithm::Run() {
    for (const auto &island: islands) {
        island->Start();
    }
    for (const auto &island: islands) {
        island->Join();
    }

    Chromosome best;
    if (migrationManager.TryGetBest(best)) {
        return best;
    }

    best.fitness = std::numeric_limits<int>::max();
    for (const auto &islandThread: islands) {
        for (const auto &chromosome: islandThread->GetPopulation().GetChromosomes()) {
            if (chromosome.fitness < best.fitness) {
                best = chromosome;
            }
        }
    }
    return best;
}
