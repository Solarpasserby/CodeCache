#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

int n, m;
int sta[100], cnt[100];
ll dp[11][100][100];

int init_line()
{
    int p = 0;
    for(int i = 0; i < (1 << n); ++i)
        if(i&(i>>1) || i&(i<<1)) continue;
        else {
            int t = 0;
            for(int j = 1; j <= i; j <<= 1)
                if(i & j) ++t;
            sta[++p] = i;
            cnt[p] = t;
        }

    return p;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> n >> m;
    int p = init_line();
    for(int i = 1 ; i <= n; ++i) //行数
        for(int j = 1; j <= m; ++j) //已落棋子
            for(int k = 1; k <= p; ++k) { //当前状态码
                if(cnt[k] > j) continue;
                int t = j - cnt[k];
                if(t < 1) { dp[i][j][k] += 1; continue; }
                for(int u = 1; u <= p; ++u) //上一行状态码
                    if(sta[k]&sta[u]||sta[k]&(sta[u]>>1)||sta[k]&(sta[u]<<1)) continue;
                    else dp[i][j][k] += dp[i-1][t][u];
            }

    ll ans = 0;
    for(int k = 1; k <= p; ++k) ans += dp[n][m][k];
    cout << ans << '\n';

    return 0;
}

/**
 * 脑子要没了...
 * dp[1][1][001] = dp[1][1][010] = dp[1][1][100] = 1
 * dp[1][2][101] = 1;
 * 
 * dp[2][1][000] += sum(dp[1][1]) -> 3
 * dp[2][1][001] = dp[2][1][010] = dp[2][1][100] = 1
 * dp[2][2][000] += dp[1][2][101] -> 1
 * dp[2][2][100] += dp[1][1][001] -> 1
 * dp[2][2][001] += dp[1][1][100] -> 1
 * dp[2][2][101] = 1
 * 
 * dp[3][1][000] += sum(dp[2][1]) = 6
 * dp[3][1][001] = dp[3][1][010] = dp[3][1][100] = 1
 * dp[3][2][000] += sum(dp[2][2]) -> 4
 * dp[3][2][001] += dp[2][1][000] + dp[2][1][100] -> 4
 * dp[3][2][010] += dp[2][1][000] -> 3
 * dp[3][2][001] += dp[2][1][000] + dp[2][1][100] -> 4
 * dp[3][2][101] = 1
 * 
 * dp[i][j][k] += dp[i-1][j-cnt(k)][u]
 * 
 * 计算所有k个情况，k由二进制数，变为状态编号
 */