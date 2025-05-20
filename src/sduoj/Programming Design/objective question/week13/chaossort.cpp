#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, d;
ll dp[65600][18];
int data[18];
vector<vector<int>> g;

void init()
{
    g.resize(n+1);
    for(int i = 0; i < (1 << n); ++i) {
        int t = 0;
        for(int j = 1; j <= i; j <<= 1)
            if(i & j) ++t;
        if(t != 0) g[t].push_back(i);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> n >> d;
    for(int i = 1; i <= n; ++i) cin >> data[i];

    init();
    for(int len = 1; len <= n; ++len)
        for(int i: g[len])
            for(int j = 1; j <= n; ++j) { //数字序号
                if(!(i&(1<<(j-1)))) continue;
                if(len == 1) { dp[i][j] = 1; break; }
                int u = i^(1<<(j-1));
                for(int k = 1; k <= n; ++k)
                    if(u&(1<<(k-1)) && abs(data[k]-data[j])>d) dp[i][j] += dp[u][k];
            }

    ll ans = 0;
    for(int i = 1; i <= n; ++i) ans += dp[(1<<n)-1][i];
    cout << ans << '\n';

    return 0;
}

/**
 * dp[65600][18] 希望使用第一维表示选择情况，第二维表示以该序号数字结尾，存储总数
 * dp[i][j]
 * 
 * dp[i][j] = sum(dp[u][v]) 其中u=i^(1<<(j-1))&&u&(1<<(v-1))&&abs(v-j)>k
 */