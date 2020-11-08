#include "utils.hpp"

using namespace std;

void showUsage(char* argv) {
    cout << "Usage: " << string(argv) << " <INSTANCE>" << endl;
}

void printSolution(const Solution& solution) {
        cout << "Total cost: " << solution.totalCost << endl;
        cout << "Found in " << solution.time << "seconds" << endl;
        for (int i = 0; i < solution.vehicles.size(); i++) {
                cout << "Vehicle " << i << ": ";
                for (const pair<int, int>& edge : solution.vehicles[i].edges) {
                        cout << "(" << edge.first << ", " << edge.second << ") ";
                }
                cout << endl;
        }
}

Candidate getChosen(const vector<Candidate>& candidates, double alpha) {
        double minCost = candidates.front().cost;
        double maxCost = candidates.back().cost;
        double acceptableCost = minCost + (maxCost - minCost) * alpha;

        int n = 0;
        while (n < candidates.size() && candidates[n].cost <= acceptableCost) n++;

        int chosenId = rand() % n;
        return candidates[chosenId];
}

Vehicle::Vehicle(int capacity, int startVertex) {
        remainingCapacity = capacity;
        elapsedTime = 0;
        currentVertex = startVertex;
}

Solution::Solution(int capacity, int nVehicles, int startVertex) {
        vehicleCapacity = capacity;
        totalCost = 0;
        for (int i = 0; i < nVehicles; i++) {
                vehicles.push_back(Vehicle(capacity, startVertex));
        }
}
