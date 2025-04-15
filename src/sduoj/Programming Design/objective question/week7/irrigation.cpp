#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1e5 + 5;

int n, m, p;

struct Union
{
    int f[N];
    int rb;

    Union()
    {
        for(int i = 0; i <= N; ++i) f[i] = i;
        rb = 0;
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
            return rb;
        }
        return -1;
    }
};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m >> p;

    ll cost = 0;
    Union un;
    vector<tuple<int, int, int>> edge;

    while(m--)
    {
        int x, y, z;
        cin >> x >> y >> z;
        edge.push_back({x, y, z});
    }
    for(int i = 1; i <= n; ++i) edge.push_back({0, i, p});
    sort(edge.begin(), edge.end(), [](const auto& a, const auto& b) {
        return get<2>(a) < get<2>(b);
    });

    for(auto& t : edge)
    {
        if(un.rb >= n) break;
        int x, y, z;
        tie(x, y, z) = t;
        int t_res = un.join(x, y);
        if(t_res == -1) continue;
        else cost += z;
    }

    cout << cost << '\n';
    return 0;
}