#include "Evaluator.h"
#include <assert.h>

Evaluator::Evaluator(const matrix &adjacencyMatrix) : adjacencyMatrix(adjacencyMatrix) {
}

void Evaluator::Evaluate(Chromosome &chromosome) const {
    int total = 0;
    const auto &genes = chromosome.genes;

    for (size_t i = 0; i < genes.size() - 1; i++) {
        total += adjacencyMatrix[genes[i]][genes[i + 1]];
    }

    chromosome.fitness = total;
}

int Evaluator::EvaluateDelta(const Chromosome &chromosome, const int i, const int j) const {
    const auto &genes = chromosome.genes;

    const int oldFitness = i == j - 1
       ? adjacencyMatrix[genes[i - 1]][genes[i]] + adjacencyMatrix[genes[i]][genes[j]] +
         adjacencyMatrix[genes[j]][genes[j + 1]]
       : adjacencyMatrix[genes[i - 1]][genes[i]] + adjacencyMatrix[genes[i]][genes[i + 1]] +
         adjacencyMatrix[genes[j - 1]][genes[j]] + adjacencyMatrix[genes[j]][genes[j + 1]];

    const int newFitness = i == j - 1
       ? adjacencyMatrix[genes[i - 1]][genes[j]] + adjacencyMatrix[genes[j]][genes[i]] +
         adjacencyMatrix[genes[i]][genes[j + 1]]
       : adjacencyMatrix[genes[i - 1]][genes[j]] + adjacencyMatrix[genes[j]][genes[i + 1]] +
         adjacencyMatrix[genes[j - 1]][genes[i]] + adjacencyMatrix[genes[i]][genes[j + 1]];

    return chromosome.fitness - oldFitness + newFitness;
}
