#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n;
    ll h, f;
    cin >> n >> h >> f;
    for(int i = 1; i <= n; ++i)
    {
        ll tmp;
        cin >> tmp;
        h -= max(static_cast<ll>(0), tmp - f);
        f = max(tmp, f);
        if(h <= 0)
        {
            cout << "NO\n" << i - 1 << '\n';
            exit(0);
        }
    }

    cout << "YES\n" << h << '\n';

    return 0;
}