#include<bits/stdc++.h>

using namespace std;

const int N = 1e6+5;

int cnt, dfn;
int low[N], num[N];
int sccno[N];
stack<int> stk;
vector<vector<int>> g;


void dfs(int u)
{
    stk.push(u);
    low[u] = num[u] = ++dfn;
    for(int i = 0; i < g[u].size(); ++i)
    {
        int v = g[u][i];
        if(!num[v])
        {
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
        else if(!sccno[v])
            low[u] = min(num[v], low[u]);
    }
    if(low[u] == num[u])
    {
        ++cnt;
        while(true)
        {
            int t = stk.top();
            stk.pop();
            sccno[t] = cnt;
            if(u == t) break;
        }
    }
}

void tarjan(int n)
{
    cnt = dfn = 0;
    memset(low, 0, sizeof(low));
    memset(num, 0, sizeof(num));
    memset(sccno, 0, sizeof(sccno));
    for(int i = 1; i <= n; ++i)
        if(!num[i]) dfs(i);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    g.resize(n + 1);
    while(m--)
    {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }

    tarjan(n);
    int ans = cnt;
    vector<int> cntSccno(cnt + 1, 0);
    for(int i = 1; i <= n; ++i)
        for(int j = 0; j < g[i].size(); ++j)
            if(sccno[i] != sccno[g[i][j]] && cntSccno[sccno[g[i][j]]]++ == 0) --ans;

    cout << ans << '\n';

    return 0;
}