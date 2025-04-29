#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e8;

int n, m;
vector<vector<tuple<int, int, int>>> g;

bool spfa(double num)
{
    vector<bool> inque(n + 1, false);
    vector<int> dis(n + 1, MAX);
    vector<int> cnt(n + 1, 0);
    queue<int> q;

    q.push(dis[0] = 0);
    while(!q.empty())
    {
        int t = q.front();
        q.pop();
        inque[t] = false;
        for(auto [a, b, c]: g[t])
        {
            int tmp = c * num - b;
            if(dis[a] > dis[t] + tmp)
            {
                if(++cnt[a] > n) return true;
                dis[a] = dis[t] + tmp;
                if(!inque[a])
                {
                    inque[a] = true;
                    q.push(a);
                }
            }
        }
    }

    return false;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> n >> m;
    g.resize(n + 1);
    while(m--)
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        g[a].emplace_back(b, c, d);
    }
    for(int i = 1; i <= n; ++i)
        g[0].emplace_back(i, 0, 0);
    
    double left = 0, right = 1000;
    for(int i = 0; i < 20; ++i)
    {
        double mid = left + (right - left) / 2;
        if(spfa(mid)) left = mid;
        else right = mid;
    }

    cout << fixed << setprecision(1) << right << '\n';

    return 0;
}