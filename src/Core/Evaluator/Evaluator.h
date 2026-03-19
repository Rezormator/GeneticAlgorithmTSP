#pragma once

#include "../../Utils/Utils.h"
#include "../Chromosome/Chromosome.h"

class Evaluator {
private:
    const matrix& adjacencyMatrix;

public:
    explicit Evaluator(const matrix& adjacencyMatrix);

    void Evaluate(Chromosome& chromosome) const;
    NODISCARD int EvaluateDelta(const Chromosome& chromosome, int i, int j) const;
};