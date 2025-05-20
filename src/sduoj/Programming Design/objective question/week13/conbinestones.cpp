#include<bits/stdc++.h>

using namespace std;

int n;
int sum[105];
int dp[105][105];
int dpb[105][105];

int func(int l, int r)
{
    if(l <= r) return sum[r] - sum[l-1];
    else return sum[n] - sum[l-1] + sum[r];
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> n;
    for(int i = 1; i <= n; ++i)
    {
        cin >> sum[i];
        sum[i] += sum[i-1];
    }
    
    for(int i = 1; i < n; ++i)
        for(int j = 1; j <= n; ++j)
        {
            int r = (j+i-1)%n+1;
            for(int k = 0; k < i; ++k)
            {
                int l = (j+k-1)%n+1, m = (j+k)%n+1;
                dp[j][r] = max(dp[j][r], dp[j][l]+dp[m][r]);
                if(dpb[j][r] == 0) dpb[j][r] = dpb[j][l]+dpb[m][r];
                else dpb[j][r] = min(dpb[j][r], dpb[j][l]+dpb[m][r]);
            }
            dp[j][r] += func(j, r);
            dpb[j][r] += func(j, r);
        }

    int ansa = 0, ansb = INT32_MAX;
    for(int i = 1; i <= n; ++i)
    {
        int r = (i+n-2)%n+1;
        ansa = max(ansa, dp[i][r]);
        ansb = min(ansb, dpb[i][r]);
    }
    cout << ansb << '\n';
    cout << ansa << '\n';

    return 0;
}