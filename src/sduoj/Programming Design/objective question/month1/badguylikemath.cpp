#include<iostream>
#include<cstdint>
#include<cmath>

using namespace std;

typedef long long ll;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    ll l, r, k, t, ans = 1;
    bool isExist = false;
    cin >> l >> r >> k;

    t = (int) log(INT64_MAX) / log(k) + 1;
    while(ans <= r && t--)
    {
        if (ans >= l)
        {
            if (!isExist)
            {
                isExist = true;
                cout << ans;
            }
            else
                cout << ' ' << ans;
        }

        ans *= k;
    }

    if (!isExist) cout << -1;
    cout << '\n';

    return 0;
}