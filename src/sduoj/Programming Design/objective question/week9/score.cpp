#include<bits/stdc++.h>

using namespace std;

const int N = 1e6+5;

int cnt[N];
vector<vector<int>> e;
priority_queue<int, vector<int>, greater<>> pq;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int m, n;
    cin >> n >> m;
    e.resize(n);
    while(m--)
    {
        int a, b;
        cin >> a >> b;
        ++cnt[b];
        e[a].push_back(b);
    }

    for(int i = 1; i <= n; ++i) if(cnt[i] == 0) pq.push(i);

    while(!pq.empty())
    {
        int t = pq.top();
        pq.pop();
        cout << t << ' ';
        for(int a: e[t]) if(--cnt[a] == 0) pq.push(a);
    }
    cout << '\n';

    return 0;
}