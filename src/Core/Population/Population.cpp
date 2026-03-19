#include "Population.h"
#include <algorithm>

Population::Population(const int size) {
    chromosomes.reserve(size);
}

void Population::SetChromosomes(std::vector<Chromosome> &&newChromosomes) {
    this->chromosomes = std::move(newChromosomes);
}

std::vector<Chromosome> &Population::GetChromosomes() {
    return chromosomes;
}

const std::vector<Chromosome> &Population::GetChromosomes() const {
    return chromosomes;
}

const Chromosome &Population::GetBest() const {
    return *std::ranges::min_element(chromosomes,
        [](const Chromosome &a, const Chromosome &b) {
            return a.fitness < b.fitness;
        }
    );
}

void Population::IntegrateChild(Chromosome &&child) {
    auto worst = std::ranges::max_element(chromosomes, std::ranges::less{}, &Chromosome::fitness);
    if (worst != chromosomes.end() && child.fitness < worst->fitness) {
        *worst = std::move(child);
    }
}
