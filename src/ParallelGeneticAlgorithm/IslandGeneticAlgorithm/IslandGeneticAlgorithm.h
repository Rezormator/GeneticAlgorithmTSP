#pragma once

#include <vector>
#include <memory>
#include "../../Core/Evaluator/Evaluator.h"
#include "../IslandThread/IslandThread.h"
#include "../MigrationManager/MigrationManager.h"

class IslandGeneticAlgorithm {
private:
    const Evaluator &evaluator;
    MigrationManager migrationManager;

    std::vector<std::unique_ptr<IslandThread> > islands;
public:
    explicit IslandGeneticAlgorithm(const Configurations &configurations, const Evaluator &evaluator);

    Chromosome Run();
};
