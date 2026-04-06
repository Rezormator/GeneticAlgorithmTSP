#pragma once

struct Configurations {
    int testIterations = 5;
    int cityCount = 1000;
    double mutationProbability = 0.5;
    double improveProbability = 0.5;
    int goalFitness = 0;

    int populationSize = 100;
    int iterations = 10000;

    int treads = 10;
    int parallelPopulationSize = 10;
    int epochIterations = 100;
    int totalEpochs = 50;
};
