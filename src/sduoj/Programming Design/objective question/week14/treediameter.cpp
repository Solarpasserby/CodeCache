#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 100005;

int n;
ll dep[N]; //深度
ll dp1[N]; //经过根
ll dp2[N]; //不经过根
ll dcnt[N]; //深度 计数
ll cnt1[N]; //经过根 计数
ll cnt2[N]; //不经过根 计数
vector<vector<int>> tree;

void dfs(int u, int v)
{
    if(dep[v]) return;
    if(tree[v].size() == 1 && tree[v].front() == u) {
        dep[v] = dcnt[v] = 1;
        return;
    }

    int tm = 0, tn = 0;
    for(int a: tree[v]) {
        if(a == u) continue;
        dfs(v, a);
        if(tm < dep[a]) { tm = dep[a], tn = a; }
    }

    dep[v] = tm+1, dcnt[v] = dcnt[tn];

    for(int a: tree[v]) {
        if(a == u) continue;
        if(dp1[a] > dp2[v]) {
            dp2[v] = dp1[a];
            cnt2[v] = cnt1[a];
        } else if(dp1[a] == dp2[v]) cnt2[v] += cnt1[a];
        if(dp2[a] > dp2[v]) {
            dp2[v] = dp2[a];
            cnt2[v] = cnt2[a];
        } else if(dp2[a] == dp2[v]) cnt2[v] += cnt2[a];

        if(a == tn) continue;
        if(tm+dep[a]+1 > dp1[v]) {
            dp1[v] = tm+dep[a]+1;
            cnt1[v] = dcnt[v]*dcnt[a];
        } else if(tm+dep[a]+1 == dp1[v]) {
            cnt1[v] += dcnt[v]*dcnt[a];
        }
        if(tm == dep[a]) dcnt[v] += dcnt[a];
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> n;
    tree.resize(n+1);
    for(int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    dfs(0, 1);
    if(dep[1] > dp1[1] && dep[1] > dp2[1]) cout << dep[1]-1 << ' ' << dcnt[1] << '\n';
    else if(dp1[1] > dep[1] && dp1[1] > dp2[1]) cout << dp1[1]-1 << ' ' << cnt1[1] << '\n';
    else cout << dp2[1]-1 << ' ' << cnt2[1] << '\n';

    return 0;
}
