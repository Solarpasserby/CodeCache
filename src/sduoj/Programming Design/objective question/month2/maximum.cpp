#include<bits/stdc++.h>

using namespace std;

int mtx[505][505];
bool ans[505][505];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n, m, cnt = 0;
    cin >> n >> m;

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j)
        {
            cin >> mtx[i][j];
            if(j > 1)
            {
                if(mtx[i][j] >= mtx[i][j - 1]) ans[i][j - 1] = true;
                if(mtx[i][j] <= mtx[i][j - 1]) ans[i][j] = true;
            }
            if(i > 1)
            {
                if(mtx[i][j] >= mtx[i - 1][j]) ans[i - 1][j] = true;
                if(mtx[i][j] <= mtx[i - 1][j]) ans[i][j] = true;
            }
        }

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j)  
            if(ans[i][j] == false) ++cnt;

    cout << cnt << '\n';

    return 0;
}