#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

typedef long long ll;

struct Edge {
	int a, b, cost, time, demand;
};

int getFarNode(vector<vector<ll> >& g) {
	int n = g.size() - 1;
	for (int i = 1; i <= n; i++) g[i][i] = 0;
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (g[i][j] > g[i][k] + g[k][j]) {
					g[i][j] = g[i][k] + g[k][j];
				}
			}
		}
	}
	int who = 1;
	for (int i = 1; i <= n; i++) {
		if (g[1][who] < g[1][i]) who = i;
	}
	return who;
}

void showUsage(const string argv) {
	cout << "Usage: " << argv << " <INPUT FILENAME> <OUTPUT FILENAME>" << endl;
}

int main(int argc, char** argv) {
	if (argc < 3) {
		showUsage(string(argv[0]));
		return -1;
	}
	string inputFilename(argv[1]);
	string outputFilename(argv[2]);
	int n, m, nVehicles, vehicleCapacity;
	
	ifstream fin(inputFilename);
	ofstream fout(outputFilename);
	
	string line, skip;
	
	getline(fin, line);
	stringstream ss(line);
	
	ss >> skip >> skip >> n >> m >> nVehicles >> vehicleCapacity;
	
	vector<vector<ll> > g(n+1, vector<ll>(n+1, 0x7fffffff));
	
	vector<Edge> edges;
	
	int totalCost = 0;
	while (getline(fin, line)) {
		stringstream ss(line);
		int from, to, cost, demand;
		ss >> skip >> from >> to >> cost >> demand;
		
		g[from][to] = g[to][from] = cost;
		
		Edge edge;
		edge.a = from;
		edge.b = to;
		edge.cost = cost;
		edge.time = cost;
		edge.demand = demand;
		edges.push_back(edge);
		
		totalCost += cost;
	}
	
	int vehicleCost = totalCost / 2;
	int tMax = (3 * totalCost) / (nVehicles);
	
	
	fout << nVehicles << " " << vehicleCapacity << " " << vehicleCost << endl;
	fout << tMax << endl;
	fout << n << " " << m << endl; // number of vertex and number of edges
	for (Edge edge : edges) {
		fout << edge.a << " " << edge.b << " " << edge.cost << " " << 
				edge.time << " " << edge.demand << endl;
	}
	fout << "1 " << getFarNode(g) << endl; // depot and disposal vertexes
	fout.close();
	return 0;
}
