## Week 10

#### Question1

树状数组支持单点修改、区间查询，可以解决区间求和的问题，而显然我们知道区间的和又知道区间的长度，很容易便可以得出区间的平均值。

#### Question2

**解法**

学习了相关知识后明白了该问题是一个典型的二维逆序问题，可以先按照第一维优先第二维次之升序排序，这样可以保证对于排序完成的数据，任意一个其中的元素，该元素大于其他元素的个数（这里定义一个元素大于另一个元素，当且仅当其两个维度中的数据均大于等于另一个元素）即为该元素左侧满足第二维小于等于当前元素第二维的元素的个数，如此可以转化为求排序玩的数据中第二维的顺序数对的个数，这个问题就可以使用树状数组求解。将数的频次作为树状数组的元素，从左往右遍历数据，计算小于等于当前数字的数字的频次和，并维护当前数字的频次，由此便可得到答案

**时间复杂度**

对所有数据排序的时间复杂度为$O(n\log n)$，而后续对于每个数字频次的维护以及小于等于该数字的数字的频次的求和均需要$O(\log n)$ 的时间复杂度，因此总体上时间复杂度为$O(n\log n)$

**代码**

```c++
#include<bits/stdc++.h>

using namespace std;

#define ll long long
#define lowbit(x) ((x) & -(x))

const int N = 1e6+5;

int n;
int tree[N], ans[N]; //定义树状数组，这里直接将结果保存在数组中；定义答案数组，记录每个分数出现次数
ll sec[N]; //获取第二维的数据，主要是为了后续对数据进行离散化处理
unordered_map<ll, int> rk; //离散化处理，记录每个数据对应的位次

//单点更新
void update(int x, int val)
{
    while(x <= n)
    {
        tree[x] += val;
        x += lowbit(x);
    }
}

//区间求和
int sum(int x)
{
    int res = 0;
    while(x > 0)
    {
        res += tree[x];
        x -= lowbit(x);
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> n;
    vector<pair<ll, ll>> num(n + 1);
    for(int i = 1; i <= n; ++i)
    {
        cin >> num[i].first >> num[i].second;
        sec[i] = num[i].second;
    }
    sort(sec + 1, sec + n + 1); //排序第二维数据以用来进行离散化处理
    sort(num.begin() + 1, num.end()); //排序数据，第一维优先第二维次之升序排序

    sec[0] = -1;
    for(int i = 1, j = 0; i <= n; ++i) //离散化处理
    {
        if(sec[i] == sec[i - 1]) continue;
        else rk[sec[i]] = ++j; //对每个第二维的数据，给一个相对位次
    }

    for(int i = 1; i <= n; ++i)
    {
        int id = rk[num[i].second];
        ++ans[sum(id)]; //统计小于等于当前数字的数字的频次的和，得到分数，自加分数出现次数
        update(id, 1); //维护当前数字的频次
    }

    for(int i = 0; i < n; ++i)
        cout << ans[i] << '\n';

    return 0;
}
```

#### Question3

**解法**

区间最值的问题，通过特定的方法维护线段树，已经特定方法查询线段树，也可以实现对该问题的求解，在当前$n=2\times10^5$的数量级下可以完成解题、

**时间复杂度**

特定维护线段树，对于每个节点，将新值赋给该节点，同时使用其子节点更新该节点；以同样的方式更新其父节点，如此循环直至达到当前路径最大父节点。该操作的需更新$\log n$ 个节点，每个节点需更新$\log n$次，因此单次更新的时间复杂度为$O((\log n)^2)$。特定查询线段树，检查当前节点区间是否被涵盖，被涵盖则直接返回节点元素，否则节点值减1，递归检查，该查询时间复杂度同样为$O((\log n)^2)$。因此总体时间复杂度为$O(n(\log n)^2)$

**代码**

```c++
#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int m, p, cnt, tmp;
int tree[N], A[N]; //前者为树结构，后者为真实数据

int lowbit(int x) { return (x & -x); }

//区间最值更新
void update(int x, int val)
{
    A[x] = tree[x] = val;
    while(x <= cnt)
    {
        for(int i = 1; i < lowbit(x); i <<= 1) //用子节点更新自身
            tree[x] = max(tree[x], tree[x - i]);
        x += lowbit(x);
    }
}

//区间最值查询
//实际上抄的模板，不太能理解如何通过A确定最小值
int query(int l, int r)
{
    int res = 0;
    while(l <= r)
    {
        res = max(res, A[r]); //查询区间补完全包含节点涵盖区间，得到当前节点值，更新数据
        --r;
        while(r - l >= lowbit(r)) //查询区间包含节点涵盖区间，直接更新，转到剩余部分
        {
            res = max(res, tree[r]);
            r -= lowbit(r);
        }
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> m >> p;
    cnt = tmp = 0;
    while(m--)
    {
        char c; int a;
        cin >> c >> a;
        if(c == 'A')
            update(++cnt, (tmp + a) % p);
        else
            cout << (tmp = query(cnt - a + 1, cnt)) << '\n';
    }

    return 0;
}
```

