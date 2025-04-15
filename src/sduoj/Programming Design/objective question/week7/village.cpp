#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

struct Union
{
    int f[N];
    int rb;

    Union()
    {
        for(int i = 0; i < N; ++i) f[i] = i;
        rb = 1;
    }

    pair<int, int> find(int t)
    {
        int h = 1;
        for(; f[t] != t; ++h) t = f[t];
        return {t, h};
    }

    int join(int x, int y)
    {
        pair<int, int> t1, t2;
        t1 = find(x);
        t2 = find(y);
        if(t1.first != t2.first)
        {
            ++rb;
            if(t1.second > t2.second)
                f[t2.first] = t1.first;
            else
                f[t1.first] = t2.first;
        }
        return rb;
    }
};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int m, n;
    Union un;
    cin >> n >> m;
    while(m--)
    {
        int x, y;
        cin >> x >> y;
        cout << n - un.join(x, y) << '\n';
    }

    return 0;
}