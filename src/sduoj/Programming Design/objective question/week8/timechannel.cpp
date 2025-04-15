#include<bits/stdc++.h>

using namespace std;

bool spfa(const vector<vector<pair<int, int>>> &e, int n)
{
    queue<int> q;
    vector<bool> inq(n + 1, false);
    vector<int> cnt(n + 1, 0);
    vector<int> dis(n + 1, 1e9);
    q.push(0);
    dis[0] = 0;

    while(!q.empty())
    {
        int tmp = q.front();
        q.pop();
        inq[tmp] = false;
        for(auto a: e[tmp])
        {
            if(dis[a.first] > dis[tmp] + a.second)
            {
                dis[a.first] = dis[tmp] + a.second;
                if(!inq[a.first])
                {
                    inq[a.first] = true;
                    q.push(a.first);
                }
                if(++cnt[a.first] > n) return true;
            }
        }
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int times;
    cin >> times;
    while(times--)
    {
        int n, m, w;
        cin >> n >> m >> w;
        vector<vector<pair<int, int>>> e(n + 1);
        while(m--)
        {
            int a, b, c;
            cin >> a >> b >> c;
            e[a].emplace_back(b, c);
            e[b].emplace_back(a, c);
        }
        while(w--)
        {
            int a, b, c;
            cin >> a >> b >> c;
            e[a].emplace_back(b, -c);
        }
        for(int i = 1; i <= n; ++i) e[0].emplace_back(n, 0);

        if(spfa(e, n)) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}