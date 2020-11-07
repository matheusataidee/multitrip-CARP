#include <iostream>
#include <climits>

#include "graph.hpp"
#include "utils.hpp"

using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        showUsage(argv[0]);
        return 0;
    }
    string filename = string(argv[1]);

    Graph g(filename);
    
    Solution bestSolution(0, 0);
    bestSolution.totalCost = INT_MAX;

    for (int iteration = 1; iteration <= 5000; iteration++) {

        Solution solution(g.vehicleCapacity, g.nVehicles);

        vector<Candidate> candidates = g.getCandidates(solution.vehicles); 
        while (!candidates.empty()) {
            Candidate chosen = getChosen(candidates, 0.2);

            solution.totalCost += chosen.cost;
            solution.vehicles[chosen.vehicleId].edges.push_back(g.requiredEdges[chosen.edgeId]);
            solution.vehicles[chosen.vehicleId].currentVertex = chosen.endVertex;
            solution.vehicles[chosen.vehicleId].remainingCapacity = chosen.endCapacity;

            g.isEdgeOk[chosen.edgeId] = true;

            candidates = g.getCandidates(solution.vehicles); 
        }
        solution.totalCost += g.lastTrip(solution.vehicles);
        if (solution.totalCost < bestSolution.totalCost) {
            bestSolution = solution;
        }

        g.resetEdgeOk();
    }

    printSolution(bestSolution);
    return 0;
}