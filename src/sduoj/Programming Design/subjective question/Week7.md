## Week7

#### Question 1

只记录了邻接点的信息，占用的空间比邻接矩阵少，空间复杂度仅为O(𝑚)

#### Question2

最小瓶颈生成树是指在一个连通无向图中，所有生成树中**最大边权值最小**的那个生成树。而我们构建最小生成树时，总是会优先选择最小的边，使得最后添加的边是所有生成树中最大权值最小的边，满足最小瓶颈生成树的定义，因此在无向图中，最小生成树一定是最小瓶颈生成树

#### Question3

**解法**

这道题可以使用并查集来做，把村庄抽象成不同元素，每个元素都有自己所属的组，村庄之间建立公路就可以抽象成把两个元素所在的组合并。因此修建公路的条数，可以表示为还需合并的次数，由于合并次数最多为村庄的数量减一，因此可以对齐进行求解

**时间复杂度**

对于并查集，使用按秩合并和路径压缩，因此查询和合并的复杂度近似为$O(1)$。对于$m$次操作，总体的时间复杂度近似为$O(m)$

**代码**

```c++
#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

//并查集
struct Union
{
    int f[N];
    int rb; //表示合并次数，初始设置为1

    Union() //初始化，每个元素的父节点是自身
    {
        for(int i = 0; i < N; ++i) f[i] = i;
        rb = 1;
    }

    pair<int, int> find(int t)
    {
        int h = 1; //记录树高度
        for(; f[t] != t; ++h) t = f[t]; //迭代查找
        return {t, h};
    }

    int join(int x, int y)
    {
        pair<int, int> t1, t2;
        t1 = find(x);
        t2 = find(y);
        if(t1.first != t2.first) //不是相同组，进行合并
        {
            ++rb; //合并次数加一
            //依据树的高度进行合并
            if(t1.second > t2.second)
                f[t2.first] = t1.first;
            else
                f[t1.first] = t2.first;
        }
        return rb; //返回合并次数
    }
};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int m, n;
    Union un;
    cin >> n >> m;
    while(m--)
    {
        int x, y;
        cin >> x >> y;
        cout << n - un.join(x, y) << '\n'; //计算答案
    }

    return 0;
}
```

#### Question4

**解法**

可以把水渠抽象成边，田地抽象成点，问题就可以转化成求解最小生成树，因为这样可以使水渠的花费最小。而由于问题中还存在抽水机，可以向任意田地供水，因此进一步的，我们可以设置一个超级源点，使其能通往所有点，同时边权为抽水机花费。由此我们仍然可以使用最小生成树来解题。

**时间复杂度**

总共存在$m+n$条边，由于使用Kruskal算法，故先要对边进行排序，时间复杂度为 $O((m+n)\log(m+n))$ 。随后仅需从小到大遍历所有边，当顶点不重复时，添加边的权重即可。由于并查集使用按秩合并和路径压缩，因此查询和合并的复杂度近似为$O(1)$，故遍历所有边求解的时间复杂度为 $O(m+n)$。综上总体的时间复杂度为$O((m+n)\log(m+n))$ 

**代码**

```c++
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 1e5 + 5;

int n, m, p;

//并查集
struct Union
{
    int f[N];
    int rb;

    Union()
    {
        for(int i = 0; i <= N; ++i) f[i] = i;
        rb = 0;
    }

    pair<int, int> find(int t)
    {
        int h = 1;
        for(; f[t] != t; ++h) t = f[t];
        return {t, h};
    }

    int join(int x, int y)
    {
        pair<int, int> t1, t2;
        t1 = find(x);
        t2 = find(y);
        if(t1.first != t2.first)
        {
            ++rb;
            if(t1.second > t2.second)
                f[t2.first] = t1.first;
            else
                f[t1.first] = t2.first;
            return rb;
        }
        return -1;
    }
};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m >> p;

    ll cost = 0;
    Union un;
    vector<tuple<int, int, int>> edge;

    while(m--)
    {
        int x, y, z;
        cin >> x >> y >> z;
        edge.push_back({x, y, z}); //添加题目所给边及权重
    }
    for(int i = 1; i <= n; ++i) edge.push_back({0, i, p}); //添加超级源点到所有点的边及权重
    sort(edge.begin(), edge.end(), [](const auto& a, const auto& b) {
        return get<2>(a) < get<2>(b);
    }); //排序

    for(auto& t : edge)
    {
        if(un.rb >= n) break; //已添加所有点，推出循环
        int x, y, z;
        tie(x, y, z) = t;
        int t_res = un.join(x, y); //尝试合并点
        if(t_res == -1) continue; //失败则跳过当前边
        else cost += z; //成功则加上边的权重
    }

    cout << cost << '\n';
    return 0;
}
```





