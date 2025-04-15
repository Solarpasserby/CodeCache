#include<bits/stdc++.h>

using namespace std;

pair<int, int> pa[2005];
pair<int, int> pb[2005];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i)
        cin >> pa[i].first >> pa[i].second;
    for(int i = 1; i <= n; ++i)
        cin >> pb[i].first >> pb[i].second;

    long long ans = 0;
    for(int i = 1, j = 1; i <= n && j <= n;)
    {
        for(; pa[i].first >= pb[j].second && j <= n; ++j);
        if(j > n) break;
        ans += max(0, min(pa[i].second, pb[j].second) - max(pa[i].first, pb[j].first));
        if(pa[i].second > pb[j].second) ++j;
        else ++i;
    }

    cout << ans << '\n';

    return 0;
}