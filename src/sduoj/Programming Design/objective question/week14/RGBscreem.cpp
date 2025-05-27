#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll mod = 998244353;
const ll inv4 = 748683265;

ll func(ll t)
{
    if(t == 0) return 1;
    if(t == 1) return 3;
    ll tmp = func(t/2);
    if(t & 1) return tmp * tmp * 3 % mod;
    else return tmp * tmp % mod;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n;
    cin >> n;
    while(n--)
    {
        ll a;
        cin >> a;
        if(a & 1) cout << (func(a) + 1) % mod * inv4 % mod << '\n';
        else cout << (func(a) + 3) % mod * inv4 % mod << '\n';
    }

    return 0;
}
