#ifndef _UTILS_H_
#define _UTILS_H_

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <stdlib.h>

using namespace std;

void showUsage(char* argv);

class Vehicle {
public:
    int currentVertex;
    int elapsedTime;
    int remainingCapacity;
    vector<pair<int, int> > edges;
    Vehicle(int capacity, int startVertex);
};

class Solution {
public:
    int totalCost;
    int vehicleCapacity;
    int maxTime;
    int carCost;
    vector<Vehicle> vehicles;

    Solution(int capacity, int nVehicles, int maxTime, int carCost, int startVertex);
};

class Candidate {
public:
    int cost;
    int vehicleId;
    int edgeId;
    int endVertex;
    int endCapacity;
    int timeIncrease;
    Candidate(int cost, int vehicleId, int edgeId, int endVertex, int endCapacity, int timeIncrease) : 
                    cost(cost), vehicleId(vehicleId), edgeId(edgeId), endVertex(endVertex),
                    endCapacity(endCapacity), timeIncrease(timeIncrease) {}
    bool operator<(const Candidate& other) {
        return cost < other.cost;
    }
};

void printSolution(const Solution& solution);

Candidate getChosen(const vector<Candidate>& candidates, double alpha);

#endif // _SOLUTION_H_