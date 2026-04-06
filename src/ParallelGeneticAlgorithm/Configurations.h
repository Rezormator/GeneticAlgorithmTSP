#pragma once

struct Configurations {
    int testIterations = 5;
    int cityCount = 1000;
    int populationSize = 100;
    int iterations = 100000;
    int treads = 10;
    int epochIterations = 100;
    int totalEpochs = 100;
    double mutationProbability = 0.5;
    double improveProbability = 0.5;
    int goalFitness = 0;
};
