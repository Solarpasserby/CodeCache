#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e6+5;

int n, m;
ll sum[N];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> n >> m;
    for(int i = 1; i <= n; ++i) {
        cin >> sum[i];
        sum[i] += sum[i-1];
    }

    ll ans = 0;
    deque<int> dq;
    dq.push_back(0);
    for(int i = 1; i <= n; ++i) {
        ll t = sum[i];
        ans = max(ans, t - sum[dq.front()]);
        while(!dq.empty() && sum[dq.back()] > t) dq.pop_back();
        dq.push_back(i);
        while(dq.front()+m <= i) dq.pop_front();
    }
    cout << ans << '\n';

    return 0;
}
