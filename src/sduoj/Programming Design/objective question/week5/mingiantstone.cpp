#include<bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n, l, cnt, ans, record[26] = {0};
    string stone;

    cin >> n >> stone;

    ans = 1114514;
    l = cnt = 0;
    for(int i = 0; i < n; ++i)
    {
        if(record[stone[i] - 'A'] == 0) ++cnt;
        ++record[stone[i] - 'A'];

        if(cnt == 26)
            ans = min(ans, i + 1 - l);

        while(i + 1 - l >= ans)
        {
            --record[stone[l] - 'A'];
            if(record[stone[l] - 'A'] == 0) --cnt;
            ++l;

            if(cnt == 26)
                ans = min(ans, i + 1 - l);
        }
    }

    cout << ans << '\n';

    return 0;
}