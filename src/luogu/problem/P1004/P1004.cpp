#include <iostream>

using namespace std;

typedef long long ll;

#define N 11

int sc[N][N], dp[N][N][N][N], n, x, y, v;

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
            for (int k = 1; k <= n; k++)
                for (int g = 1; g <= n; g++)
                {
                    dp[i][j][k][g] = max(max(dp[i-1][j][k-1][g], dp[i-1][j][k][g-1]), max(dp[i][j-1][k-1][g], dp[i][j-1][k][g-1])) + sc[i][j];
                    if (i != k && j != g)
                        dp[i][j][k][g] += sc[k][g];
                }

    cout << dp[n][n][n][n] << '\n';
    return 0;
}