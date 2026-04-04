#include "Population.h"
#include <algorithm>

Population::Population(const int size) : bestChromosome(0), worstChromosome(0) {
    chromosomes.reserve(size);
}

void Population::SetChromosomes(std::vector<Chromosome> &&newChromosomes) {
    this->chromosomes = std::move(newChromosomes);
    for (int i = 1; i < chromosomes.size(); i++) {
        if (chromosomes[worstChromosome].fitness < chromosomes[i].fitness) {
            worstChromosome = i;
        }
        if (chromosomes[bestChromosome].fitness > chromosomes[i].fitness) {
            bestChromosome = i;
        }
    }
}

std::vector<Chromosome> &Population::GetChromosomes() {
    return chromosomes;
}

const std::vector<Chromosome> &Population::GetChromosomes() const {
    return chromosomes;
}

const Chromosome &Population::GetBest() const {
    return chromosomes[bestChromosome];
}

void Population::IntegrateChild(Chromosome &&child) {
    if (child.fitness < chromosomes[worstChromosome].fitness) {
        chromosomes[worstChromosome] = std::move(child);
        if (child.fitness < chromosomes[bestChromosome].fitness) {
            bestChromosome = worstChromosome;
        }
        worstChromosome = 0;
        for (int i = 1; i < chromosomes.size(); i++) {
            if (chromosomes[worstChromosome].fitness < chromosomes[i].fitness) {
                worstChromosome = i;
            }
        }
    }
}
