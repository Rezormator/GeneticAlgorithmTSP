#include "Route.h"
#include <random>
#include <algorithm>

Route::Route() {
}

Route::Route(const matrixi *matrix) {
    generateRoute(matrix);
}

void Route::setRoute(const std::vector<int> &route) {
    this->route = route;
}

std::vector<int> Route::getRoute() const {
    return route;
}

int Route::getDistance() const {
    return distance;
}

void Route::generateRoute(const matrixi *matrix) {
    for (int j = 1; j < (*matrix)[0].size(); j++) {
        route.push_back(j);
    }
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::ranges::shuffle(route, rng);
    route.push_back(0);
    std::ranges::reverse(route);
    route.push_back(0);
    distance = calculateTotalDistance(matrix);
}

int Route::calculateTotalDistance(const matrixi *matrix) const {
    auto sum = 0;
    for (int i = 0; i < route.size() - 1; i++) {
        sum += (*matrix)[route[i]][route[i + 1]];
    }
    return sum;
}
