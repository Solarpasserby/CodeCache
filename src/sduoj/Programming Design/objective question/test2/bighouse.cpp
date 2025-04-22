#include<bits/stdc++.h>

using namespace std;

const int IMAX = 1e7;

bool ing[205];
int t[205];
int dp[205][205];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            dp[i][j] = IMAX;
    for(int i = 0; i < n; ++i) cin >> t[i];
    for(int i = 0; i < m; ++i)
    {
        int x, y, z;
        cin >> x >> y >> z;
        dp[x][y] = dp[y][x] = z;
    }

    int query, k = 0;
    cin >> query;
    while(query--)
    {
        int x, y, z;
        cin >> x >> y >> z;

        for(; k < n && t[k] <= z; ++k)
        {
            for(int i = 0; i < n; ++i)
                for(int j = 0; j < n; ++j)
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
        }

        if (max(x, y) < k) cout << (dp[x][y] == IMAX ? -1 : dp[x][y]) << '\n';
        else cout << "-1\n";
    }

    return 0;
}