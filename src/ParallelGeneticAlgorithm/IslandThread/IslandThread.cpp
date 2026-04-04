#include "IslandThread.h"
#include "../../Core/Operators/Operators.h"

IslandThread::IslandThread(const int id, const Configurations& configuration, const Evaluator& evaluator, MigrationManager& migrationManager)
    : id(id), configuration(configuration), evaluator(evaluator), migrationManager(migrationManager), population(configuration.populationSize)
{
    auto& chromosomes = population.GetChromosomes();
    chromosomes.resize(configuration.populationSize);
    for (auto& chromosome : chromosomes) {
        Operators::GenerateRandomGenes(chromosome, configuration.cityCount);
        evaluator.Evaluate(chromosome);
    }
}

const Population &IslandThread::GetPopulation() const {
    return population;
}

void IslandThread::Start() {
    thread = std::thread([this]() { Run(); });
}

void IslandThread::Join() {
    if (thread.joinable()) {
        thread.join();
    }
}

void IslandThread::Run() {
    for (int epoch = 0; epoch < configuration.totalEpochs; epoch++) {
        EvolveEpoch();

        const auto& best = population.GetBest();
        if (best.fitness <= configuration.goalFitness) {
            migrationManager.ReportGoalReached(best);
        }

        migrationManager.SyncAndMigrate(id, population);
        if (migrationManager.IsStopped()) {
            return;
        }
    }
}

void IslandThread::EvolveEpoch() {
    auto& chromosomes = population.GetChromosomes();
    const int size = static_cast<int>(chromosomes[0].genes.size());

    int iterationCount = 0;
    do {
        auto probabilityDistribution = Operators::CalculateProbabilityDistribution(chromosomes);
        auto parents = Operators::SelectParentIndices(probabilityDistribution);

        auto crossover = Operators::GetRandomCrossover();
        auto child = crossover(chromosomes[parents.first], chromosomes[parents.second], size);
        evaluator.Evaluate(child);

        Operators::ApplyMutation(child, configuration.mutationProbability, evaluator);
        Operators::LocalImprovement(child, configuration.improveProbability, evaluator);

        population.IntegrateChild(std::move(child));
    } while (population.GetBest().fitness > configuration.goalFitness && iterationCount++ < configuration.epochIterations);
}