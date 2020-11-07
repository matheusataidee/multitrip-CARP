#include <fstream>

#include "graph.hpp"

Graph::Graph(const string filename) {
    ifstream fin(filename);
    string line, skip;
    getline(fin, line);
    stringstream ss(line);
    
    ss >> nVehicles >> vehicleCapacity >> vehicleCost;

    getline(fin, line); ss = stringstream(line);
    ss >> tMax;

    getline(fin, line); ss = stringstream(line);
    ss >> _n >> _m;

    edgeCost = vector<vector<double> >(_n + 1, vector<double>(_n + 1, 99999999));
    edgeTime = vector<vector<double> >(_n + 1, vector<double>(_n + 1, 99999999));
    pathCost = vector<vector<double> >(_n + 1, vector<double>(_n + 1, 99999999));
    pathTime = vector<vector<double> >(_n + 1, vector<double>(_n + 1, 99999999));
    edgeDemand = vector<vector<double> >(_n + 1, vector<double>(_n + 1, 0));

    for (int i = 0; i < _m; i++) {
        getline(fin, line);
        stringstream ss(line);

        int from, to, cost, demand, time;
        ss >> from >> to >> cost >> time >> demand;

        edgeCost[from][to] = edgeCost[to][from] = pathCost[from][to] = pathCost[to][from]= cost;
        edgeTime[from][to] = edgeTime[to][from] = pathTime[from][to] = pathTime[to][from] = time;
        edgeDemand[from][to] = edgeDemand[to][from] = demand;

        if (demand > 0) {
            requiredEdges.push_back({from, to});
        }
    }
    getline(fin, line); ss = stringstream(line);
    ss >> startId >> disposalId;

    isEdgeOk = vector<bool>(requiredEdges.size(), false);
    floydWarshall();
    fin.close();
}

vector<Candidate> Graph::getCandidates(const vector<Vehicle>& vehicles) {
    vector<Candidate> candidates;
    for (int i = 0; i < isEdgeOk.size(); i++) {
        if (isEdgeOk[i]) continue;
        for (int j = 0; j < vehicles.size(); j++) {
            int current = vehicles[j].currentVertex, baseCost = 0, endDemand;
            int firstUseCost = (vehicles[j].edges.empty()) ? vehicleCost : 0;
            if (vehicles[j].remainingCapacity >= edgeDemand[requiredEdges[i].first][requiredEdges[i].second]) {
                endDemand = vehicles[j].remainingCapacity - edgeDemand[requiredEdges[i].first][requiredEdges[i].second];
            } else {
                baseCost = pathCost[current][disposalId];
                current = disposalId;
                endDemand = vehicleCapacity - edgeDemand[requiredEdges[i].first][requiredEdges[i].second];
            }
            int from = requiredEdges[i].first;
            int to =   requiredEdges[i].second;
            int minCost = min(pathCost[current][from] + edgeCost[from][to], 
                                pathCost[current][to] + edgeCost[to][from]);
            Candidate candidate = Candidate(0, 0, 0, 0, 0, 0);
            if (pathCost[current][from] + edgeCost[from][to] <
                pathCost[current][to] + edgeCost[to][from]) {
                candidate = Candidate(baseCost + minCost + firstUseCost, j, i, to, endDemand, baseCost + minCost);
            } else {
                candidate = Candidate(baseCost + minCost + firstUseCost, j, i, from, endDemand, baseCost + minCost);
            }
            if (vehicles[j].elapsedTime + candidate.timeIncrease + pathTime[candidate.endVertex][disposalId]
                <= tMax) {
                candidates.push_back(candidate);
            }
        }
    }
    sort(begin(candidates), end(candidates));
    return candidates;
}

void Graph::resetEdgeOk() {
    for (int i = 0; i < isEdgeOk.size(); i++) {
        isEdgeOk[i] = false;
    }
}

void Graph::floydWarshall() {
    for (int i = 1; i < _n; i++) pathCost[i][i] = pathTime[i][i] = 0;
    for (int k = 1; k <= _n; k++) {
        for (int i = 1; i <= _n; i++) {
            for (int j = 1; j <= _n; j++) {
                if (pathCost[i][j] > pathCost[i][k] + pathCost[k][j]) {
                    pathCost[i][j] = pathCost[i][k] + pathCost[k][j];

                    // This is only viable because we are assuming time = cost is true
                    pathTime[i][j] = pathTime[i][k] + pathTime[k][j];
                }
            }
        }
    }
}

int Graph::lastTrip(const vector<Vehicle>& vehicles) {
    int addedCost = 0;
    for (int i = 0; i < vehicles.size(); i++) {

        if (vehicles[i].edges.empty()) continue;

        int current = vehicles[i].currentVertex;
        addedCost += pathCost[current][disposalId]; 
    }
    return addedCost;
}

bool Graph::isSolved() {
    for (bool ok : isEdgeOk) {
        if (!ok) return false;
    }
    return true;
}