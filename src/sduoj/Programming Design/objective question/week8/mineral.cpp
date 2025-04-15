#include<bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int tests;
    cin >> tests;
    while(tests--)
    {
        int n, m, t, maxEdge = 0;
        cin >> n >> m >> t;
        vector<vector<tuple<int, int, int>>> e(n + 1);
        vector<pair<int, int>> dis;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        while(m--)
        {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            e[a].emplace_back(b, c, d);
            e[b].emplace_back(a, c, d);
            maxEdge = max(maxEdge, c);
        }
        int right, left, mid;
        left = 0, right = maxEdge;
        while(left < right)
        {
            mid = (left + right + 1) >> 1;
            dis.assign(n + 1, {1e9, 0});
            pq.emplace(dis[1].first = 0, 1);
            while(!pq.empty())
            {
                int b = pq.top().first, d = pq.top().second;
                pq.pop();
                if(b > dis[d].first) continue;
                for(const auto &edge : e[d])
                {
                    int x = get<0>(edge), y = get<1>(edge), z = get<2>(edge);
                    if(dis[x].first > b + y && dis[d].second + z <= t && y >= mid)
                    {
                        pq.emplace(dis[x].first = b + y, x);
                        dis[x].second = dis[d].second + z;
                    }
                }
            }
            if(dis[n].first != 1e9) left = mid;
            else right = mid - 1;
        }
        cout << left << '\n';
    }

    return 0;
}