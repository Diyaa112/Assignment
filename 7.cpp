#include <iostream>
using namespace std;

class Tree {
    int a[20][20]; // Adjacency matrix to store the weights of the edges
    int l, u, w, i, j, v, e; // Variables for branches, connections, and weights
    int visited[20]; // Array to track visited vertices

public:
    void input();    // Function to input graph data
    void display();  // Function to display the adjacency matrix
    void minimum();  // Function to find and display the minimum spanning tree
};

// Function to input the graph data
void Tree::input() {
    cout << "Enter the number of branches: ";
    cin >> v; // Read the number of vertices (branches)

    // Initialize the adjacency matrix and visited array
    for (i = 0; i < v; i++) {
        visited[i] = 0; // Mark all vertices as unvisited
        for (j = 0; j < v; j++) {
            a[i][j] = 999; // Initialize all edges with a large value (infinity)
        }
    }

    cout << "Enter the number of connections: ";
    cin >> e; // Read the number of edges (connections)
    cout << endl;

    // Input the edges and their weights
    for (i = 0; i < e; i++) {
        cout << "Enter the first branch of connection " << i + 1 << " : ";
        cin >> l; // Read the first vertex of the edge
        cout << "Enter the second branch of connection " << i + 1 << " : ";
        cin >> u; // Read the second vertex of the edge
        cout << "Enter the phone company charges for this connection: ";
        cin >> w; // Read the weight of the edge
        a[l - 1][u - 1] = a[u - 1][l - 1] = w; // Update the adjacency matrix for both directions
        cout << endl;
    }
}

// Function to display the adjacency matrix
void Tree::display() {
    cout << "\nAdjacency matrix:";
    for (i = 0; i < v; i++) {
        cout << endl;
        for (j = 0; j < v; j++) {
            cout << a[i][j] << " "; // Print the weight of the edge
        }
        cout << endl;
    }
}

// Function to find and display the minimum spanning tree using Prim's algorithm
void Tree::minimum() {
    int p = 0, q = 0, total = 0, min;
    visited[0] = 1; // Start from the first vertex and mark it as visited

    // Loop to find (v - 1) edges for the MST
    for (int count = 0; count < (v - 1); count++) {
        min = 999; // Initialize min to a large value (infinity)

        // Loop through all vertices to find the minimum edge
        for (i = 0; i < v; i++) {
            if (visited[i] == 1) { // If vertex i is visited
                for (j = 0; j < v; j++) {
                    if (visited[j] != 1) { // If vertex j is not visited
                        // Check if the edge weight is less than the current minimum
                        if (min > a[i][j]) {
                            min = a[i][j]; // Update min
                            p = i; // Update the vertex from which the edge is taken
                            q = j; // Update the vertex to which the edge is going
                        }
                    }
                }
            }
        }

        // Mark the selected vertices as visited
        visited[q] = 1;

        // Add the weight of the selected edge to the total cost
        total += min;

        // Print the selected edge and its weight
        cout << "Minimum cost connection is " << (p + 1) << " -> " << (q + 1)
             << " with charge: " << min << endl;
    }

    // Print the total cost of the minimum spanning tree
    cout << "The minimum total cost of connections of all branches is: " << total << endl;
}

int main() {
    Tree t;
    t.input();
    t.display();
    t.minimum();
    return 0;
}


