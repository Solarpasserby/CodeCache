#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
    ll n, t;
    int x, y, m, timer;
    cin >> n >> x >> y;

    t = min(x, y);
    if (--n == 0)
    {
        cout << t << '\n';
        exit(0);
    }

    t += n / (x + y) * x * y; 
    n -= n / (x + y) * (x + y);

    timer = 0;
    while(n > 0)
    {
        timer++;
        if (timer % x == 0) --n;
        if (timer % y == 0) --n;
    }

    t += timer;
    cout << t << '\n';

    return 0;
}