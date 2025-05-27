## Week 14

#### Question1

**解法**

使用dfs遍历树的所有节点，对于每个子树，求解其最大直径，该最大直径是包含子树根的最大直径，使用全局变量记录最大值及数量，即可得到该树的最大直径和数量

**时间复杂度**

采用dfs，复杂度为正比树的边数，即$O(n)$

**代码**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5+5;

int n;
ll dp[N], cnt[N]; //dp记录节点i的子树的深度，cnt记录最大深度路径的数量
ll ans, num; //记录dp过程中的最大直径及其对应的数量
vector<vector<int>> g; //存储树结构

void dfs(int u, int v) //对节点v进行dfs，其父节点为u
{
    //遍历所有孩子
    for(int a: g[v]) {
        if(a == u) continue; //跳过父子树
        dfs(v, a); //继续dfs，更新完所有数据后处理
        int t = dp[a] + 1; //计算当前路径的深度
        if(dp[v]+t>ans) { //计算直径，更新最大直径
            ans = dp[v]+t;
            num = cnt[v]*cnt[a]; //直径数量为最大深度路径数量之积
        } else if(dp[v]+t==ans) {
            num += cnt[v]*cnt[a]; //有相同深度的路径，更新次数
        }

        if(t > dp[v]) { //更新最大深度
            dp[v] = t;
            cnt[v] = cnt[a];
        } else if(t == dp[v]) {
            cnt[v] += cnt[a];
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> n;
    cnt[1] = 1, ans = 0;
    g.resize(n+1);
    for(int i = 2; i <= n; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
        cnt[i] = 1; //初始化cnt
    }
    dfs(0, 1); //dfs求解
    cout << ans << ' ' << num << '\n';

    return 0;
}
```

#### Question2

**解法**

查阅相关资料后，发现该问题具有通解，$Ans_n=\frac{3^n+(-1)^n+2}{4}$，因此可以使用快速幂求解

**时间复杂度**

$O(T\log n)$

**代码**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll mod = 998244353;
const ll inv4 = 748683265; //用以代替除以4

ll func(ll t) //快速幂
{
    if(t == 0) return 1;
    if(t == 1) return 3;
    ll tmp = func(t/2);
    if(t & 1) return tmp * tmp * 3 % mod;
    else return tmp * tmp % mod;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n;
    cin >> n;
    while(n--)
    {
        ll a;
        cin >> a;
        if(a & 1) cout << (func(a) + 1) % mod * inv4 % mod << '\n';
        else cout << (func(a) + 3) % mod * inv4 % mod << '\n';
    }

    return 0;
}
```

