## Week4

#### Question1

eps设置的过小时，算法的迭代时间增加，效率下降。eps设置的过大时，因为精度缺失，使得算法提前终止，无法得到正确解。

#### Question2

1. 对于第一题**割绳子**，可能存在$n$段绳子中，$n-1$条绳子都极短，而$1$条绳子极长的特殊情况，导致截取的绳子都产生在最长的绳子上。
2. 对于第三题**商店**，可能存在所有商店价格相同的特殊情况。

#### Question3

**解法**

容易想到的一个思路是，从一段绳子开始，计算可以截取的最长的绳子，随后逐次增加绳子段数，直到到达$k$。在这样的思路下，我们可以维护一个最大堆，表示要使绳子段数增加$1$，可以选取的最长截取长度，同时最大堆中的元素包含两个值：绳子长度、截取段数，$\text{绳子长度}/\text{截取段数}$的值越大，优先级越高。每次选取优先级最大的元素，将其在堆中删除，并将其“截取段数”的值$+1$后再添入堆中。由此重复$k$次可以得到答案。

**时间复杂度**

最大堆的删除和插入的时间复杂度均为$O(\log n)$，初始化最大堆（这里是直接插入）的复杂度为$O(n\log n)$，后续求解需进行$k$次插入和删除，复杂度为$O(k\log n)$，因此总的时间复杂度为$O(\max(n, k)\cdot\log n)$。

**代码**

```c++
#include<bits/stdc++.h>

using namespace std;

//自定义比较函数，这里使商最大的元素优先级最高，商即为 绳子长度/截取段数
struct cmp
{
    bool operator()(pair<int, int> a, pair<int, int> b)
    {
        return (a.first * 1.0 / a.second) < (b.first * 1.0 / b.second);
    }
};

//优先级队列，使队首始终为商最大的元素，元素有两个值：绳子长度、截取段数
priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> q;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    //初始化优先级队列
    while(n--)
    {
        int tmp;
        cin >> tmp;
        q.push(pair<int, int>(tmp, 1));
    }

    //删除插入元素
    while(k-- > 1)
    {
        pair<int, int> tmp;
        tmp = q.top();
        tmp.second += 1;
        q.push(tmp);
        q.pop();
    }

    cout << q.top().first * 1.0 / q.top().second << '\n';

    return 0;
}
```

#### Question4

**解法**

观察题目，发现商店价格数据段可以划分成多个不严格单调递增的子段。显然在每一个子段中最高值减去最低值即为该子段中的能取得的最大利润。可以证明，每个子段的和即为最大利润，每个利润不为$0$的子段的个数$\times2$即为交易次数。

**时间复杂度**

算法仅需遍历所有数据，故复杂度为$O(n)$。

**代码**

```c++
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

//记录商店价格
int price[100005];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int t, n, maxP, minP, cnt; //maxP, minP表示子段中的最大、最小值
    ll profit = 0;
    cin >> t;
    while(t--)
    {
        cin >> n;
        //初始化数组
        for(int i = 1; i <= n; ++i)
            cin >> price[i];
        
        cnt = 0;
        profit = 0;
        maxP = minP = price[n]; //初始化maxP, minP
        for(int i = n; i > 1; --i)
        {
            if (price[i] >= price[i - 1])
                minP = price[i - 1]; //判断是否单调
            else
            {
                if (maxP - minP != 0) cnt += 2; //次数+2
                profit += maxP - minP; //计算单调区间最大利润
                maxP = minP = price[i - 1]; //重新初始化maxP, minP
            }
        }

        //处理末尾数据
        if (maxP - minP != 0) cnt += 2;
        profit += maxP - minP;

        cout << profit << ' ' <<  cnt << '\n';
    }

    return 0;
}
```

