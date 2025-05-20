#include<bits/stdc++.h>

using namespace std;

const int N = 5005;

int n, m;
int A[N], B[N];
int dp[N][N];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> n >> m;
    for(int i = 1; i <= n; ++i) cin >> A[i];
    for(int i = 1; i <= m; ++i) cin >> B[i];

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j)
        {
            if(A[i] == B[j]) dp[i][j] = dp[i-1][j-1] + 1;
            else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }

    cout << dp[n][m] << '\n';

    return 0;
}