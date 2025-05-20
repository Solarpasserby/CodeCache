#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1e6+5;
const ll MOD = 998244353;

ll dp[N];
ll sum[N];
bool unsafe[N];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    while(m--)
    {
        int tmp;
        cin >> tmp;
        unsafe[tmp] = true;
    }

    sum[0] = dp[0] = 1;
    for(int i = 1; i <= n; ++i)
    {
        ll tmp = i - k - 1 < 0 ? 0 : sum[i - k - 1];
        if(!unsafe[i]) dp[i] = (sum[i - 1] - tmp) % MOD;
        sum[i] = dp[i] + sum[i - 1];
    }
    
    cout << dp[n] << '\n';

    return 0;
}