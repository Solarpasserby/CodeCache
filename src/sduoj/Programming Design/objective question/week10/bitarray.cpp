#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1e6 + 5;

ll data[N + 1];

struct Bit {
    int s;
    Bit(int _s)
    {
        assert(_s < N);
        s = _s;
        memset(data, 0, sizeof(data));
    }
    void add(int p, ll q) {
        for (; p <= s; p += p & -p) data[p] += q;
    }
    ll query(int p) {
        ll res = 0;
        for (; p; p -= p & -p)
            res += data[p];
        return res;
    }
    ll query(int l, int r) {
        return query(r) - query(l - 1);
    }
};


int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    Bit bit(n);
    for (int i = 1; i <= n; ++i) {
        int t;
        cin >> t;
        bit.add(i, t);
    }

    while(m--) {
        int u, v, w;
        cin >> u >> v >> w;
        if(u == 1) bit.add(v, w);
        else cout << bit.query(v, w) << '\n';
    }

    return 0;
}