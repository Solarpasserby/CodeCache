#include<bits/stdc++.h>

using namespace std;

const int N = 500005;

int record[N][26] = {0};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n, m;
    string stone;
    cin >> n >> stone;
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 0; j < 26; j++)
            record[i][j] = record[i-1][j];
        ++record[i][stone[i - 1] - 'A'];
    }

    cin >> m;
    for(int i = 0; i < m; ++i)
    {
        int l, r, j = 0;
        cin >> l >> r;
        for(; j < 26; ++j)
            if (record[r][j] - record[l-1][j] < 1) break;
        if (j == 26) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}