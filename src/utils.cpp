#include "utils.hpp"

using namespace std;

void showUsage(char* argv) {
    cout << "Usage: " << string(argv) << " <INSTANCE>" << endl;
}

void printSolution(const Solution& solution) {
        // TODO: show time to find best solution
        cout << "Total cost: " << solution.totalCost << endl;
        for (int i = 0; i < solution.vehicles.size(); i++) {
                cout << "Vehicle " << i << ": ";
                for (const pair<int, int>& edge : solution.vehicles[i].edges) {
                        cout << "(" << edge.first << ", " << edge.second << ") ";
                }
                cout << endl;
        }
}

Candidate getChosen(const vector<Candidate>& candidates, double alpha) {
        // TODO: chosen should get a random from alpha % best cost, not number of candidates
        int chosenId = rand() % (int)ceil((double)candidates.size() * alpha);
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
