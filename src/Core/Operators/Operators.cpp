#include "Operators.h"
#include <algorithm>
#include <numeric>
#include <ranges>
#include "../../Utils/Utils.h"

namespace Operators {
    void GenerateRandomGenes(Chromosome &chromosome, int cityCount) {
        auto vals = std::views::iota(1, cityCount);
        std::vector array(vals.begin(), vals.end());
        array = Utils::Shuffle(std::move(array));

        chromosome.genes.clear();
        chromosome.genes.reserve(cityCount + 1);

        chromosome.genes.push_back(0);
        chromosome.genes.insert(chromosome.genes.end(), array.begin(), array.end());
        chromosome.genes.push_back(0);
    }

    void ApplyMutation(Chromosome &chromosome, const double probability, const Evaluator &evaluator) {
        const size_t size = chromosome.genes.size();
        if (size < 4) {
            return;
        }

        if (Utils::GenerateDouble(0, 1) > probability) {
            return;
        }

        if (Utils::GenerateInt(1, 2) == 1) {
            const int i = Utils::GenerateInt(1, static_cast<int>(size) - 2);
            const int j = Utils::GenerateInt(1, static_cast<int>(size) - 2);
            std::swap(chromosome.genes[i], chromosome.genes[j]);
        }
        else {
            std::ranges::reverse(chromosome.genes);
        }

        evaluator.Evaluate(chromosome);
    }

    void LocalImprovement(Chromosome &chromosome, const double probability, const Evaluator &evaluator) {
        if (Utils::GenerateDouble(0, 1) > probability) {
            return;
        }

        const auto size = chromosome.genes.size();

        for (int i = 1; i < size - 2; i++) {
            for (int j = i + 1; j < size - 1; j++) {
                const auto newFitness = evaluator.EvaluateDelta(chromosome, i, j);

                if (newFitness < chromosome.fitness) {
                    std::swap(chromosome.genes[i], chromosome.genes[j]);
                    chromosome.fitness = newFitness;
                    return;
                }
            }
        }
    }

    std::vector<double> CalculateProbabilityDistribution(std::vector<Chromosome> &chromosomes) {
        std::vector<double> probabilityDistribution;
        probabilityDistribution.reserve(chromosomes.size());

        double invertedDistanceTotal = 0;
        for (const auto &chromosome: chromosomes) {
            invertedDistanceTotal += 1.0 / chromosome.fitness;
        }

        probabilityDistribution.push_back(1.0 / chromosomes[0].fitness / invertedDistanceTotal);
        for (int i = 1; i < chromosomes.size() - 1; i++) {
            const double chromosomeProbability = 1.0 / chromosomes[i].fitness / invertedDistanceTotal;
            probabilityDistribution.push_back(probabilityDistribution[i - 1] + chromosomeProbability);
        }
        probabilityDistribution.push_back(1.0);

        return probabilityDistribution;
    }

    int GetIndexByProbability(const std::vector<double> &probabilityDistribution) {
        const double target = Utils::GenerateDouble(0.0, 1.0);
        const auto it = std::lower_bound(
            probabilityDistribution.begin(),
            probabilityDistribution.end(),
            target);
        return static_cast<int>(std::distance(probabilityDistribution.begin(), it));
    }

    std::pair<int, int> SelectParentIndices(const std::vector<double> &probabilityDistribution) {
        std::pair parents(GetIndexByProbability(probabilityDistribution), -1);
        do {
            parents.second = GetIndexByProbability(probabilityDistribution);
        } while (parents.first == parents.second);
        return parents;
    }

    Chromosome OrderCrossover(const Chromosome &firstParent, const Chromosome &secondParent, const int genesCount) {
        auto startPosition = Utils::GenerateInt(1, genesCount - 2);
        auto endPosition = Utils::GenerateInt(1, genesCount - 2);
        if (startPosition > endPosition) {
            std::swap(startPosition, endPosition);
        }

        std::vector genes(genesCount, 0);
        for (int i = startPosition; i < endPosition; i++) {
            genes[i] = firstParent.genes[i];
        }

        int currentPosition = 1;
        for (int i = 1; i < genesCount - 1; i++) {
            const auto point = secondParent.genes[i];
            if (std::ranges::find(genes, point) != genes.end()) {
                continue;
            }
            while (genes[currentPosition] != 0) {
                currentPosition++;
            }
            genes[currentPosition] = point;
        }

        return Chromosome(genes);
    }

    Chromosome HalfCrossover(const Chromosome &firstParent, const Chromosome &secondParent, const int genesCount) {
        std::vector genes(genesCount, 0);
        std::vector visited(genesCount, false);
        visited[0] = true;

        for (int i = 1; i < genesCount - 1; i += 2) {
            genes[i] = firstParent.genes[i];
            visited[genes[i]] = true;
        }

        int p2Pos = 1;
        for (int i = 1; i < genesCount - 1; i++) {
            if (genes[i] != 0) {
                continue;
            }
            while (p2Pos < genesCount - 1) {
                int gene = secondParent.genes[p2Pos++];
                if (!visited[gene]) {
                    genes[i] = gene;
                    visited[gene] = true;
                    break;
                }
            }
        }

        return Chromosome(genes);
    }

    Crossover GetRandomCrossover() {
        return Utils::GenerateInt(1, 2) == 1 ? OrderCrossover : HalfCrossover;
    }
}
