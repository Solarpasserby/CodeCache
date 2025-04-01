#include<bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n, m, l, t1, t2;
    cin >> n;
    m = INT32_MIN;
    t2 = l = 1;
    while(n--)
    {
        cin >> t1;
        if(t1 > m)
        {
            m = t1;
            l = t2 = 1;
        }
        else if(t1 == m && ++t2 > l)
            l = t2;
        else if(t1 < m)
            t2 = 0;
    }

    cout << m << ' ' << l << '\n';

    return 0;
}