#include <iostream>

using namespace std;

#define N 11

// x1, y1, x2, (y2 = x1 + y1 - x2)
int sc[N][N], dp[N][N][N], n, x, y, v;

int main()
{
    cin >> n;
    for(;;)
    {
        cin >> x >> y >> v;
        if (!(x || y || v))
            break;
        sc[x][y] = v;
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k < i + j; k++)
            {
                dp[i][j][k] = sc[i][j] + sc[k][i + j - k] + max(max(dp[i-1][j][k-1], dp[i-1][j][k]), max(dp[i][j-1][k-1], dp[i][j-1][k]));
                if (i == k)
                    dp[i][j][k] -= sc[i][j];
            }

    cout << dp[n][n][n] << '\n';

    return 0;
}