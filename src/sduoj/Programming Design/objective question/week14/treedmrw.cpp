#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5+5;

int n;
ll dp[N], cnt[N];
ll ans, num;
vector<vector<int>> g;

void dfs(int u, int v)
{
    for(int a: g[v]) {
        if(a == u) continue;
        dfs(v, a);
        int t = dp[a] + 1;
        if(dp[v]+t>ans) {
            ans = dp[v]+t;
            num = cnt[v]*cnt[a];
        } else if(dp[v]+t==ans) {
            num += cnt[v]*cnt[a];
        }

        if(t > dp[v]) {
            dp[v] = t;
            cnt[v] = cnt[a];
        } else if(t == dp[v]) {
            cnt[v] += cnt[a];
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> n;
    cnt[1] = 1, ans = 0;
    g.resize(n+1);
    for(int i = 2; i <= n; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
        cnt[i] = 1;
    }
    dfs(0, 1);
    cout << ans << ' ' << num << '\n';

    return 0;
}