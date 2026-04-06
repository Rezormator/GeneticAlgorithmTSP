#include "MigrationManager.h"

MigrationManager::MigrationManager(const int islandCount, const int populationSize)
    : islandCount(islandCount),
      populationSize(populationSize),
      islandReferences(islandCount, nullptr),
      stopFlag(false),
      bestFound(nullptr),
      barrier(islandCount, std::function<void()>([this]() noexcept { OnEpochEnd(); })) {
}

MigrationManager::~MigrationManager() {
    delete bestFound.load();
}

void MigrationManager::SyncAndMigrate(const int islandId, Population &population) {
    islandReferences[islandId] = &population;

    if (stopFlag.load(std::memory_order_relaxed)) {
        barrier.arrive_and_drop();
        return;
    }

    barrier.arrive_and_wait();
}

bool MigrationManager::IsStopped() const {
    return stopFlag.load(std::memory_order_relaxed);
}

void MigrationManager::ReportGoalReached(const Chromosome &best) {
    auto *candidate = new Chromosome(best);
    Chromosome *expected = nullptr;

    if (!bestFound.compare_exchange_strong(expected, candidate)) {
        delete candidate;
    }

    stopFlag.store(true, std::memory_order_relaxed);
}

bool MigrationManager::TryGetBest(Chromosome &out) const {
    if (const auto *chromosome = bestFound.load()) {
        out = *chromosome;
        return true;
    }
    return false;
}

void MigrationManager::OnEpochEnd() noexcept {
    if (stopFlag.load(std::memory_order_relaxed)) {
        return;
    }
    BuildSuperPopulation();
    DistributeSuperPopulation();
}

void MigrationManager::BuildSuperPopulation() {
    superPopulation.clear();

    for (int i = 0; i < islandCount && i < populationSize; i++) {
        superPopulation.push_back(islandReferences[i]->GetBest());
    }

    for (int i = islandCount; i < populationSize; i++) {
        superPopulation.push_back(islandReferences[i % islandCount]->GetChromosomes()[Utils::GenerateInt(0, populationSize - 1)]);
    }
}

void MigrationManager::DistributeSuperPopulation() {
    for (auto *population: islandReferences) {
        if (population) {
            population->SetChromosomes(std::vector<Chromosome>(superPopulation));
        }
    }
}
