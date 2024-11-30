#include "RandomGenerator.h"
#include <random>

int RandomGenerator::generateInt(const int a, const int b) {
    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(a, b);
    return dist(rng);
}

double RandomGenerator::generateDouble(const double a, const double b) {
    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_real_distribution<double> dist(a, b);
    return dist(rng);
}