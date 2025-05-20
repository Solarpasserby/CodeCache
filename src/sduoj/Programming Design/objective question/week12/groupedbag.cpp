#include<bits/stdc++.h>

using namespace std;

int n, v;
vector<vector<int>> w, c;
int dp[1005];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> n >> v;
    w.resize(n+1), c.resize(n+1);
    int mz = 0;
    for(int i = 1; i <= n; ++i)
    {
        int x, y, z;
        cin >> x >> y >> z;
        if(z > n && z > mz) {w.resize(z+1); c.resize(z+1);}
        w[z].push_back(x);
        c[z].push_back(y);
        mz = max(mz, z);
    }
    w.resize(mz+1), c.resize(mz+1);

    for(int i = 1; i <= mz; ++i)
        for(int j = v; j >= 0; --j)
            for(int k = 0; k < w[i].size(); ++k)
                if(w[i][k] <= j) dp[j] = max(dp[j], dp[j-w[i][k]]+c[i][k]);
    cout << dp[v] << '\n'; 

    return 0;
}