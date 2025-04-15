#include<bits/stdc++.h>

using namespace std;

int chain[200005];
int lst = 0;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int m, q;
    cin >> m >> q;
    while(q--)
    {
        char c;
        cin >> c;
        switch (c)
        {
        case 'M':
        {
            int a;
            cin >> a;
            chain[lst] = a;
            chain[a] = 0;
            lst = a;
            break;
        }

        case 'C':
        {
            int a, b, cnt = 0, pre = 0, n = chain[0];
            cin >> a >> b;
            while(n != 0)
            {
                if (n >= a && n <= b)
                {
                    ++cnt;
                    if (chain[n] == 0)
                        lst = pre;
                    chain[pre] = chain[n];
                }
                else
                    pre = chain[pre];

                n = chain[pre];
            }
            cout << cnt << '\n';
        }
            break;
        
        default:
            break;
        }
    }

    return 0;
}