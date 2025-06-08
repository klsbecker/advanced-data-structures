/**
 * University of Vale do Rio dos Sinos (UNISINOS)
 * Computer Engineering Course
 * Advanded Data Structures and Algorithms
 * 
 * Project: TGB - A* Pathfinding Algorithm
 * 
 * Author: Klaus Becker
 * 
 * Description: 
 * This file contains the main implementation of the A* pathfinding
 * algorithm, including the Graph class structure and a practical example
 * of its execution.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <limits>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Node {
    int vertex;
    int fCost;

    bool operator>(const Node& other) const {
        return fCost > other.fCost;
    }
};

class Graph {
private:
    int numVertices;
    vector<vector<pair<int, int>>> adjList;
    vector<pair<int, int>> coordinates;
public:
    Graph(int V) : numVertices(V) {
        adjList.resize(V);
        coordinates.resize(V);
    }

    void printGraph() const {
        if (coordinates.empty()) return;

        int gridWidth = numVertices;
        int gridHeight = numVertices;

        vector<vector<string>> displayGrid(gridHeight, vector<string>(gridWidth, "[-]"));

        cout << "======================" << endl;
        cout << "   Coordinates Map" << endl;
        cout << "======================" << endl;
        cout << "    ";
        for (int i = 0; i < numVertices; ++i)
            displayGrid[coordinates[i].first][coordinates[i].second] = "[" + to_string(i) + "]";
        for (int x = 0; x < gridWidth; ++x)
            cout << x << "  ";
        cout << endl;
        for (int y = 0; y < gridHeight; ++y) {
            cout << " " << y << " ";
            for (int x = 0; x < gridWidth; ++x)
                cout << displayGrid[y][x];
            cout << endl;
        }
        cout << "======================" << endl << endl;

        cout << "======================" << endl;
        cout << "    Adjacency List" << endl;
        cout << "======================" << endl;
        displayGrid.assign(gridHeight, std::vector<std::string>(gridWidth, "[-]"));
        for (int u = 0; u < numVertices; ++u) {
            cout << " " << u << ": ";
            if (adjList[u].empty()) {
                cout << "No connections" << endl;
            } else {
                for (const auto& adj : adjList[u]) {
                    int v = adj.first;
                    int weight = adj.second;
                    cout << v << "(" << weight << ")" << (adjList[u].back() == pair<int, int>{v, weight} ? "" : " → ");
                    displayGrid[u][v] = "[" + to_string(weight) + "]";
                    displayGrid[v][u] = "[" + to_string(weight) + "]";
                }
                cout << endl;
            }
        }
        cout << "======================" << endl << endl;

        cout << "======================" << endl;
        cout << "   Adjacency Matrix" << endl;
        cout << "======================" << endl;

        cout << "    ";
        for (int x = 0; x < gridWidth; ++x)
            cout << x << "  ";
        cout << endl;
        for (int y = 0; y < gridHeight; ++y) {
            cout << " " << y << " ";
            for (int x = 0; x < gridWidth; ++x)
                cout << displayGrid[y][x];
            cout << endl;
        }
        cout << "======================" << endl << endl;
    }

    bool isOutOfBounds(int vertex) {
        return vertex < 0 || vertex >= numVertices;
    }

    bool isOutOfBounds(int u, int v) {
        if (isOutOfBounds(u) || isOutOfBounds(v)) {
            cerr << "<ERROR> Invalid vertex index (" << u << ", " << v << ")." << endl;
            return true;
        }
        return false;
    }

    void addEdge(int u, int v) {
        if (isOutOfBounds(u, v)) return;
        int weight = heuristic(u, v);
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight});
    }

    void setCoordinates(int vertex, int x, int y) {
        if (isOutOfBounds(vertex)) return;
        coordinates[vertex] = {x, y};
    }

    int heuristic(int u, int v) {
        int dx = coordinates[u].first - coordinates[v].first;
        int dy = coordinates[u].second - coordinates[v].second;
        return sqrt(dx * dx + dy * dy) + 0.5;
    }
    
    vector<int> aStar(int start, int goal) {
        if (isOutOfBounds(start, goal)) return {};
        
        if (start == goal) return {start};

        priority_queue<Node, vector<Node>, greater<Node>> openList;

        vector<bool> closedList(numVertices, false);

        vector<int> gCosts(numVertices, numeric_limits<int>::max());
        vector<int> parent(numVertices, -1);
        
        gCosts[start] = 0;
        openList.push({start, heuristic(start, goal)});
        
        while (!openList.empty()) {
            Node current = openList.top();
            openList.pop();
            
            int u = current.vertex;
            
            if (closedList[u]) continue;
            
            if (u == goal) {
                vector<int> path;
                int current = goal;
                while (current != -1) {
                    path.push_back(current);
                    current = parent[current];
                }
                reverse(path.begin(), path.end());
                return path;
            }

            for (const auto& adj : adjList[u]) {
                int v = adj.first;
                int weight = adj.second;

                if (closedList[v]) continue;

                int tentativeGCost = gCosts[u] + weight;

                if (tentativeGCost < gCosts[v]) {
                    parent[v] = u;
                    gCosts[v] = tentativeGCost;
                    int fCost = tentativeGCost + heuristic(v, goal);
                    openList.push({v, fCost});
                }
            }
        }

        return {};
    }
};

int main() {
    cout << endl;
    cout << "======================" << endl;
    cout << " A* Algorithm Example" << endl;
    cout << " Author: Klaus Becker" << endl;
    cout << "======================" << endl;
    cout << endl;

    Graph g(6);

    g.setCoordinates(0, 0, 0);
    g.setCoordinates(1, 2, 1);
    g.setCoordinates(2, 4, 0);
    g.setCoordinates(3, 1, 3);
    g.setCoordinates(4, 3, 3);
    g.setCoordinates(5, 5, 5);

    g.addEdge(0, 1);
    g.addEdge(0, 3);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 5);
    g.addEdge(3, 4);
    g.addEdge(4, 5);

    g.printGraph();

    int start_node = 0;
    int goal_node = 5;

    vector<int> path = g.aStar(start_node, goal_node);

    if (!path.empty()) {
        cout << "Path found from " << start_node << " to " << goal_node << ": ";
        for (int i = 0; i < path.size(); ++i) {
            cout << path[i] << (i == path.size() - 1 ? "" : " → ");
        }
        cout << endl;
    } else {
        cout << "No path found from " << start_node << " to " << goal_node << "." << endl;
    }
    cout << endl;

    return 0;
}
