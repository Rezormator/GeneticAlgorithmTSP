#include "GeneticAlgorithm.h"

#include "../Core/Operators/Operators.h"

GeneticAlgorithm::GeneticAlgorithm(Configurations configuration, Evaluator evaluator)
    : configuration(configuration), evaluator(evaluator), population(configuration.populationSize)
{
    auto& chromosomes = population.GetChromosomes();
    chromosomes.resize(configuration.populationSize);
    for (auto& chromosome : chromosomes) {
        Operators::GenerateRandomGenes(chromosome, configuration.cityCount);
        evaluator.Evaluate(chromosome);
    }
}

Chromosome GeneticAlgorithm::Solve() {
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
    } while (population.GetBest().fitness > configuration.goalFitness && iterationCount++ < configuration.iterations);

    return population.GetBest();
}
