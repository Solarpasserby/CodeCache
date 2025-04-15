#include<bits/stdc++.h>

using namespace std;

pair<int, int> point[1005];

int main()
{
    int n, x, y, r, cnt = 0;
    cin >> n;

    for(int i = 1; i <= n; ++i)
    {
        cin >> point[i].first >> point[i].second;
    }
    cin >> x >> y >> r;

    for(int i = 1; i <= n; ++i)
    {
        if(pow(point[i].first - x, 2) + pow(point[i].second - y, 2) <= pow(r, 2)) ++cnt;
    }

    cout << cnt << '\n';

    return 0;
}