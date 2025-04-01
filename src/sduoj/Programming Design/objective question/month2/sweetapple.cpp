#include<bits/stdc++.h>

using namespace std;

int apple[1000005];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n, cnt = 0;
    cin >> n;
    for(int i = 1; i <= n; ++i)
    {
        cin >> apple[i];
        apple[i] += apple[i - 1];
    }

    for(int i = 1; i < n; ++i)
        if(apple[i] == apple[n] - apple[i]) ++cnt;

    cout << cnt << '\n';

    return 0;
}