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
    Vehicle(int capacity);
};

class Solution {
public:
    int totalCost;
    int vehicleCapacity;
    vector<Vehicle> vehicles;

    Solution(int capacity, int nVehicles);
};

class Candidate {
public:
    int cost;
    int vehicleId;
    int edgeId;
    int endVertex;
    int endCapacity;
    Candidate(int cost, int vehicleId, int edgeId, int endVertex, int endCapacity) : 
        cost(cost), vehicleId(vehicleId), edgeId(edgeId), endVertex(endVertex), endCapacity(endCapacity) {}
    bool operator<(const Candidate& other) {
        return cost < other.cost;
    }
};

void printSolution(const Solution& solution);

Candidate getChosen(const vector<Candidate>& candidates, double alpha);

#endif // _SOLUTION_H_