#include<bits/stdc++.h>

using namespace std;

#define ll long long
#define lowbit(x) ((x) & -(x))

const int N = 1e6+5;

int n;
int tree[N], ans[N];
ll sec[N];
unordered_map<ll, int> rk;

void update(int x, int val)
{
    while(x <= n)
    {
        tree[x] += val;
        x += lowbit(x);
    }
}

int sum(int x)
{
    int res = 0;
    while(x > 0)
    {
        res += tree[x];
        x -= lowbit(x);
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> n;
    vector<pair<ll, ll>> num(n + 1);
    for(int i = 1; i <= n; ++i)
    {
        cin >> num[i].first >> num[i].second;
        sec[i] = num[i].second;
    }
    sort(sec + 1, sec + n + 1);
    sort(num.begin() + 1, num.end());

    sec[0] = -1;
    for(int i = 1, j = 0; i <= n; ++i)
    {
        if(sec[i] == sec[i - 1]) continue;
        else rk[sec[i]] = ++j;
    }

    for(int i = 1; i <= n; ++i)
    {
        int id = rk[num[i].second];
        ++ans[sum(id)];
        update(id, 1);
    }

    for(int i = 0; i < n; ++i)
        cout << ans[i] << '\n';

    return 0;
}