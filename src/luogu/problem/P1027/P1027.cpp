#include<bits/stdc++.h>

using namespace std;

int s, t, a, b;
int city[105][9];
int route[105], from[105], to[105];

pair<int, int> findPoint(int x1, int y1, int x2, int y2, int x3, int y3)
{
    int l1, l2, l3;
    pair<int, int> res;
    l1 = pow(x1 - x2, 2) + pow(y1 - y2, 2); 
    l2 = pow(x1 - x3, 2) + pow(y1 - y3, 2); 
    l3 = pow(x2 - x3, 2) + pow(y2 - y3, 2);
    
    if (l1 > l2 && l1 > l3)
    {
        res.first = x1 + x2 - x3;
        res.second = y1 + y2 - y3;
    }
    else if (l2 > l1 && l2 > l3)
    {
        res.first = x1 + x3 - x2;
        res.second = y1 + y3 - y2;
    }
    else
    {
        res.first = x2 + x3 - x1;
        res.second = y2 + y3 - y1;
    }

    return res;
}

void dfs()
{
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for(;n--;)
    {
        cin >> s >> t >> a >> b;
        for(int i = 1; i <= s; i++)
        {
            cin >> city[i][1] >> city[i][2] >> city[i][3] >> city[i][4] >> city[i][5] >> city[i][6] >> city[i][0];
            auto tmp = findPoint(city[i][1], city[i][2], city[i][3], city[i][4], city[i][5], city[i][6]);
            city[i][7] = tmp.first;
            city[i][8] = tmp.second;
        }
    }

    return 0;
}