#include "Utils.h"
#include <random>
#include <algorithm>

namespace Utils {
    thread_local std::mt19937 rng{std::random_device{}()};

    int GenerateInt(const int a, const int b) {
        std::uniform_int_distribution<int> dist(a, b);
        return dist(rng);
    }

    double GenerateDouble(const double a, const double b) {
        std::uniform_real_distribution<double> dist(a, b);
        return dist(rng);
    }

    std::vector<int> Shuffle(std::vector<int> array) {
        std::ranges::shuffle(array, rng);
        return array;
    }
}