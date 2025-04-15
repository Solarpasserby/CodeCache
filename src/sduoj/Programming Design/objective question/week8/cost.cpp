#include<bits/stdc++.h>

using namespace std;

void dijkstra(const vector<vector<pair<int, int>>> &e, vector<int> &cost)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.emplace(cost[1] = 0, 1);
    while(!pq.empty())
    {
        pair<int, int> tmp = pq.top();
        pq.pop();
        if(tmp.first > cost[tmp.second]) continue;
        for(const auto &a: e[tmp.second])
            if(cost[a.first] > tmp.first + a.second)
                pq.emplace(cost[a.first] = tmp.first + a.second, a.first);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--)
    {
        int n, m, sum = 0;
        cin >> n >> m;
        vector<vector<pair<int, int>>> e(n + 1), re(n + 1);
        vector<int> cost_a(n + 1, 1e9), cost_b(n + 1, 1e9);
        while(m--)
        {
            int a, b, c;
            cin >> a >> b >> c;
            e[a].emplace_back(b, c);
            re[b].emplace_back(a, c);
        }
        dijkstra(e, cost_a);
        dijkstra(re, cost_b);
        for(int i = 1; i <= n; ++i) sum += cost_a[i] + cost_b[i];
        cout << sum << '\n';
    }

    return 0;
}