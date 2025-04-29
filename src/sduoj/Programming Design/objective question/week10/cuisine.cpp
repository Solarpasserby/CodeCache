#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int m, p, cnt, tmp;
int tree[N], A[N];

int lowbit(int x) { return (x & -x); }

void update(int x, int val)
{
    A[x] = tree[x] = val;
    while(x <= cnt)
    {
        for(int i = 1; i < lowbit(x); i <<= 1)
            tree[x] = max(tree[x], tree[x - i]);
        x += lowbit(x);
    }
}

//实际上还没有搞懂为什么这么写
int query(int l, int r)
{
    int res = 0;
    while(l <= r)
    {
        res = max(res, A[r]);
        --r;
        while(r - l >= lowbit(r))
        {
            res = max(res, tree[r]);
            r -= lowbit(r);
        }
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> m >> p;
    cnt = tmp = 0;
    while(m--)
    {
        char c; int a;
        cin >> c >> a;
        if(c == 'A')
            update(++cnt, (tmp + a) % p);
        else
            cout << (tmp = query(cnt - a + 1, cnt)) << '\n';
    }

    return 0;
}