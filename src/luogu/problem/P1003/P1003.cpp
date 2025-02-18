#include<iostream>

#define l 10005

using namespace std;

typedef long long ll;

int a[l], b[l], k[l], g[l];

int main()
{
    int n, x, y;
    bool ch = false;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int aa, bb, kk, gg;
        cin >> aa >> bb >> kk >> gg;
        a[i] = aa;
        b[i] = bb;
        k[i] = kk;
        g[i] = gg;
    }
    cin >> x >> y;

    for (int i = n - 1; i >= 0; i--)
    {
        if (x >= a[i] && y >= b[i] && x <= a[i] + k[i] && y <= b[i] + g[i])
        {
            ch = true;
            cout << i + 1 << '\n';
            break;
        }
    }

    if (!ch) cout << -1 << '\n';

    return 0;
}