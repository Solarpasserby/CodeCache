#include <iostream>
#include <cmath>

using namespace std;

// typedef unsigned long long ll;
typedef __uint128_t ll;

#define N 90

bool fb[N][N];
ll fc[N][N], ans = 0;
int a[N], n, m;

void write(ll num)
{
    if (num >= 10) write(num / 10);
    putchar(num % 10 + '0');
}

ll func(int l, int r)
{
    int p = m - r + l;

    if (!fb[l][r])
    {
        fc[l][r] = 2 * max(a[l] + func(l+1, r), a[r] + func(l, r-1));
        fb[l][r] = true;
    }

    return fc[l][r];
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
            {
                if (i != j) fb[i][j] = false;
                else
                {
                    fc[i][i] = 2 * a[i];
                    fb[i][i] = true;
                }
            }

        ans += func(1, m);
    }

    write(ans);
    return 0;
}