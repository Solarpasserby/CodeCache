#include<bits/stdc++.h>

using namespace std;

int n, v;
int w[5005], c[5005];
int dp[5005];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> n >> v;
    for(int i = 1; i <= n; ++i)
        cin >> w[i] >> c[i];

    for(int i = 1; i <= n; ++i)
        for(int j = w[i]; j <= v; ++j)
            dp[j] = max(dp[j], dp[j-w[i]]+c[i]);
    cout << dp[v] << '\n';

    return 0;
}