#include<bits/stdc++.h>

using namespace std;

int n, k, kids[1100];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> n >> k;
    for(int i = 1; i <= n; i++)
        kids[i] = i;

    int i = 0, cnt = 1, m = n;
    while(true)
    {
        int loc = i % n + 1;

        if (kids[loc] != 0)
        {
            if (cnt % k == 0 || cnt % 10 == k)
            {
                if (m == 1)
                {
                    cout << loc << '\n';
                    break;
                }
                
                kids[loc] = 0;
                --m;
            }

            ++cnt;
        }

        ++i;
    }

    return 0;
}