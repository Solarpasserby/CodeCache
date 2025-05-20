#include <bits/stdc++.h>

using namespace std;

int n;
int dp[105][105];
string s;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> s;
    n = s.size();
    s.insert(0, 1, '#');

    for(int i = 1; i <= n; ++i)
        for(int j = i; j <= n; ++j)
            if(i == j) dp[i][j] = 1;
            else dp[i][j] = INT32_MAX;
    
    for(int len = 2; len <= n; ++len)
        for(int i = 1; i + len - 1 <= n; ++i) {
            int r = i + len - 1;
            if(s[i] == '[' && s[r] == ']' || s[i] == '(' && s[r] == ')') dp[i][r] = dp[i+1][r-1];
            for(int j = i; j < r; ++j) dp[i][r] = min(dp[i][r], dp[i][j] + dp[j+1][r]);
        }

    cout << dp[1][n] << '\n';

    return 0;
}