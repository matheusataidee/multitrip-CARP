#include <iostream>
#include <climits>
#include <chrono>


#include "graph.hpp"
#include "utils.hpp"

using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        showUsage(argv[0]);
        return 0;
    }

    srand(0);

    string filename = string(argv[1]);

    Graph g(filename);
    
    Solution bestSolution(0, 0, 0);
    bestSolution.totalCost = INT_MAX;

    chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    double totalTime = 0;
    while (totalTime < 60) {

        Solution solution(g.vehicleCapacity, g.nVehicles, g.startId);

        vector<Candidate> candidates = g.getCandidates(solution.vehicles); 
        while (!candidates.empty()) {

            // TODO: parameterize alpha
            Candidate chosen = getChosen(candidates, 0.2);

            solution.totalCost += chosen.cost;
            solution.vehicles[chosen.vehicleId].edges.push_back(g.requiredEdges[chosen.edgeId]);
            solution.vehicles[chosen.vehicleId].currentVertex = chosen.endVertex;
            solution.vehicles[chosen.vehicleId].remainingCapacity = chosen.endCapacity;
            solution.vehicles[chosen.vehicleId].elapsedTime += chosen.timeIncrease;

            g.isEdgeOk[chosen.edgeId] = true;

            candidates = g.getCandidates(solution.vehicles); 
        }

        if (g.isSolved()) {
            solution.totalCost += g.lastTrip(solution.vehicles);
            if (solution.totalCost < bestSolution.totalCost) {

                chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                solution.time = chrono::duration_cast<chrono::microseconds>(end - begin).count() / (double)1000000;

                bestSolution = solution;
            }
        }

        g.resetEdgeOk();

        chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        totalTime = chrono::duration_cast<chrono::microseconds>(end - begin).count() / (double)1000000;
    }

    printSolution(bestSolution);
    return 0;
}