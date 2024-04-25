#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

// Tree class representing the adjacency list
class Tree {
    int V;  // Number of vertices
    vector<vector<int>> adj;  // Adjacency list

public:
    Tree(int V) : V(V), adj(V) {}

    // Add an edge to the tree
    void addEdge(int v, int w) {
        adj[v].push_back(w);
    }

    // Parallel Depth-First Search
    void parallelDFS(int startVertex) {
        vector<bool> visited(V, false);
        parallelDFSUtil(startVertex, visited);
    }

    // Parallel DFS utility function
    void parallelDFSUtil(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";

        #pragma omp parallel for
        for (int i = 0; i < adj[v].size(); ++i) {
            int n = adj[v][i];
            if (!visited[n])
                parallelDFSUtil(n, visited);
        }
    }

    // Parallel Breadth-First Search
    void parallelBFS(int startVertex) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[startVertex] = true;
        q.push(startVertex);

        while (!q.empty()) {
            int size = q.size();
            #pragma omp parallel for
            for (int j = 0; j < size; ++j) {
                int v = q.front();
                q.pop();
                cout << v << " ";

                for (int i = 0; i < adj[v].size(); ++i) {
                    int n = adj[v][i];
                    if (!visited[n]) {
                        visited[n] = true;
                        q.push(n);
                    }
                }
            }
        }
    }
};

int main() {
    // Create a tree
    Tree t(7);
    t.addEdge(0, 1);
    t.addEdge(0, 2);
    t.addEdge(1, 3);
    t.addEdge(1, 4);
    t.addEdge(2, 5);
    t.addEdge(2, 6);


    cout << "Depth-First Search (DFS): ";
    t.parallelDFS(0);
    cout << endl;

    cout << "Breadth-First Search (BFS): ";
    t.parallelBFS(0);
    cout << endl;

    return 0;
}
