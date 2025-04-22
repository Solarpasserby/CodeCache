## Week8

#### Question1

**解法**

野路子😱，逐个遍历两个区间数组，将重合的值累加

**时间复杂度**

遍历两个长度为$n$的数组，时间复杂度为$O(n)$

**代码**

```c++
#include<bits/stdc++.h>

using namespace std;

//使用两个数组存a, b装车区间
pair<int, int> pa[2005];
pair<int, int> pb[2005];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i)
        cin >> pa[i].first >> pa[i].second;
    for(int i = 1; i <= n; ++i)
        cin >> pb[i].first >> pb[i].second;

    long long ans = 0;
    for(int i = 1, j = 1; i <= n && j <= n;)
    {
        for(; pa[i].first >= pb[j].second && j <= n; ++j); //找到b中第一个结束时间在a之前的区间
        if(j > n) break;
        ans += max(0, min(pa[i].second, pb[j].second) - max(pa[i].first, pb[j].first)); //计算重合区间
        if(pa[i].second > pb[j].second) ++j; //当a区间的结束时间大于b，则可能存在b区间依然满足在a之前
        else ++i; //否则a区间已被完全计算，跳过
    }

    cout << ans << '\n';

    return 0;
}
```

#### Question2

**解法**

问题可以转换为当前图中是否存在负权环路，由课上所讲的内容，知道可以借助Bellman-ford 算法来处理，在每次松弛点时借助一个计数器来记录当前点被松弛的次数。建立一个超级源点通向所有点，并使用Bellman-ford 算法松弛点，当计数器的次数大于等于边的总数，则说明至少存在一条边两次出现在了最短路径中，且该边的权重为负数，因此说明图中存在负权环路。依据这个方法即可解决问题

**时间复杂度**

最坏情况下每个点都被松弛最大次数，则可以得到时间复杂度为$O((m+w)n)$

**代码**

```c++
#include<bits/stdc++.h>

using namespace std;

bool spfa(const vector<vector<pair<int, int>>> &e, int n)
{
    queue<int> q;
    vector<bool> inq(n + 1, false); //检查是否已经在队列中
    vector<int> cnt(n + 1, 0); //计数器
    vector<int> dis(n + 1, 1e9); //到源点的距离
    q.push(0); //初始化，添加源点以松弛相邻点
    dis[0] = 0;

    while(!q.empty())
    {
        int tmp = q.front();
        q.pop();
        inq[tmp] = false;
        for(auto a: e[tmp])
        {
            if(dis[a.first] > dis[tmp] + a.second) //如果点可以被松弛
            {
                dis[a.first] = dis[tmp] + a.second; //更行距离
                if(!inq[a.first]) //若该点不在队列中则加入队列
                {
                    inq[a.first] = true;
                    q.push(a.first);
                }
                if(++cnt[a.first] > n) return true; //松弛次数大于等于边数，则存在负权环路
            }
        }
    }
    return false; //可以完全松弛所有点，说明不存在负权环路
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int times;
    cin >> times;
    while(times--)
    {
        int n, m, w;
        cin >> n >> m >> w;
        vector<vector<pair<int, int>>> e(n + 1);
        while(m--)
        {
            int a, b, c;
            cin >> a >> b >> c;
            e[a].emplace_back(b, c);
            e[b].emplace_back(a, c);
        }
        while(w--)
        {
            int a, b, c;
            cin >> a >> b >> c;
            e[a].emplace_back(b, -c);
        }
        for(int i = 1; i <= n; ++i) e[0].emplace_back(n, 0); //设置超级源点

        //求解
        if(spfa(e, n)) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
```

