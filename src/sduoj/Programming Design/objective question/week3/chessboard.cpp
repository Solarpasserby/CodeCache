#include <bits/stdc++.h>

using namespace std;

int n, k, ans;
vector<pair<int, int>> board;
vector<int> x, y;

bool check(pair<int, int> p)
{
    for (int v : x)
        if (v == p.first)
            return false;
    for (int v : y)
        if (v == p.second)
            return false;

    return true;
}

void dfs(const int &cnt, const vector<pair<int, int>>::const_iterator &it)
{
    if (cnt > k)
    {
        ans++;
        return;
    }

    if (it == board.end())
        return;

    if (check(*it))
    {
        x.push_back(it->first);
        y.push_back(it->second);
        dfs(cnt + 1, it + 1);
        x.pop_back();
        y.pop_back();
    }

    dfs(cnt, it + 1);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    while (true)
    {
        cin >> n >> k;
        if (n == -1)
            break;

        ans = 0;
        board.reserve(100);
        board.clear();

        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                char c;
                pair<int, int> tmp(i, j);
                cin >> c;
                if (c == '#')
                    board.push_back(tmp);
            }

        auto it = board.begin();
        dfs(1, it);

        cout << ans << '\n';
    }

    return 0;
}