#include<bits/stdc++.h>

using namespace std;

int r, g, y, n;

void func(int u, int v, int& num)
{
    if(u == 2) num += v + r;
    else if(u == 1) num += v;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> r >> y >> g >> n;
    int ans = 0;
    while(n--)
    {
        int x, y;
        cin >> x >> y;
        if(x == 0) ans += y;
        else func(x, y, ans);
    }

    cout << ans << '\n';

    return 0;
}