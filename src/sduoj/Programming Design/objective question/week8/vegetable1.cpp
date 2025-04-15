#include<bits/stdc++.h>

using namespace std;

int v[1005];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i)
        cin >> v[i];
    v[0] = (v[1] + v[2]) / 2;
    v[n + 1] = (v[n - 1] + v[n]) / 2;

    for(int i = 1; i <= n; ++i)
        cout << (v[i - 1] + v[i] + v[i + 1]) / 3 << ' ';
    cout << '\n';

    return 0;
}