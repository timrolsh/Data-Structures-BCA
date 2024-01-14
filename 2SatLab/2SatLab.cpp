/*
Tim Rolshud
Data Structures
January 12th, 2024
*/
#include <iostream>
#include <stack>
#include <queue>
#include <vector>

using std::cout;
using std::cin;
using std::vector;
using std::queue;
using std::stack;
using std::find;
using std::fill;

// if the maximum variable size is 5000, doubling it to account for negatives will be 10000
const int MAX_VARIABLE_SIZE = 10000;

/*
These will be the graphs represented as lists where each vector is a variable and each vector of that vector is all
the other variables this variable points to in the graph
*/
vector<vector<int>> graph(MAX_VARIABLE_SIZE);
vector<vector<int>> graphTransposed(MAX_VARIABLE_SIZE);
vector<vector<int>> graphCondensed(MAX_VARIABLE_SIZE);
vector<vector<int>> components(MAX_VARIABLE_SIZE);

vector<bool> varVisited(MAX_VARIABLE_SIZE, false);
vector<bool> varExists(MAX_VARIABLE_SIZE, false);
stack<int> topSortStack;
queue<int> reversedTopSortQueue;
vector<int> sccList(MAX_VARIABLE_SIZE, 0);
int sccCount = 0;
vector<short> assignments(MAX_VARIABLE_SIZE, 0);

int negation(int var) {
    return MAX_VARIABLE_SIZE - var;
}

void initialDFS(int i, vector<vector<int>> &adjacenyMatrix) {
    if (!varVisited[i]) {
        varVisited[i] = true;
        for (int j: adjacenyMatrix[i]) {
            if (!varVisited[j]) {
                initialDFS(j, adjacenyMatrix);
            }
        }
        topSortStack.push(i);
    };

}

void transposedDFS(int i, vector<vector<int>> &listGraph) {
    if (!varVisited[i]) {
        varVisited[i] = true;
        for (int j: listGraph[i]) {
            if (!varVisited[j]) {
                transposedDFS(j, listGraph);
            }
        }
        sccList[i] = sccCount;
        components[sccCount].push_back(i);
    }

}

void condense(int i, vector<vector<int>> &listGraph) {
    if (!varVisited[i]) {
        varVisited[i] = true;
        for (int j: listGraph[i]) {
            if (sccList[i] == sccList[j]) continue;
            else {
                vector<int> &graphIndex = graphCondensed[sccList[i]];
                if (find(graphIndex.begin(), graphIndex.end(), sccList[j]) == graphIndex.end())
                    graphIndex.push_back(sccList[j]);
            }
            if (!varVisited[j]) {
                condense(j, listGraph);
            }
        }
    }

}

void dfsEnd(int i, vector<vector<int>> &listGraph) {
    if (!varVisited[i]) {
        varVisited[i] = true;
        for (int v: listGraph[i]) {
            if (!varVisited[v]) {
                dfsEnd(v, listGraph);
            }
        }
        reversedTopSortQueue.push(i);
    }
}

int main() {
    int variablesCount, clausesCount;
    cin >> variablesCount >> clausesCount;
    for (int i = 0; i < clausesCount; ++i) {
        int varOne, varTwo;
        cin >> varOne >> varTwo;
        varOne = (varOne > 0) ? varOne : varOne + MAX_VARIABLE_SIZE;
        varTwo = (varTwo > 0) ? varTwo : varTwo + MAX_VARIABLE_SIZE;
        graph[negation(varOne)].push_back(varTwo);
        graphTransposed[varTwo].push_back(negation(varOne));
        graph[negation(varTwo)].push_back(varOne);
        graphTransposed[varOne].push_back(negation(varTwo));
        varExists[varOne] = true;
        varExists[negation(varOne)] = true;
        varExists[varTwo] = true;
        varExists[negation(varTwo)] = true;
    }

    for (int i = 1; i < MAX_VARIABLE_SIZE; ++i) {
        if (varExists[i] && !varVisited[i]) {
            initialDFS(i, graph);
        }
    }
    fill(varVisited.begin(), varVisited.end(), false);
    while (!topSortStack.empty()) {
        int t = topSortStack.top();
        topSortStack.pop();
        if (!varVisited[t]) {
            transposedDFS(t, graphTransposed);
            ++sccCount;
        }
    }
    for (int i = 1; i <= 5000; ++i) {
        if (varExists[i] && sccList[i] == sccList[negation(i)]) {
            cout << "Not satisfiable\n";
            return 0;
        }
    }
    fill(varVisited.begin(), varVisited.end(), false);
    for (int i = 1; i < MAX_VARIABLE_SIZE; ++i) {
        if (!varVisited[i] && varExists[i]) {
            condense(i, graph);
        }
    }
    fill(varVisited.begin(), varVisited.end(), false);
    for (int i = 0; i < sccCount; ++i) {
        if (!varVisited[i]) {
            dfsEnd(i, graphCondensed);
        }
    }
    while (!reversedTopSortQueue.empty()) {
        int i = reversedTopSortQueue.front();
        reversedTopSortQueue.pop();
        for (int j: components[i]) {
            if (assignments[j] == 0) {
                assignments[j] = 1;
                assignments[negation(j)] = -1;
            }
        }
    }
    for (int i = 1; i <= variablesCount; ++i) {
        if (varExists[i]) {
            cout << (assignments[i] == 1 ? "T" : "F") << "\n";
        }
        else cout << "T\n";
    }

    return 0;
}