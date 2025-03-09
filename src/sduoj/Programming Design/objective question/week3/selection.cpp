#include<bits/stdc++.h>

using namespace std;

int n, k;
int num[30];
int ans;

bool checkPrime(int m)
{
    if (m == 1) return false;
    else if (m == 2) return true;
    else if (m % 2 == 0) return false;
    else
    {
        int tmp = ceil(sqrt(m));
        for(int i = 3; i < tmp; i += 2)
            if (m % i == 0) return false;
    }

    return true;
}

void dfs(const int &depth, const int &loc, const int &res)
{
    if (depth > k)
    {
        if (checkPrime(res)) ++ans;
        return;
    }

    if (loc > n)
        return;

    dfs(depth, loc + 1, res);
    dfs(depth + 1, loc + 1, res + num[loc]);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> n >> k;
    for(int i = 1; i <= n; i++)
        cin >> num[i];

    dfs(1, 1, 0);

    cout << ans << '\n';

    return 0;
}