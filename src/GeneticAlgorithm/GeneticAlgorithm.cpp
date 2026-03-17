#include "GeneticAlgorithm.h"
#include "../Population/Population.h"

namespace GeneticAlgorithm {
    AdjacencyMatrix *adjacencyMatrix = nullptr;

    void SetAdjacencyMatrix(AdjacencyMatrix *adjacencyMatrix) {
        GeneticAlgorithm::adjacencyMatrix = adjacencyMatrix;
    }

    matrix *GetMatrix() {
        return adjacencyMatrix->GetAdjacencyMatrix();
    }

    AdjacencyMatrix *GetAdjacencyMatrix() {
        return adjacencyMatrix;
    }

    int GetGeneIndex(const std::vector<double> &probabilityDistribution) {
        const auto probability = Utils::GenerateDouble(0, 1);
        int geneIndex = 0;
        for (const auto geneProbability : probabilityDistribution) {
            if (probability > geneProbability) {
                geneIndex++;
            }
            else {
                break;
            }
        }
        return geneIndex;
    }

    Chromosome *OrderCrossover(const Chromosome *firstParent, const Chromosome *secondParent, const int genesCount) {
        auto startPosition = Utils::GenerateInt(1, genesCount - 2);
        auto endPosition = Utils::GenerateInt(1, genesCount - 2);
        if (startPosition > endPosition) {
            std::swap(startPosition, endPosition);
        }

        std::vector genes(genesCount, 0);
        for (int i = startPosition; i < endPosition; i++) {
            genes[i] = firstParent->GetGenes()[i];
        }

        int currentPosition = 1;
        for (int i = 1; i < genesCount - 1; i++) {
            const auto point = secondParent->GetGenes()[i];
            if (std::ranges::find(genes, point) != genes.end()) {
                continue;
            }
            while (genes[currentPosition] != 0) {
                currentPosition++;
            }
            genes[currentPosition] = point;
        }

        return new Chromosome(genes);
    }

    Chromosome* HalfCrossover(const Chromosome* firstParent, const Chromosome* secondParent, const int genesCount) {
        std::vector genes(genesCount, 0);
        for (int i = 1; i < genesCount - 1; i += 2) {
            genes[i] = firstParent->GetGenes()[i];
        }

        for (int i = 2; i < genesCount - 1; i += 2) {
            const auto point = secondParent->GetGenes()[i];
            if (std::ranges::find(genes, point) != genes.end()) {
                continue;
            }
            genes[i] = point;
        }

        int currentPosition = 1;
        for (int i = 1; i < genesCount - 1; i++) {
            const auto point = secondParent->GetGenes()[i];
            if (std::ranges::find(genes, point) != genes.end()) {
                continue;
            }
            while (genes[currentPosition] != 0) {
                currentPosition++;
            }
            genes[currentPosition] = point;
        }

        return new Chromosome(genes);
    }

    Chromosome *CycleCrossover(const Chromosome *firstParent, const Chromosome *secondParent, const int genesCount) {
        std::vector genes(genesCount, 0);
        const auto firstChromosome = firstParent->GetGenes();
        const auto secondChromosome = secondParent->GetGenes();
        for (int i = 1; i < genesCount - 1; i++) {
            const auto position = std::distance(secondChromosome.begin(), std::ranges::find(secondChromosome, firstChromosome[i]));
            genes[firstChromosome[i]] = static_cast<int>(position);
        }
        return new Chromosome(genes);
    }

    Chromosome SolveTSP(const int populationSize, const double mutationProbability, const double improvementProbability, int iterationsCount, const int goal) {
        const auto population = new Population(populationSize);
        // std::cout << std::endl << "First population: " << std::endl;
        // population->print();
        int iteration = 0;

        do {
            const auto parents = population->SelectParents();
            const auto child = population->Crossover(parents);
            // child->print();
            child->Mutation(mutationProbability);
            child->LocalImprovement(improvementProbability);
            // std::cout << std::endl;
            population->AddChromosome(child);
            population->DeleteWorstChromosome();
            // population->print();
            iterationsCount--;
            iteration++;
        } while (goal < population->GetBestChromosome()->GetFitness() && iterationsCount != 0);

        // std::cout << "Last population: " << std::endl;
        // population->print();
        const auto route = *population->GetBestChromosome();
        delete population;
        // std::cout << "Result: " << std::endl;
        // genes.print(true);
        // std::cout << iteration;
        return route;
    }
}