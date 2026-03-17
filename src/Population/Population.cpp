#include "Population.h"
#include <algorithm>
#include "../GeneticAlgorithm/GeneticAlgorithm.h"

Population::Population(const int size) : size(size) {
    GeneratePopulation();
}

Population::~Population() {
    for (const auto chromosome : chromosomes) {
        delete chromosome;
    }
}

void Population::SetPopulation(const std::vector<Chromosome *>& chromosomes) {
    this->chromosomes = chromosomes;
}

std::vector<Chromosome *> Population::GetPopulation() const {
    return chromosomes;
}

void Population::GeneratePopulation() {
    for (int i = 0; i < size; i++) {
        chromosomes.push_back(new Chromosome());
    }
}

std::vector<double> Population::CalculateProbabilityDistribution() const {
    std::vector<double> probabilityDistribution;
    double distanceTotal = 0;
    for (const auto gene : chromosomes) {
        distanceTotal += 1.0 / gene->GetFitness();
    }
    for (int i = 0; i < size; i++) {
        double geneProbability = 1.0 / chromosomes[i]->GetFitness() / distanceTotal;
        if (probabilityDistribution.empty()) {
            probabilityDistribution.push_back(geneProbability);
        }
        else {
            probabilityDistribution.push_back(probabilityDistribution[i - 1] + geneProbability);
        }
    }
    return probabilityDistribution;
}

void Population::Sort() {
    std::ranges::sort(chromosomes, [](const Chromosome *a, const Chromosome *b) { return a->GetFitness() < b->GetFitness(); });
}

Chromosome *Population::GetBestChromosome() {
    Sort();
    return chromosomes[0];
}

std::pair<int, int> Population::SelectParents() const {
    std::pair parents(-1, -1);
    const auto probabilityDistribution = CalculateProbabilityDistribution();
    parents.first = GeneticAlgorithm::GetGeneIndex(probabilityDistribution);
    do {
        parents.second = GeneticAlgorithm::GetGeneIndex(probabilityDistribution);
    } while (parents.first == parents.second);
    return parents;
}

Chromosome *Population::Crossover(const std::pair<int, int> &parents) const {
    const auto firstParent = chromosomes[parents.first];
    const auto secondParent = chromosomes[parents.second];
    const auto genesCount = static_cast<int>(firstParent->GetGenes().size());
    Chromosome *chromosome;
    switch (Utils::GenerateInt(1, 3)) {
        case 1:
            chromosome = GeneticAlgorithm::OrderCrossover(firstParent, secondParent, genesCount);
        break;
        case 2:
            chromosome = GeneticAlgorithm::HalfCrossover(firstParent, secondParent, genesCount);
        break;
        default:
            chromosome = GeneticAlgorithm::CycleCrossover(firstParent, secondParent, genesCount);
        break;
    }
    return chromosome;
}

void Population::AddChromosome(Chromosome *chromosome) {
    chromosomes.push_back(chromosome);
}

void Population::DeleteWorstChromosome() {
    Sort();
    chromosomes.pop_back();
}