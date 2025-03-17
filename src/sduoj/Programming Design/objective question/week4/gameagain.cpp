#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

ll num[100005];

int main()
{
    int n, cnt;
    ll k;
    cin >> n >> k;

    for(int i = 0; i < n; ++i)
        cin >> num[i];

    sort(num, num + n);

    cnt = 0;
    for(int i = n - 1; i > 0; --i)
        if (num[i] - num[i - 1] <= k) ++cnt;

    cout << cnt << '\n';

    return 0;
}