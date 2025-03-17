#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

int price[100005];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int t, n, maxP, minP, cnt;
    ll profit = 0;
    cin >> t;
    while(t--)
    {
        cin >> n;
        for(int i = 1; i <= n; ++i)
            cin >> price[i];
        
        cnt = 0;
        profit = 0;
        maxP = minP = price[n];
        for(int i = n; i > 1; --i)
        {
            if (price[i] >= price[i - 1])
                minP = price[i - 1];
            else
            {
                if (maxP - minP != 0) cnt += 2;
                profit += maxP - minP;
                maxP = minP = price[i - 1];
            }
        }

        if (maxP - minP != 0) cnt += 2;
        profit += maxP - minP;

        cout << profit << ' ' <<  cnt << '\n';
    }

    return 0;
}