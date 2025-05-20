#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

ll n, v;
ll w[50], c[50];
vector<pair<ll, ll>> subset_1, subset_2;
vector<pair<ll, ll>> newSubset_1, newSubset_2;

void generateSubset_1(int pos)
{
    static ll nw = 0, nc = 0;
    if(nw > v) return;
    if(pos > n/2) { subset_1.emplace_back(nw, -nc); return; }
    generateSubset_1(pos + 1);
    nw += w[pos], nc += c[pos];
    generateSubset_1(pos + 1);
    nw -= w[pos], nc -= c[pos];
}

void generateSubset_2(int pos)
{
    static ll nw = 0, nc = 0;
    if(nw > v) return;
    if(pos > n) { subset_2.emplace_back(nw, -nc); return; }
    generateSubset_2(pos + 1);
    nw += w[pos], nc += c[pos];
    generateSubset_2(pos + 1);
    nw -= w[pos], nc -= c[pos];
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> n >> v;
    for(int i = 1; i <= n; ++i)
        cin >> w[i] >> c[i];
    generateSubset_1(1);
    generateSubset_2(n/2+1);
    sort(subset_1.begin(), subset_1.end());
    sort(subset_2.begin(), subset_2.end());
    ll mv_1, mv_2;
    mv_1 = mv_2 = 1;
    for(auto [a, b]: subset_1)
        if(b < mv_1) { newSubset_1.emplace_back(a, b); mv_1 = b; }
    for(auto [a, b]: subset_2)
        if(b < mv_2) { newSubset_2.emplace_back(a, b); mv_2 = b; }

    ll ans = 1;
    for(auto [a, b]: newSubset_2)
    {
        auto it = lower_bound(newSubset_1.begin(), newSubset_1.end(), make_pair(v - a, 0), [](const pair<ll, ll>& p1, const pair<ll, ll>& p2) {
            return p1.first <= p2.first;
        });
        if(it == newSubset_1.begin()) ans = min(ans, b);
        else ans = min(ans, b + (it-1)->second);
    }

    cout << -ans << '\n';

    return 0;
}