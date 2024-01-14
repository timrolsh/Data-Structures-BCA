# Graph Data Structure

* Have nodes/vertices that represent objects themselves in a graph
  * Like states in a finite state machine (FSM)
* Have edges/links that represent relationships between objects
  * Like transitions in a FSM

## Directed Graphs (Digraphs)

* Edges have direction
* Fsm is an example of directed graph: each transition is a directional edge from one state to another, and you can only take that transition by being in the first state and then going to the second state, not necessarily the other way around unless another edge/transition nodeExists to go that way

## Representing/Storing Graphs

* Can use abstract data types with Nodes and list of other nodes representing the edges that you can take to get to those nodes
* Can use adjacency matrix
  * label each state from 0 to n - 1 index
  * make an n by n matrix, `matrix[i][j]` will indicate whether there is an edge that will take you from node with index i to node with index j for example
