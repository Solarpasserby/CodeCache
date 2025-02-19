#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

class Graph {
private:
    vector<set<int>> adj; // 邻接链表，使用 set 保证字典序
    vector<bool> visited;
    int n; // 节点数量

    void dfsHelper(int node, vector<int> &result) {
        visited[node] = true;
        result.push_back(node);
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfsHelper(neighbor, result);
            }
        }
    }

public:
    Graph(int n) : n(n) {
        adj.resize(n + 1); // 节点编号从 1 开始
        visited.resize(n + 1, false);
    }

    void addEdge(int u, int v) {
        adj[u].insert(v);
        adj[v].insert(u);
    }

    void removeEdge(int u, int v) {
        adj[u].erase(v);
        adj[v].erase(u);
    }

    int connectedComponents(vector<int> &minNodes) {
        fill(visited.begin(), visited.end(), false);
        int components = 0;
        for (int i = 1; i <= n; i++) {
            if (!visited[i]) {
                components++;
                vector<int> temp;
                dfsHelper(i, temp);
                minNodes.push_back(*min_element(temp.begin(), temp.end()));
            }
        }
        sort(minNodes.begin(), minNodes.end());
        return components;
    }

    vector<int> dfs(int start) {
        fill(visited.begin(), visited.end(), false);
        vector<int> result;
        dfsHelper(start, result);
        return result;
    }

    vector<int> bfs(int start) {
        fill(visited.begin(), visited.end(), false);
        vector<int> result;
        queue<int> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            result.push_back(node);

            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        return result;
    }

    int shortestPath(int start, int end) {
        if (start == end) return 0;

        vector<int> dist(n + 1, -1);
        queue<int> q;

        dist[start] = 0;
        q.push(start);

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (int neighbor : adj[node]) {
                if (dist[neighbor] == -1) {
                    dist[neighbor] = dist[node] + 1;
                    if (neighbor == end) return dist[neighbor];
                    q.push(neighbor);
                }
            }
        }
        return -1;
    }
};

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;

    Graph graph(n);

    for (int i = 0; i < m; i++) {
        int op, u, v;
        cin >> op >> u >> v;
        if (op == 0) {
            graph.addEdge(u, v);
        } else {
            graph.removeEdge(u, v);
        }
    }

    vector<int> minNodes;
    int components = graph.connectedComponents(minNodes);

    vector<int> dfsSeq = graph.dfs(s);
    vector<int> bfsSeq = graph.bfs(t);
    int shortestPathLength = graph.shortestPath(s, t);

    cout << components << endl;
    for (int node : minNodes) cout << node << " ";
    cout << endl;

    cout << dfsSeq.size() << endl;
    for (int node : dfsSeq) cout << node << " ";
    cout << endl;

    cout << bfsSeq.size() << endl;
    for (int node : bfsSeq) cout << node << " ";
    cout << endl;

    cout << shortestPathLength << endl;

    return 0;
}