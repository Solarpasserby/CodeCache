## Week 12

#### Question1

可以在状态转移时记录对当前物品的选取情况。具体来说，使用`bitset<n>`来表示物品的选取，遍历到第`i`个物品时，依据状态转移情况，使`bitset[i]`置`0`或置`1`，代表选或不选，由此可以确定最优方案时选择的物品

#### Question2

**解法**

采用二进制拆分优化的方法，将对$k$个相同的物品的选取，转化为$log_2{k}$个物品的选取，在一定程度上优化了算法。具体来说，数字$0$~$15$可以由$1,2,4,8$完全表示。于是可以对所有物品进行二进制拆分，形成“新的物品”，再使用0-1背包算法求解即可

**时间复杂度**

$O(nv\log k)$

**代码**

```c++
#include<bits/stdc++.h>

using namespace std;

int n, v;
int w[10005], c[10005], m[10005]; //存储物品的重量、价值和数量
int new_w[100005], new_c[100005]; //存储新物品的重量和价值，用于后续dp
long long dp[10005]; 

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> n >> v;
    for(int i = 1; i <= n; ++i) //读取输入
        cin >> w[i] >> c[i] >> m[i];

    //二进制拆分
    int new_n = 0;
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= m[i]; j <<= 1) //每次循环j以2的倍数递增，物品数量m大于等于j则创建新物品，m减去j
        {
            new_w[++new_n] = j * w[i]; //新物品的重量为j倍的原物品重量
            new_c[new_n] = j * c[i]; //新物品的价值为j倍的原物品价值
            m[i] -= j;
        }
        if(m[i]) //m数量小于j，则直接依据m创建新物品
        {
            new_w[++new_n] = m[i] * w[i];
            new_c[new_n] =m[i] * c[i];
        }
    }

    //0-1背包算法求解
    for(int i = 1; i <= new_n; ++i)
        for(int j = v; j >= new_w[i]; --j)
            dp[j] = max(dp[j], dp[j-new_w[i]]+new_c[i]); //状态转移
    cout << dp[v] << '\n';

    return 0;
}
```





