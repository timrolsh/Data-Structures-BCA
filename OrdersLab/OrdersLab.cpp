/*
Tim Rolshud
Data Structures
February 23rd, 2024
*/
#include <vector>

using std::vector;

typedef vector<int> VI;

struct NodesGraph {
    vector<VI> adjacencyList;
    vector<bool> visited;
    int totalNodes;

    /*
    Constructor for this struct
    */
    NodesGraph(int n, int node, vector<int> &tubes) {
        adjacencyList = vector<VI>(n);
        visited = vector<bool>(n);
        totalNodes = n;

        for (int a = 0; a < tubes.size(); a += 2) {
            if (tubes[a] != node && tubes[a + 1] != node) {
                adjacencyList[tubes[a]].push_back(tubes[a + 1]);
                adjacencyList[tubes[a + 1]].push_back(tubes[a]);
            }
        }
    }

    /*
    Count he number of connected nodes in the graph after a specific node
    has been removed by excluding any edges connected to that node
    */
    int countConnectedComponents() {
        int count = 0;
        for (int i = 0; i < totalNodes; i++) {
            if (!visited[i]) {
                ++count;
                traverseNodes(i);
            }
        }
        return count;
    }

    /*
    Perform a DFS traversal of the Node Graph given a Node index
    */
    void traverseNodes(int nodeIndex) {
        visited[nodeIndex] = true;
        for (int i: adjacencyList[nodeIndex]) {
            if (!visited[i]) {
                traverseNodes(i);
            }
        }
    }
};

int transporters(int n, vector<int> &tubes) {
    int count = 0;
    int tempMax = -1;

    for (int node = 0; node < n; ++node) {
        NodesGraph graph(n, node, tubes);
        tempMax = graph.countConnectedComponents();
        if (tempMax > count) {
            count = tempMax;
        }
    }
    return count;
}
