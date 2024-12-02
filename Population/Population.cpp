#include "Population.h"
#include <algorithm>
#include <iostream>
#include "../RandomGenerator/RandomGenerator.h"

Population::Population(const int size) : size(size) {
    generatePopulation();
}

Population::~Population() {
    for (const auto chromosome : chromosomes) {
        delete chromosome;
    }
}

Route *Population::getBestRoute() {
    sort();
    return chromosomes[0];
}

std::pair<int, int> Population::selectParents() const {
    std::pair parents(-1, -1);
    const auto probabilityDistribution = calculateProbabilityDistribution();
    parents.first = getGeneIndex(probabilityDistribution);
    do {
        parents.second = getGeneIndex(probabilityDistribution);
    } while (parents.first == parents.second);
    return parents;
}

Route *Population::crossover(const std::pair<int, int> &parents) const {
    const auto firstParent = chromosomes[parents.first];
    const auto secondParent = chromosomes[parents.second];
    const auto routeSize = static_cast<int>(firstParent->getRoute().size());
    Route *route;
    switch (RandomGenerator::generateInt(1, 3)) {
        case 1:
            route = orderCrossover(firstParent, secondParent, routeSize);
            break;
        case 2:
            route = halfCrossover(firstParent, secondParent, routeSize);
            break;
        default:
            route = cycleCrossover(firstParent, secondParent, routeSize);
            break;
    }
    return route;
}

void Population::addChromosome(Route *chromosome) {
    chromosomes.push_back(chromosome);
}

void Population::deleteWorst() {
    sort();
    chromosomes.pop_back();
}

void Population::print() const {
    for (const auto chromosome : chromosomes) {
        chromosome->print();
    }
    std::cout << std::endl;
}

Route *Population::orderCrossover(const Route *firstParent, const Route *secondParent, const int routeSize) {
    auto startPosition = RandomGenerator::generateInt(1, routeSize - 2);
    auto endPosition = RandomGenerator::generateInt(1, routeSize - 2);
    if (startPosition > endPosition) {
        std::swap(startPosition, endPosition);
    }

    std::vector route(routeSize, 0);
    for (int i = startPosition; i < endPosition; i++) {
        route[i] = firstParent->getRoute()[i];
    }

    int currentPosition = 1;
    for (int i = 1; i < routeSize - 1; i++) {
        const auto point = secondParent->getRoute()[i];
        if (std::ranges::find(route, point) != route.end()) {
            continue;
        }
        while (route[currentPosition] != 0) {
            currentPosition++;
        }
        route[currentPosition] = point;
    }

    return new Route(route);
}

Route* Population::halfCrossover(const Route* firstParent, const Route* secondParent, const int routeSize) {
    std::vector route(routeSize, 0);
    for (int i = 1; i < routeSize - 1; i += 2) {
        route[i] = firstParent->getRoute()[i];
    }
    for (int i = 2; i < routeSize - 1; i += 2) {
        const auto point = secondParent->getRoute()[i];
        if (std::ranges::find(route, point) != route.end()) {
            continue;
        }
        route[i] = point;
    }
    int currentPosition = 1;
    for (int i = 1; i < routeSize - 1; i++) {
        const auto point = secondParent->getRoute()[i];
        if (std::ranges::find(route, point) != route.end()) {
            continue;
        }
        while (route[currentPosition] != 0) {
            currentPosition++;
        }
        route[currentPosition] = point;
    }
    return new Route(route);
}

Route *Population::cycleCrossover(const Route *firstParent, const Route *secondParent, const int routeSize) {
    std::vector route(routeSize, 0);
    const auto firstRoute = firstParent->getRoute();
    const auto secondRoute = secondParent->getRoute();
    for (int i = 1; i < routeSize - 1; i++) {
        const auto position = std::distance(secondRoute.begin(), std::ranges::find(secondRoute, firstRoute[i]));
        route[firstRoute[i]] = static_cast<int>(position);
    }
    return new Route(route);
}

void Population::sort() {
    std::ranges::sort(chromosomes, [](const Route *a, const Route *b) { return a->getDistance() < b->getDistance(); });
}

void Population::generatePopulation() {
    for (int i = 0; i < size; i++) {
        chromosomes.push_back(new Route());
    }
}

std::vector<double> Population::calculateProbabilityDistribution() const {
    std::vector<double> probabilityDistribution;
    double distanceTotal = 0;
    for (const auto gene : chromosomes) {
        distanceTotal += 1.0 / gene->getDistance();
    }
    for (int i = 0; i < chromosomes.size(); i++) {
        double geneProbability = 1.0 / chromosomes[i]->getDistance() / distanceTotal;
        if (probabilityDistribution.empty()) {
            probabilityDistribution.push_back(geneProbability);
        }
        else {
            probabilityDistribution.push_back(probabilityDistribution[i - 1] + geneProbability);
        }
    }
    return probabilityDistribution;
}

int Population::getGeneIndex(const std::vector<double> &probabilityDistribution) {
    const auto probability = RandomGenerator::generateDouble(0, 1);
    int geneIndex = 0;
    for (const auto geneProbability : probabilityDistribution) {
        if (probability > geneProbability) {
            geneIndex++;
        }
        else {
            break;
        }
    }
    return geneIndex;
}
