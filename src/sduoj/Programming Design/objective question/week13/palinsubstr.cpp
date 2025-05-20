#include <bits/stdc++.h>

using namespace std;

string s;

int dp[4005][4005];

int func(int l, int r)
{
    if(l == r) return 1;
    else if(l > r) return 0;
    if(dp[l][r] != 0) return dp[l][r];
    if(s[l] == s[r]) return dp[l][r] = func(l+1, r-1) + 2;
    else return dp[l][r] = max(func(l+1, r), func(l, r-1));
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> s;
    s.insert(0, 1, '#');
    cout << func(1, s.size()-1) << '\n';
        
    return 0;
}