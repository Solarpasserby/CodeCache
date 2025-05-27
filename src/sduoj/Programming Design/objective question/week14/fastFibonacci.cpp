#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll mod;

struct Matrix
{
    ll a1, a2, b1, b2;
    Matrix(ll _a1=0, ll _a2=0, ll _b1=0, ll _b2=0) :
        a1(_a1), a2(_a2), b1(_b1), b2(_b2) {}
    
    Matrix operator*(const Matrix& other) const
    {
        return {
            (other.a1 * a1 + other.b1 * a2) % mod,
            (other.a1 * b1 + other.b1 * b2) % mod,
            (other.a2 * a1 + other.b2 * a2) % mod,
            (other.a2 * b1 + other.b2 * b2) % mod
        };
    }
};

Matrix func(ll t)
{
    static Matrix E = {1, 1, 1, 0};
    if(t <= 1) return E;
    Matrix tmp = func(t/2);
    if(t & 1) return tmp * tmp * E;
    else return tmp * tmp;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n;
    ll tms;
    cin >> n;
    while(n--) {
        cin >> tms >> mod;
        cout << func(tms-1).a1 << '\n';
    }

    return 0;
}
