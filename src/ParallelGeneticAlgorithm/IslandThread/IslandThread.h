#pragma once

#include <thread>
#include "../Configurations.h"
#include "../../Core/Evaluator/Evaluator.h"
#include "../../Core/Population/Population.h"
#include "../MigrationManager/MigrationManager.h"

class IslandThread {
private:
    int id;
    Configurations configuration;

    const Evaluator &evaluator;
    MigrationManager &migrationManager;

    Population population;
    std::thread thread;

    void Run();
    void EvolveEpoch();
public:
    IslandThread(int id, const Configurations& configuration, const Evaluator& evaluator, MigrationManager& migrationManager);

    NODISCARD const Population &GetPopulation() const;

    void Start();
    void Join();
};
