#include <iostream>

#include "GeneticAlgorithm/GeneticAlgorithm.h"
#include "Graph/Graph.h"

int main() {
    int stop;
    const Graph graph(5, 5, 150);
    const auto route = GeneticAlgorithm::solveTSP(graph.getMatrix(), 3, 5, 0.5);
    std::cout << "Distance: " << route->getDistance();
    for (const auto point : route->getRoute()) {
        std::cout << ' ' << point;
    }
    std::cout << std::endl;
    std::cin >> stop;
    return 0;
}
