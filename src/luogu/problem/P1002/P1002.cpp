#include<iostream>

using namespace std;

typedef long long ll;

const int dx[9] = {0, 1, 2, 2, 1, -1, -2, -2, -1};
const int dy[9] = {0, 2, 1, -1, -2, -2, -1, 1, 2};

ll dp[30][30] = {0};
bool isBlock[30][30] = {false};

int main()
{
    int bx, by, cx, cy;
    cin >> bx >> by >> cx >> cy;
    bx += 2, by += 2, cx += 2, cy += 2;
    dp[1][2] = 1;
    for (int i = 0; i < 9; i++)
        isBlock[cx + dx[i]][cy + dy[i]] = true;
    for (int i = 2; i <= bx; i++)
    {
        for (int j = 2; j <= by; j++)
        {
            if (isBlock[i][j])
            {
                dp[i][j] = 0;
                continue;
            }
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }
    cout << dp[bx][by] << '\n';
}