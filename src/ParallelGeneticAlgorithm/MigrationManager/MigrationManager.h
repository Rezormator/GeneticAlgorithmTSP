#pragma once

#include <vector>
#include <barrier>
#include <atomic>
#include <functional>
#include "../../Core/Population/Population.h"

class MigrationManager {
private:
    int islandCount;
    int populationSize;

    std::vector<Population *> islandReferences;
    std::vector<Chromosome> superPopulation;

    std::atomic<bool> stopFlag;
    std::atomic<Chromosome *> bestFound;

    std::barrier<std::function<void()> > barrier;

    void OnEpochEnd() noexcept;
    void BuildSuperPopulation();
    void DistributeSuperPopulation();
public:
    explicit MigrationManager(int islandCount, int populationSize);
    ~MigrationManager();

    void SyncAndMigrate(int islandId, Population &population);
    NODISCARD bool IsStopped() const;
    void ReportGoalReached(const Chromosome &best);
    bool TryGetBest(Chromosome &out) const;
};
