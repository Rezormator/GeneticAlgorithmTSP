#pragma once

#include <vector>

#define matrix std::vector<std::vector<int>>
#define NODISCARD [[nodiscard]]

namespace Utils {
    int GenerateInt(int a, int b);
    double GenerateDouble(double a, double b);
    std::vector<int> Shuffle(std::vector<int> array);
}
