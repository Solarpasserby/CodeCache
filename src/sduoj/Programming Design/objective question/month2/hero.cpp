#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 2e5 + 5;

int n;
ll a[N];

ll func(ll x)
{
    return ((1 + x) * x + (1 + a[n] - x) * (a[n] - x)) / 2;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> n;
    for(int i = 1; i <= n; ++i)
    {
        cin >> a[i];
        a[i] += a[i - 1];
    }

    int i = 1;
    for(; i <= n; ++i)
        if(a[i] > a[n] / 2) break;

    cout << min(func(a[i-1]), func(a[i])) << '\n';

    return 0;
}