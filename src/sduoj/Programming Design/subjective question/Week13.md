## Week 13

#### Question1

**解法**

求整段石子合并的最大得分，可以转化为求更小段石子合并的最大得分。可以将一段石子分成两段，假设共有n堆石子，则有n-1种划分方法，遍历所有的划分，求得分数最大值。因此可以使用动态规划实现，从段长度小的石子段开始，逐步更新更长的段的最大得分，由此可以得到最终答案。特别地，由于整个石子堆是循环而不分先后的，因此我还遍历了所有长度为n的石子段，以求得最大值

**时间复杂度**

需从长度为1的石子段逐步维护到长度为n的石子段，每个相同长度的石子段有n个，每个石子段有k种划分，因此总的时间复杂度为$O(n^3)$

**代码**

```c++
#include<bits/stdc++.h>

using namespace std;

int n;
int sum[105]; //前缀和，分数的一部分构成
int dp[105][105]; //区间dp，用于求最大值
int dpb[105][105]; //区间dp，用于求最小值

int func(int l, int r) //计算区间内数的总和
{
    if(l <= r) return sum[r] - sum[l-1];
    else return sum[n] - sum[l-1] + sum[r]; //成环时的处理
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> n;
    for(int i = 1; i <= n; ++i)
    {
        cin >> sum[i];
        sum[i] += sum[i-1]; //生成前缀和
    }
    
    for(int i = 1; i < n; ++i) //段长度
        for(int j = 1; j <= n; ++j) //左端点
        {
            int r = (j+i-1)%n+1; //计算右端点，这里实现使用了循环数组
            for(int k = 0; k < i; ++k) //划分
            {
                int l = (j+k-1)%n+1, m = (j+k)%n+1; //计算划分区间的左右端点
                dp[j][r] = max(dp[j][r], dp[j][l]+dp[m][r]); //寻找得分最大划分
                if(dpb[j][r] == 0) dpb[j][r] = dpb[j][l]+dpb[m][r];
                else dpb[j][r] = min(dpb[j][r], dpb[j][l]+dpb[m][r]); //寻找得分最小划分
            }
            dp[j][r] += func(j, r); //加上当前段的分数
            dpb[j][r] += func(j, r); //加上当前段的分数
        }

    int ansa = 0, ansb = INT32_MAX;
    for(int i = 1; i <= n; ++i) //遍历长度为n的段，找到最值
    {
        int r = (i+n-2)%n+1;
        ansa = max(ansa, dp[i][r]);
        ansb = min(ansb, dpb[i][r]);
    }
    cout << ansb << '\n';
    cout << ansa << '\n';

    return 0;
}
```

#### Question2

**解法**

长度为n的序列的排序数量，可以由长度为n-1的序列的排序数量推出。具体地，使用n位二进制，其每一位置0或置1表示序列对应数字是否参与排序，使用数字标记当前排序的最末尾数字，于是有以下逻辑可以求得最大排序数量，从长度为1的序列开始，逐步更新更长序列的排序数量；对于结尾为x，选择状态为b的序列，找到状态为c，即b中第x位置0的状态，结尾y与x的差值大于k的所有情况，将这些情况下的排序数量相加，即可得到所求序列的排序数量。因此可以借助动态规划求解问题

**时间复杂度**

共有2^n个状态，排序时每个状态至多有n个结尾数字，对确定状态确定结尾数字情况求解排序数量时，还需遍历去掉结尾数字后的状态下的所有结尾数字的情况，至多有n个结尾。因此总体时间复杂度为$O(n^2 \cdot 2^n)$

**代码**

```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, d;
ll dp[65600][18]; //状态压缩dp，第一维表示所选状态，第二维表示结尾数字序号
int data[18]; //存储第i个数字
vector<vector<int>> g; //存储长度为m的所有状态，方便遍历

void init() //初始化g
{
    g.resize(n+1); 
    for(int i = 0; i < (1 << n); ++i) {
        int t = 0;
        for(int j = 1; j <= i; j <<= 1)
            if(i & j) ++t; //统计状态中所选数字的个数
        if(t != 0) g[t].push_back(i);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> n >> d;
    for(int i = 1; i <= n; ++i) cin >> data[i];

    init();
    for(int len = 1; len <= n; ++len)
        for(int i: g[len]) //从短序列开始遍历所有状态
            for(int j = 1; j <= n; ++j) { //数字序号
                if(!(i&(1<<(j-1)))) continue; //若当前状态不含序号j则跳过
                if(len == 1) { dp[i][j] = 1; break; } //若序列长度为1，初始化
                int u = i^(1<<(j-1)); //得到取出序号j的状态u
                for(int k = 1; k <= n; ++k) //遍历状态u下满足混乱排序条件的数字序号
                    if(u&(1<<(k-1)) && abs(data[k]-data[j])>d) dp[i][j] += dp[u][k];
            }

    ll ans = 0;
    for(int i = 1; i <= n; ++i) ans += dp[(1<<n)-1][i]; //求和全部选取状态下的所有选取数量
    cout << ans << '\n';

    return 0;
}
```

#### Question3

```c++
for (int s = 0; s < (1 << n); ++s)
    for (int t = s; ; t = (t - 1) & s) {
        // 一些 O(1) 的操作
        if (t == 0) break;
    }
```

外层循环执行了2^n次，内层循环每次循环将最末位的1置0，至多执行n次，因此总体时间复杂度为$O(n\cdot2^n)$