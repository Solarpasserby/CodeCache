#include <iostream>

using namespace std;

int sc[55][55], dp[55][55][55], m, n;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> n;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            cin >> sc[i][j];

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k < i + j; k++)
            {
                if (j == k) dp[i][j][k] = sc[i][j] + max(dp[i-1][j][k-1], dp[i][j-1][k]);
                else dp[i][j][k] = sc[i][j] + sc[i + j - k][k] + max(max(dp[i-1][j][k-1], dp[i-1][j][k]), max(dp[i][j-1][k-1], dp[i][j-1][k]));
            }

    cout << dp[m][n][n] << '\n';

    return 0;
}