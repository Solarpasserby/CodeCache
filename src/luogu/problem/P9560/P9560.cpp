#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

ll n, m, minPrice;
int k, a, b;

int main()
{
    int t;
    cin >> t;

    for(;t--;)
    {
        cin >> n >> k >> m >> a >> b;
        minPrice = 1e18;

        if(k == 1)
        {
            if(n % m == 0) cout << 0 << '\n';
            else cout << -1 << '\n';
            continue;
        }

        int i = 0;
        for(; n; ++i, n /= k)
        {
            if (i * b >= minPrice) break;

            if (n % m == 0)
            {
                if(i * b < minPrice)
                {
                    minPrice = i * b;
                    break;
                }
                else break;
            }

            int j = 0;
            ll l, r;
            l = r = n;
            while(l / m == r / m && l % m)
            {
                l *= k;
                r = r * k + k - 1;
                ++j;
            }

            if (i * b + j * a < minPrice)
            {
                minPrice = i * b + j * a;
                if (j * a <= b) break;
            }
        }

        if(i * b < minPrice) minPrice = i * b;

        cout << minPrice << '\n';
    }

    return 0;
}