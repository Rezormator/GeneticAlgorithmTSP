#include "Chromosome.h"
#include <numeric>
#include <algorithm>

#include "../GeneticAlgorithm/GeneticAlgorithm.h"

Chromosome::Chromosome() : fitness(0) {
    GenerateGenes();
    UpdateFitness();
}

Chromosome::Chromosome(const std::vector<int>& genes) : genes(genes), fitness(0) {
    UpdateFitness();
}

void Chromosome::SetGenes(const std::vector<int> &genes) {
    this->genes = genes;
    UpdateFitness();
}

std::vector<int> Chromosome::GetGenes() const {
    return genes;
}

int Chromosome::GetFitness() const {
    return fitness;
}

void Chromosome::GenerateGenes() {
    std::vector<int> array(GeneticAlgorithm::GetAdjacencyMatrix()->GetSize() - 1);
    std::iota(array.begin(), array.end(), 1);

    array = Utils::Shuffle(array);
    array.push_back(0);
    std::ranges::reverse(array);
    array.push_back(0);
    genes = array;
}

void Chromosome::UpdateFitness() {
    fitness = 0;
    const auto aMatrix = *GeneticAlgorithm::GetMatrix();
    for (int i = 0; i < GeneticAlgorithm::GetAdjacencyMatrix()->GetSize(); i++) {
        fitness += aMatrix[genes[i]][genes[i + 1]];
    }
}

void Chromosome::Mutation(const double probability) {
    if (Utils::GenerateDouble(0, 1) > probability) {
        return;
    }

    Utils::GenerateInt(1, 2) == 1 ? OneGeneMutation() : ReverseMutation();
    UpdateFitness();
}

void Chromosome::OneGeneMutation() {
    const auto size = static_cast<int>(genes.size());
    const auto firstPosition = Utils::GenerateInt(1, size - 2);
    const auto secondPosition = Utils::GenerateInt(1, size - 2);
    std::swap(genes[firstPosition], genes[secondPosition]);
}

void Chromosome::ReverseMutation() {
    std::ranges::reverse(genes);
}

void Chromosome::LocalImprovement(const double probability) {
    if (Utils::GenerateDouble(0, 1) > probability) {
        return;
    }

    Utils::GenerateInt(1, 2) == 1 ? SwapOneGeneLocalImprovement() : SwapTwoGenesLocalImprovement();
    UpdateFitness();
}

void Chromosome::SwapOneGeneLocalImprovement() {
    const auto improvedRoute = new Chromosome(genes);
    for (int i = 1; i < genes.size() - 2; i++) {
        for (int j = i + 1; j < genes.size() - 1; j++) {
            auto newRoute = improvedRoute->genes;
            std::swap(newRoute[i], newRoute[j]);
            improvedRoute->SetGenes(newRoute);
            if (improvedRoute->fitness < fitness) {
                this->SetGenes(newRoute);
                delete improvedRoute;
                return;
            }
            std::swap(newRoute[i], newRoute[j]);
            improvedRoute->SetGenes(newRoute);
        }
    }
    delete improvedRoute;
}

void Chromosome::SwapTwoGenesLocalImprovement() {
    SwapOneGeneLocalImprovement();
    SwapOneGeneLocalImprovement();
}