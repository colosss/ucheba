#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <unordered_set>
#include <queue>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct Graph {
    int numVertices;
    vector<unordered_multiset<int>> adj;
    Graph(int n = 0) : numVertices(n), adj(n) {}
    void addEdge(int u, int v) {
        adj[u].insert(v);
        adj[v].insert(u);
    }
};

bool isConnected(const Graph& g, int start) {
    if (g.numVertices == 0) return true;
    vector<bool> visited(g.numVertices, false);
    queue<int> q;
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto it = g.adj[u].begin(); it != g.adj[u].end(); ++it) {
            int v = *it;
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    int countNonZero = 0;
    int countVisited = 0;
    vector<int> degrees(g.numVertices, 0);
    for (int i = 0; i < g.numVertices; ++i) {
        degrees[i] = g.adj[i].size();
    }
    for (int i = 0; i < g.numVertices; ++i) {
        if (degrees[i] > 0) {
            countNonZero++;
            if (visited[i]) countVisited++;
        }
    }
    return countVisited == countNonZero;
}

bool hasEulerPath(const Graph& g, int start) {
    if (!isConnected(g, start)) return false;
    vector<int> degrees(g.numVertices, 0);
    for (int i = 0; i < g.numVertices; ++i) {
        degrees[i] = g.adj[i].size();
    }
    int oddCount = 0;
    int odd1 = -1, odd2 = -1;
    for (int i = 0; i < g.numVertices; ++i) {
        if (degrees[i] % 2 == 1) {
            oddCount++;
            if (odd1 == -1) odd1 = i;
            else odd2 = i;
        }
    }
    if (oddCount != 0 && oddCount != 2) return false;
    if (oddCount == 2 && start != odd1 && start != odd2) return false;
    return true;
}

vector<int> getEulerPath(Graph g, int start) {
    vector<int> path;
    stack<int> stk;
    stk.push(start);
    while (!stk.empty()) {
        int u = stk.top();
        if (!g.adj[u].empty()) {
            int v = *g.adj[u].begin();
            g.adj[u].erase(g.adj[u].find(v));
            g.adj[v].erase(g.adj[v].find(u));
            stk.push(v);
        } else {
            path.push_back(u);
            stk.pop();
        }
    }
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    srand(time(NULL));
    int count = 0;
    bool cikl = true;
    Graph graph(0);
    int u, v, e, n, start;
    vector<vector<int>> inc;
    while (cikl) {
        switch (count) {
        case 0:
            cout << "***************************************************" << endl;
            cout << "1-Input Graph, 2-Euler Path, 3-Print Graph, 4-Exit" << endl;
            cin >> count;
            break;
        case 1:
            cout << "***************************************************" << endl;
            cout << "1-Add Vertex, 2-Add Edge, 3-Input Incidence, 4-Back, 5-Exit" << endl;
            cin >> count;
            count = (count == 4) ? 0 : (count == 5) ? 4 : count + 10;
            break;
        case 2:
            if (graph.numVertices == 0) {
                cout << "Graf pustoy" << endl;
                count = 0;
                break;
            }
            cout << "Vvedite nachalnuyu vershinu (0 do " << graph.numVertices - 1 << "): ";
            cin >> start;
            if (start < 0 || start >= graph.numVertices) {
                cout << "Nevernaya vershina" << endl;
                count = 0;
                break;
            }
            if (hasEulerPath(graph, start)) {
                cout << "Eylerov put suschestvuet." << endl;
                vector<int> path = getEulerPath(graph, start);
                cout << "Put: ";
                for (int p : path) cout << p << " ";
                cout << endl;
            } else {
                cout << "Eylerov put ot " << start << " ne suschestvuet" << endl;
            }
            count = 0;
            break;
        case 3:
            cout << "Spiski smejnosti:" << endl;
            for (int i = 0; i < graph.numVertices; i++) {
                cout << i << ": ";
                for (int j : graph.adj[i]) cout << j << " ";
                cout << endl;
            }
            count = 0;
            break;
        case 4:
            cikl = false;
            count = 0;
            break;
        case 11:
            graph.numVertices++;
            graph.adj.push_back(unordered_multiset<int>());
            cout << "Dobavlena vershina " << graph.numVertices - 1 << endl;
            count = 0;
            break;
        case 12:
            cout << "Vvedite u v: ";
            cin >> u >> v;
            if (u < 0 || u >= graph.numVertices || v < 0 || v >= graph.numVertices) {
                cout << "Neverno" << endl;
            } else {
                graph.addEdge(u, v);
                cout << "Dobavleno rebro " << u << "-" << v << endl;
            }
            count = 0;
            break;
        case 13:
            cout << "Vvedite kolichestvo vershin: ";
            cin >> n;
            cout << "Vvedite kolichestvo reber: ";
            cin >> e;
            inc.assign(n, vector<int>(e, 0));
            cout << "Vvedite matricu incidentnosti (" << n << " strok, " << e << " stolbcov):" << endl;
            for (int i = 0; i < n; i++) for (int j = 0; j < e; j++) cin >> inc[i][j];
            graph = Graph(n);
            for (int j = 0; j < e; j++) {
                vector<int> incident;
                for (int i = 0; i < n; i++) {
                    if (inc[i][j] != 0) incident.push_back(i); // predpolagaem 1 ili drugoe !=0
                }
                if (incident.size() == 2) {
                    graph.addEdge(incident[0], incident[1]);
                } else {
                    cout << "Nevernaya kolonka dlya rebra " << j << endl;
                }
            }
            cout << "Graf postroen iz matrici incidentnosti." << endl;
            count = 0;
            break;
        default:
            cout << "Necorrectniy vvod, povtorite vvod zanovo" << endl;
            count = 0;
            break;
        }
        cout << endl;
    }
    return 0;
}