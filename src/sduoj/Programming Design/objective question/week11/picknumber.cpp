#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1e6 + 5;

int cnt[N];
ll dp[N];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n, m, t;
    m = 0;
    t = 1145144;
    cin >> n;
    for(int i = 0; i < n; ++i)
    {
        int tmp;
        cin >> tmp;
        m = max(m, tmp);
        t = min(t, tmp);
        ++cnt[tmp];
    }

    dp[t] = t * cnt[t];
    for(int i = t + 1; i <= m; ++i)
        dp[i] = max(dp[i-1], dp[i-2] + cnt[i]*i);
    cout << dp[m] << '\n';

    return 0;
}