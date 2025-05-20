#include<bits/stdc++.h>

using namespace std;

int n, v;
int w[10005], c[10005], m[10005];
int new_w[100005], new_c[100005];
long long dp[10005];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> n >> v;
    for(int i = 1; i <= n; ++i)
        cin >> w[i] >> c[i] >> m[i];

    int new_n = 0;
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= m[i]; j <<= 1)
        {
            new_w[++new_n] = j * w[i];
            new_c[new_n] = j * c[i];
            m[i] -= j;
        }
        if(m[i])
        {
            new_w[++new_n] = m[i] * w[i];
            new_c[new_n] =m[i] * c[i];
        }
    }

    for(int i = 1; i <= new_n; ++i)
        for(int j = v; j >= new_w[i]; --j)
            dp[j] = max(dp[j], dp[j-new_w[i]]+new_c[i]);
    cout << dp[v] << '\n';

    return 0;
}