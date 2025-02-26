#include <iostream>

using namespace std;

int fb[30];

int func(int n)
{
    if (fb[n] != 0)
        return fb[n];
    else
    {
        if (n < 3)
            return (fb[n] = 1);
        else
            return (fb[n] = func(n - 1) + func(n - 2));
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int a, n, m, x, change, ans;
    cin >> a >> n >> m >> x;

    if (x < 3)
        cout << a << '\n';
    else
    {
        change = (m - func(n - 3) * a - a) / (func(n - 2) - 1);
        ans = (func(x - 2) + 1) * a + (func(x - 1) - 1) * change;
        cout << ans << '\n';
    }

    return 0;
}