#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int prime[25] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
const int N = 100005;
const int M = 1e9 + 7;

ll tree[N<<2][25];
ll tag[N<<2][25];

ll ls(ll p){return p<<1;}
ll rs(ll p){return p<<1|1;}

void push_up(ll p, ll c)
{
    tree[p][c] = min(tree[ls(p)][c], tree[rs(p)][c]);
}

void addtag(ll p, ll c, ll b)
{
    tag[p][c] += b;
    tree[p][c] += b;
}

void push_down(ll p, ll c)
{
    if(tag[p][c])
    {
        addtag(ls(p), c, tag[p][c]);
        addtag(rs(p), c, tag[p][c]);
        tag[p][c] = 0;
    }
}

void update(ll L, ll R, ll p, ll pl, ll pr, ll c, ll b)
{
    if(L <= pl && R >= pr)
    {
        addtag(p, c, b);
        return;
    }
    push_down(p, c);
    ll mid = (pl + pr)>>1;
    if(L <= mid) update(L, R, ls(p), pl, mid, c, b);
    if(R > mid) update(L, R, rs(p), mid + 1, pr, c, b);
    push_up(p, c);
}

long long binpow(ll a, ll b)
{
    a %= M;
    ll res = 1;
    while(b)
    {
        if(b & 1) res = res * a % M;
        a = a * a % M;
        b >>= 1;
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n, m;
    ll ans = 1;
    cin >> n >> m;

    while(m--)
    {
        int l, r;
        ll tc, tb;
        cin >> l >> r >> tc >> tb;
        for(int i = 0; i < 25; ++i)
        {
            int tmp = 0;
            while(tc % prime[i] == 0)
            {
                ++tmp;
                tc /= prime[i];
            }
            update(l, r, 1, 1, n, i, tmp * tb);

            if(tc == 1) break;
        }
    }

    for(int i = 0; i < 25; ++i)
        ans = ans * binpow(prime[i], tree[1][i]) % M;

    cout << ans << '\n';

    return 0;
}