#include<bits/stdc++.h>

using namespace std;

const int N =  1005;
const int MAX = 1e7;

int n, m;
vector<vector<pair<int, int>>> e;

int spfa()
{
    int dis[N], cnt[N], visit[N];
    queue<int> q;
    fill(dis, dis + N, MAX);
    memset(cnt, 0, sizeof(cnt));
    memset(visit, 0, sizeof(visit));

    q.push(dis[0] = 0);
    cnt[0] = 1;
    while(!q.empty())
    {
        int t = q.front();
        q.pop();
        visit[t] = 0;
        for(auto& [a, b]: e[t])
            if(dis[a] > dis[t] + b)
            {
                if(++cnt[a] > n) return -1;
                dis[a] = dis[t] + b;
                if(visit[a] == 0)
                {
                    visit[a] = 1;
                    q.push(a);
                }
            }
    }

    return dis[n];
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int res;
    cin >> n >> m;
    e.resize(n + 1);
    for(int i = 0; i < n; ++i)
    {
        e[i].emplace_back(i + 1, 1);
        e[i + 1].emplace_back(i, 0);
    }
    while(m--)
    {
        int k, a, b, c;
        cin >> k >> a >> b >> c;
        a--;
        switch (k)
        {
        case 1:
            e[a].emplace_back(b, c);
            break;

        case 2:
            e[b].emplace_back(a, -c);
            break;

        case 3:
            e[a].emplace_back(b, c - 1);
            break;

        case 4:
            e[b].emplace_back(a, -(c + 1));
            break;

        case 5:
            e[a].emplace_back(b, c);
            e[b].emplace_back(a, -c);
            break;
        
        default:
            break;
        }
    }

    res = spfa();
    if (res == -1 || res == MAX) cout << "impossible\n";
    else cout << res << "\n";
    return 0;
}