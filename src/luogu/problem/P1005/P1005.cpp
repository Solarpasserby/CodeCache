#include <iostream>
#include <cmath>

using namespace std;

typedef unsigned long long ll;

#define N 90

bool fb[N][N];
ll fc[N][N], ans = 0;
int a[N], n, m;

ll func(int l, int r)
{
    int p = m - r + l;

    if (!fb[l][r])
    {
        fc[loc(l, r)] = max(2 * (a[l] + func(l+1, r)), 2 * (a[r] + func(l, r-1)));
        fb[loc(l, r)] = true;
    }

    return fc[loc(l, r)];
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j <= m; j++)
            cin >> a[j];

        for (int i = 1; i < N; i++)
            for (int j = 1; j < N; j++)
                fb[i][j] = false;

        ans += func(1, m);
    }

    cout << ans << '\n';
    return 0;
}