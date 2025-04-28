#include<iostream>
#include<queue>
using namespace std;

// Node class represents a vertex in the graph
class Node {
   private:
       int vertex;
       Node* next;
   public:
       Node() {
           vertex = 0;
           next = nullptr;
       }
       Node(int vertex) {
           this->vertex = vertex;
           next = nullptr;
       }
       friend class Graph;
};

// Graph class represents the graph structure
class Graph {
   private:
       Node* head[100];
       bool visited[100];
       int vertices;
       int edges;
   public:
       void create_graph() {
           cout << "Enter the number of vertices in the graph: ";
           cin >> vertices;
           for (int i = 0; i <= vertices; i++) {
               head[i] = nullptr;
               visited[i] = false;
           }
           cout << "Enter the number of edges in the graph: ";
           cin >> edges;
           while (edges--) {
               int startVertex, endVertex;
               cout << "Enter an edge (startVertex, endVertex): ";
               cin >> startVertex >> endVertex;
               insert_graph(startVertex, endVertex);
               insert_graph(endVertex, startVertex);
           }
           cout << endl;
       }


       void insert_graph(int startVertex, int endVertex) {
           Node* newNode = new Node(endVertex);
           if (head[startVertex] == nullptr) {
               head[startVertex] = newNode;
           } else {
               Node* temp = head[startVertex];
               while (temp->next != nullptr) {
                   temp = temp->next;
               }
               temp->next = newNode;
           }
       }


       // Function to display the graph
       void display() {
           for (int i = 1; i <= vertices; i++) {
               cout << i << " -> ";
               Node* temp = head[i];
               while (temp != nullptr) {
                   cout << temp->vertex;
                   if (temp->next != nullptr) {
                       cout << ", ";
                   }
                   temp = temp->next;
               }
               cout << endl;
           }
       }


       // Recursive function for Depth-First Search (DFS)
       void DFS(int vertex) {
           cout << vertex << " ";
           visited[vertex] = true;
           Node* temp = head[vertex];
           while (temp != nullptr) {
               int adjacentVertex = temp->vertex;
               if (!visited[adjacentVertex]) {
                   DFS(adjacentVertex);
               }
               temp = temp->next;
           }
       }


       // Function to initiate DFS from a user-defined starting vertex
       void DFS() {
           int vertex;
           cout << "Enter the starting vertex for DFS: ";
           cin >> vertex;
           DFS(vertex);
           cout << endl;
           for (int i = 1; i <= vertices; i++) {
               visited[i] = false;
           }
       }


       // Function for Breadth-First Search (BFS) using STL queue
       void BFS(int vertex) {
           queue<int> q;
           q.push(vertex);
           visited[vertex] = true;
           while (!q.empty()) {
               int current = q.front();
               cout << current << " ";
               q.pop();
               Node* temp = head[current];
               while (temp != nullptr) {
                   int adjacentVertex = temp->vertex;
                   if (!visited[adjacentVertex]) {
                       q.push(adjacentVertex);
                       visited[adjacentVertex] = true;
                   }
                   temp = temp->next;
               }
           }
           cout << endl;
       }


       // Function to initiate BFS from a user-defined starting vertex
       void BFS() {
           int vertex;
           cout << "Enter the starting vertex for BFS: ";
           cin >> vertex;
           BFS(vertex);
           for (int i = 1; i <= vertices; i++) {
               visited[i] = false;
           }
       }
};


int main() {
   Graph g;
   int choice;


   do {
       cout << "\nMenu:\n";
       cout << "1. Create graph\n";
       cout << "2. Display graph\n";
       cout << "3. Perform DFS\n";
       cout << "4. Perform BFS\n";
       cout << "5. Exit\n";
       cout << "Enter your choice: ";
       cin >> choice;


       switch (choice) {
           case 1:
               g.create_graph();
               break;
           case 2:
               g.display();
               break;
           case 3:
               g.DFS();
               break;
           case 4:
               g.BFS();
               break;
           case 5:
               cout << "Exiting...\n";
               break;
           default:
               cout << "Invalid choice. Please try again.\n";
       }
   } while (choice != 5);
   return 0;
}


// OUTPUT
// Menu:
// 1. Create graph
// 2. Display graph
// 3. Perform DFS
// 4. Perform BFS
// 5. Exit
// Enter your choice: 1
// Enter the number of vertices in the graph: 7
// Enter the number of edges in the graph: 7
// Enter an edge (startVertex, endVertex): 1 2
// Enter an edge (startVertex, endVertex): 1 3
// Enter an edge (startVertex, endVertex): 2 4
// Enter an edge (startVertex, endVertex): 3 4
// Enter an edge (startVertex, endVertex): 4 5
// Enter an edge (startVertex, endVertex): 4 6
// Enter an edge (startVertex, endVertex): 3 7


// Menu:
// 1. Create graph
// 2. Display graph
// 3. Perform DFS
// 4. Perform BFS
// 5. Exit
// Enter your choice: 2
// 1 -> 2, 3
// 2 -> 1, 4
// 3 -> 1, 4, 7
// 4 -> 2, 3, 5, 6
// 5 -> 4
// 6 -> 4
// 7 -> 3

// Menu:
// 1. Create graph
// 2. Display graph
// 3. Perform DFS
// 4. Perform BFS
// 5. Exit
// Enter your choice: 3
// Enter the starting vertex for DFS: 1
// 1 2 4 3 7 5 6 

// Menu:
// 1. Create graph
// 2. Display graph
// 3. Perform DFS
// 4. Perform BFS
// 5. Exit
// Enter your choice: 4
// Enter the starting vertex for BFS: 1
// 1 2 3 4 7 5 6 

// Menu:
// 1. Create graph
// 2. Display graph
// 3. Perform DFS
// 4. Perform BFS
// 5. Exit
// Enter your choice: 5
// Exiting...




