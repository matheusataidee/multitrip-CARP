#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

#include "utils.hpp"

using namespace std;

class Graph {
public:
    int _n, _m, nVehicles, vehicleCapacity, vehicleCost, tMax;
    int startId, disposalId;
    vector<vector<double> > edgeCost;
    vector<vector<double> > edgeTime;
    vector<vector<double> > pathCost;
    vector<vector<double> > pathTime;
    vector<vector<double> > edgeDemand;
    vector<pair<int, int> > requiredEdges;
    vector<bool> isEdgeOk;

    Graph(const string filename);
    vector<Candidate> getCandidates(const vector<Vehicle>& vehicles);
    int lastTrip(const vector<Vehicle>& vehicles);
    void resetEdgeOk();
    bool isSolved();
private:
    void floydWarshall();
};

#endif // _GRAPH_H_