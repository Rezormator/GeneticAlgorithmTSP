#include "Route.h"
#include "../AdjacencyMatrix/AdjacencyMatrix.h"
#include <random>
#include <algorithm>
#include <iostream>
#include "../RandomGenerator/RandomGenerator.h"

Route::Route() {
    generateRoute();
    calculateDistance();
}

Route::Route(const std::vector<int>& route) : route(route) {
    calculateDistance();
}

void Route::setRoute(const std::vector<int> &route) {
    this->route = route;
    calculateDistance();
}

std::vector<int> Route::getRoute() const {
    return route;
}

int Route::getDistance() const {
    return distance;
}

void Route::mutation(const double mutationProbability) {
    if (RandomGenerator::generateDouble(0, 1) <= mutationProbability) {
        if (RandomGenerator::generateInt(1, 2) == 1) {
            oneGeneMutation();
        }
        else {
            reverseMutation();
        }
        calculateDistance();
    }
}

void Route::oneGeneMutation() {
    const auto size = static_cast<int>(route.size());
    const auto firstPosition = RandomGenerator::generateInt(1, size - 2);
    const auto secondPosition = RandomGenerator::generateInt(1, size - 2);
    std::swap(route[firstPosition], route[secondPosition]);
}

void Route::reverseMutation() {
    std::ranges::reverse(route);
}

void Route::localImprovement() {
    if (RandomGenerator::generateInt(1, 2) == 1) {
        swapOneGeneLocalImprovement();
    }
    else {
        swapTwoGenesLocalImprovement();
    }
    calculateDistance();
}

void Route::swapOneGeneLocalImprovement() {
    const auto improvedRoute = new Route(route);
    for (int i = 1; i < route.size() - 2; i++) {
        for (int j = i + 1; j < route.size() - 1; j++) {
            auto newRoute = improvedRoute->route;
            std::swap(newRoute[i], newRoute[j]);
            improvedRoute->setRoute(newRoute);
            if (improvedRoute->distance < distance) {
                this->setRoute(newRoute);
                delete improvedRoute;
                return;
            }
            std::swap(newRoute[i], newRoute[j]);
            improvedRoute->setRoute(newRoute);
        }
    }
    delete improvedRoute;
}

void Route::swapTwoGenesLocalImprovement() {
    for (int k = 0; k < 2; k++) {
        swapOneGeneLocalImprovement();
    }
}

void Route::print(const bool printRoute) const {
    std::cout << "Distance: " << distance << std::endl;
    if (printRoute) {
        std::cout << "Route:";
        for (const auto point : route) {
            std::cout << ' ' << point;
        }
        std::cout << std::endl;
    }
}

void Route::generateRoute() {
    for (int j = 1; j < (*AdjacencyMatrix::getAdjacencyMatrixMatrix())[0].size(); j++) {
        route.push_back(j);
    }
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::ranges::shuffle(route, rng);
    route.push_back(0);
    std::ranges::reverse(route);
    route.push_back(0);
}

void Route::calculateDistance() {
    const auto adjacencyMatrix = AdjacencyMatrix::getAdjacencyMatrixMatrix();
    const auto size = (*adjacencyMatrix)[0].size();
    distance = 0;
    for (int i = 0; i < size; i++) {
        distance += (*adjacencyMatrix)[route[i]][route[i + 1]];
    }
}
