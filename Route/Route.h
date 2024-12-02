#pragma once

#include <vector>
#include "../Utils.h"

class Route {
private:
    std::vector<int> route;
    int distance;
    void generateRoute();
    void calculateDistance();
    void oneGeneMutation();
    void reverseMutation();
    void swapOneGeneLocalImprovement();
    void swapTwoGenesLocalImprovement();
public:
    explicit Route();
    explicit Route(const std::vector<int> &route);
    void setRoute(const std::vector<int> &route);
    NODISCARD std::vector<int> getRoute() const;
    NODISCARD int getDistance() const;
    void mutation(double mutationProbability);
    void localImprovement();
    void print(bool printRoute = false) const;
};
