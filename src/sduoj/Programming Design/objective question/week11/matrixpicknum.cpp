#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1e6;

ll data[N][3];
ll dp[N][3];

ll func(int id, int t)
{
    return min(min(abs(data[id][t] - data[id-1][0]) + dp[id-1][0], abs(data[id][t] - data[id-1][1]) + dp[id-1][1]), abs(data[id][t] - data[id-1][2]) + dp[id-1][2]);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int m;
    cin >> m;
    for(int j = 0; j <= 2; ++j)
        for(int i = 1; i <= m; ++i)
            cin >> data[i][j];

    for(int i = 2; i <= m; ++i)
    {
        dp[i][0] = func(i, 0);
        dp[i][1] = func(i, 1);
        dp[i][2] = func(i, 2);
    }

    cout << min(min(dp[m][0], dp[m][1]), dp[m][2]) << '\n';

    return 0;
}