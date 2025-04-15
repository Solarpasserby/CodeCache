#include<bits/stdc++.h>

using namespace std;

int mp[505][505];
pair<int, int> trans[505][505];
queue<pair<int, int>> q;

void func(pair<int, int> tmp)
{
    int tx, ty;
    tx = tmp.first;
    ty = tmp.second;

    if(mp[tx-1][ty] == -1)
    {
        mp[tx-1][ty] = mp[tx][ty] + 1;
        q.push(pair(tx-1, ty));
    }
    if(mp[tx+1][ty] == -1)
    {
        mp[tx+1][ty] = mp[tx][ty] + 1;
        q.push(pair(tx+1, ty));
    }
    if(mp[tx][ty-1] == -1)
    {
        mp[tx][ty-1] = mp[tx][ty] + 1;
        q.push(pair(tx,ty-1));
    }
    if(mp[tx][ty+1] == -1)
    {
        mp[tx][ty+1] = mp[tx][ty] + 1;
        q.push(pair(tx, ty+1));
    }
}

int main()
{
    int n, m, k;
    pair<int, int> s, e;
    
    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            char c;
            cin >> c;
            switch (c)
            {
            case 'S':
                mp[i][j] = 0;
                s.first = i; //行
                s.second = j; //列
                break;

            case 'E':
                mp[i][j] = -1; //特殊?
                e.first = i; //行
                e.second = j; //列
                break;

            case '.':
                mp[i][j] = -1;
                break;

            case '#':
                mp[i][j] = -2;
                break;
            
            default:
                break;
            }
        }

    for(int i = 1; i <= k; ++i)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        trans[x1+1][y1+1] = pair(x2+1, y2+1);
        trans[x2+1][y2+1] = pair(x1+1, y1+1);
    }

    q.push(s);
    while(!q.empty())
    {
        int tx, ty;
        tx = q.front().first;
        ty = q.front().second;

        func(q.front());
        if(trans[tx][ty].first != 0 && mp[trans[tx][ty].first][trans[tx][ty].second] == -1)
        {
            mp[trans[tx][ty].first][trans[tx][ty].second] = mp[tx][ty] + 1;
            q.push(pair(trans[tx][ty].first, trans[tx][ty].second));
        }
        else if(trans[tx][ty].first != 0 && mp[trans[tx][ty].first][trans[tx][ty].second] > mp[tx][ty] + 1)
        {
            mp[trans[tx][ty].first][trans[tx][ty].second] = mp[tx][ty] + 1;
            q.push(pair(trans[tx][ty].first, trans[tx][ty].second));
        }

        q.pop();

        if(mp[e.first][e.second] != -1)
        {
            cout << mp[e.first][e.second] << '\n';
            exit(0);
        }
    }

    cout << -1 << '\n';
    
    return 0;
}