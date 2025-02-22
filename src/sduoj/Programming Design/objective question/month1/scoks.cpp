#include<iostream>

using namespace std;

int socks[1005];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n, k, ans = 0;
    cin >> n >> k;

    for (;n--;)
    {
        int tmp;
        cin >> tmp;
        ++socks[tmp];
    }

    for (int i = 1; i <= k; i++)
    {
        while (socks[i] > 1)
        {
            socks[i] -= 2;
            ans += 1;
        }
    }

    cout << ans << '\n';

    return 0;
}