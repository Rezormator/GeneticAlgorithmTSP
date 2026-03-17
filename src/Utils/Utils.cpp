#include "Utils.h"
#include <random>
#include <algorithm>

namespace Utils {
    int GenerateInt(const int a, const int b) {
        thread_local std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist(a, b);
        return dist(rng);
    }

    double GenerateDouble(const double a, const double b) {
        thread_local std::mt19937 rng(std::random_device{}());
        std::uniform_real_distribution<double> dist(a, b);
        return dist(rng);
    }

    std::vector<int> Shuffle(std::vector<int> array) {
        thread_local std::mt19937 rng(std::random_device{}());
        std::ranges::shuffle(array, rng);
        return array;
    }

}