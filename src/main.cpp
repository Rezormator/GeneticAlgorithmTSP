#include "AdjacencyMatrix/AdjacencyMatrix.h"
#include "Population/Population.h"
#include "Chromosome/Chromosome.h"
#include "GeneticAlgorithm/GeneticAlgorithm.h"

int main() {
    const auto adjacencyMatrix = new AdjacencyMatrix();

    GeneticAlgorithm::SetAdjacencyMatrix(adjacencyMatrix);
    const auto population = new Population();

    GeneticAlgorithm::SolveTSP(10, 0.5, 1, 200, 2000);

    delete adjacencyMatrix;
    delete population;

    return 0;
}
