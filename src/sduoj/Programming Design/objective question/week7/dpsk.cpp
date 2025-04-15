#include <bits/stdc++.h>
using namespace std;

const int MAX = 2e5 + 5;

struct Edge {
    int u, v, w;
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

int parent[MAX];

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

bool unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return false;
    parent[y] = x;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, p;
    cin >> n >> m >> p;

    vector<Edge> edges;
    for (int i = 1; i <= n; ++i) edges.emplace_back(0, i, p);

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.emplace_back(u, v, w);
    }

    sort(edges.begin(), edges.end());

    iota(parent, parent + n + 1, 0);

    int total = 0, connected = 0;
    for (const auto& e : edges) {
        if (unite(e.u, e.v)) {
            total += e.w;
            connected++;
            if (connected == n) break;
        }
    }

    cout << total << '\n';
    return 0;
}