#include<bits/stdc++.h>

using namespace std;

int n;

int bfs(int a, const vector<vector<int>> &v)
{
    int end;
    queue<int> q;
    vector<bool> ch(n + 1, false);

    q.push(a);
    ch[a] = true;
    while(!q.empty())
    {
        for(auto p: v[q.front()])
            if(!ch[p])
            {
                ch[p] = true;
                q.push(p);
            }
        end = q.front();
        q.pop();
    }

    return end;
}

void func(int a, int b, const vector<vector<int>> &v, vector<int> &ans)
{
    queue<int> q;
    vector<bool> ch(n + 1, false);
    vector<int> tmp(n + 1, 0);

    q.push(a);
    ch[a] = true;
    while(!q.empty())
    {
        for(auto p: v[q.front()])
        {
            int depth = tmp[q.front()];
            if(!ch[p])
            {
                ch[p] = true;
                tmp[p] = depth + 1;
                q.push(p);
            }
        }
        q.pop();
    }

    q.push(b);
    ch.assign(n + 1, false);
    ch[b] = true;
    while(!q.empty())
    {
        for(auto p: v[q.front()])
        {
            int depth = ans[q.front()];
            if(!ch[p])
            {
                ch[p] = true;
                ans[p] = depth + 1;
                q.push(p);
            }
        }
        q.pop();
    }

    for(int i = 1; i <= n; ++i) ans[i] = max(tmp[i], ans[i]);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> n;
    int t;
    vector<vector<int>> e(n + 1);
    vector<int> ans(n + 1, 0);

    for(int i = 1; i < n; ++i)
    {
        int x, y;
        cin >> x >> y;
        e[x].push_back(y);
        e[y].push_back(x);
    }

    t = bfs(1, e);
    func(t, bfs(t, e), e, ans);
    for(int i = 1; i <= n; ++i)
        cout << ans[i] << ' ';
    cout << '\n';

    return 0;
}