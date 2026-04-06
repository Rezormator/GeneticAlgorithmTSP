#include "IslandGeneticAlgorithm.h"

IslandGeneticAlgorithm::IslandGeneticAlgorithm(const Configurations &configurations, const Evaluator &evaluator)
    : evaluator(evaluator), migrationManager(configurations.treads, configurations.parallelPopulationSize) {
    islands.reserve(configurations.treads);
    for (int i = 0; i < configurations.treads; i++) {
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

    best.fitness = islands[0]->GetPopulation().GetBest().fitness;
    for (const auto &islandThread: islands) {
        const auto &chromosome = islandThread->GetPopulation().GetBest();
        if (chromosome.fitness < best.fitness) {
            best = chromosome;
        }
    }
    return best;
}
