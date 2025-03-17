#include<bits/stdc++.h>

using namespace std;

struct cmp
{
    bool operator()(pair<int, int> a, pair<int, int> b)
    {
        return (a.first * 1.0 / a.second) < (b.first * 1.0 / b.second);
    }
};

priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> q;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    while(n--)
    {
        int tmp;
        cin >> tmp;
        q.push(pair<int, int>(tmp, 1));
    }

    while(k-- > 1)
    {
        pair<int, int> tmp;
        tmp = q.top();
        tmp.second += 1;
        q.push(tmp);
        q.pop();
    }

    cout << q.top().first * 1.0 / q.top().second << '\n';

    return 0;
}