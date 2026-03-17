#pragma once
#include "../Chromosome/Chromosome.h"

class Population {
    static constexpr int DEFAULT_SIZE = 10;
private:
    std::vector<Chromosome *> chromosomes;
    int size;
    void GeneratePopulation();
    NODISCARD std::vector<double> CalculateProbabilityDistribution() const;
    void Sort();
public:
    explicit Population(int size = DEFAULT_SIZE);
    ~Population();

    void SetPopulation(const std::vector<Chromosome *>& chromosomes);
    NODISCARD std::vector<Chromosome *> GetPopulation() const;

    NODISCARD Chromosome *GetBestChromosome();
    NODISCARD std::pair<int, int> SelectParents() const;
    NODISCARD Chromosome *Crossover(const std::pair<int, int> &parents) const;
    void AddChromosome(Chromosome *chromosome);
    void DeleteWorstChromosome();
};
