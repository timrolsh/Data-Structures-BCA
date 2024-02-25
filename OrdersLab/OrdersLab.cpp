/*
Tim Rolsud
Data Structures
February 23rd, 2024
*/
#include <vector>
#include <set>

using std::set;
using std::vector;
using std::min;

using VI = vector<int>;

void findBridges(int u, vector<VI> &adjacencyList, VI &visited, VI &discoverTime, VI &lowestDiscoveryTime, VI &parent, set<int> &criticalNodes) {
    static int time = 0;
    visited[u] = 1;
    discoverTime[u] = lowestDiscoveryTime[u] = ++time;

    for (int v: adjacencyList[u]) {
        if (!visited[v]) {
            parent[v] = u;
            findBridges(v, adjacencyList, visited, discoverTime, lowestDiscoveryTime, parent, criticalNodes);
            lowestDiscoveryTime[u] = min(lowestDiscoveryTime[u], lowestDiscoveryTime[v]);
            if (lowestDiscoveryTime[v] > discoverTime[u]) {
                criticalNodes.insert(u);
                criticalNodes.insert(v);
            }
        } else if (v != parent[u]) {
            lowestDiscoveryTime[u] = min(lowestDiscoveryTime[u], discoverTime[v]);
        }
    }
}

vector<VI> convertToAdjList(int n, VI &tubes) {
    vector<VI> adj(n);
    for (size_t i = 0; i < tubes.size(); i += 2) {
        adj[tubes[i]].push_back(tubes[i + 1]);
        adj[tubes[i + 1]].push_back(tubes[i]);
    }
    return adj;
}

int transporters(int n, VI &tubes) {
    vector<VI> adjacencyList = convertToAdjList(n, tubes);
    VI visited(n, 0), discoverTime(n), lowestDiscoveryTime(n), parent(n, -1);
    set<int> criticalNodes;

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            findBridges(i, adjacencyList, visited, discoverTime, lowestDiscoveryTime, parent, criticalNodes);
        }
    }
    return (int) criticalNodes.size();
}

#include <iostream>
using std::cout;
// to be removed
int main() {
    int n = 7;
    vector<int> tubes = {6, 0, 0, 2, 0, 1, 1, 4, 1, 3, 2, 5};
    cout << transporters(n, tubes);
}
