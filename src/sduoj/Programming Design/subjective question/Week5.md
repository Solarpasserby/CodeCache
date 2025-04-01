## Week5

#### Question1

```c++
int func(int k)
{
    if (k < 1) return 0;
    return 1 + (func(k - 1) << 1);
}
```

#### Question2

因为这些数据结构都仅对每个数据进行了常数级次操作，故随着数据规模的增大，复杂度也是线性增大的

#### Question3

**解法**

求最大公约数的问题，可以进行转化。每个整数可以转化成其质因数对应幂次的积，即可以进行质因数分解，如$60=2^2\times3^1\times5^1\times7^0$。考虑到题目给出的底数不超过$100$，因此任何乘数都可以使用一个数组表示，其中数组的第$i$位表示第$i+1$个质数。因为求若干整数的最大公约数可以转化成求各整数质因数分解后，各质数最小幂次的积，当我们把整数转化为数组后，我们就可以求解一个最小数组，这个数组中的每一项都是所有数组中该项的最小值。同时注意到存在对已有整数有$m$次区间操作，因此这样的题目我选择使用线段树来处理，这样既可以保证平均单次区间操作的复杂度维持在$O(\log n)$，而且最后求解的复杂度为$O(1)$，可以满足题目要求。由于题目所给整数过大且有多次幂运算，还需要使用取模快速幂的算法

**时间复杂度**

总共进行$m$次区间操作，平均单次区间操作的复杂度维持在$O(\log n)$，操作的时间复杂度为$O(m\log n)$，最终求解的复杂度为$O(1)$，因此总体时间复杂度为$O(m\log n)$

**代码**

```c++
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int prime[25] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97}; //直接写出100以内的所有质数
const int N = 100005; //数据最大值
const int M = 1e9 + 7; //取模数

ll tree[N<<2][25]; //建立线段树，每个数组元素有一个数组构成，每位对应第i+1位质数的指数
ll tag[N<<2][25]; //同时建立线段树的懒惰标签

ll ls(ll p){return p<<1;} //快速运算左子树位置
ll rs(ll p){return p<<1|1;} //快速运算右子树

//当线段树的孩子更改后，更新其父亲
void push_up(ll p, ll c)
{
    tree[p][c] = min(tree[ls(p)][c], tree[rs(p)][c]);
}

//为节点添加懒惰标签，记录当前操作对此区间的影响
void addtag(ll p, ll c, ll b)
{
    tag[p][c] += b; //记录对该区间对应指数加b
    tree[p][c] += b; //对应指数指数加b
}

//当被懒惰标签标记的节点的子节点需要单独更新时，下移标签
void push_down(ll p, ll c)
{
    if(tag[p][c])
    {
        addtag(ls(p), c, tag[p][c]); //下移标签
        addtag(rs(p), c, tag[p][c]); //下移标签
        tag[p][c] = 0; //标签置0
    }
}

//总体的处理区间更新的函数
void update(ll L, ll R, ll p, ll pl, ll pr, ll c, ll b)
{
    if(L <= pl && R >= pr)
    {
        addtag(p, c, b); //若待更新区间涵盖当前区间，直接贴上懒惰标签
        return;
    }
    //否则处理当前区间和子区间
    push_down(p, c); //下移标签
    ll mid = (pl + pr)>>1; //得到当前区间的中间点
    if(L <= mid) update(L, R, ls(p), pl, mid, c, b); //递归更新左半区间
    if(R > mid) update(L, R, rs(p), mid + 1, pr, c, b); //递归更新右半区间
    push_up(p, c); //将子区间的更新上推
}

//取模快速幂
long long binpow(ll a, ll b)
{
    a %= M;
    ll res = 1;
    while(b)
    {
        if(b & 1) res = res * a % M;
        a = a * a % M;
        b >>= 1;
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n, m;
    ll ans = 1; //存储答案
    cin >> n >> m;

    while(m--)
    {
        int l, r;
        ll tc, tb;
        cin >> l >> r >> tc >> tb; //获取单次操作
        for(int i = 0; i < 25; ++i)
        {
            int tmp = 0;
            while(tc % prime[i] == 0)
            {
                ++tmp;
                tc /= prime[i];
            }
            update(l, r, 1, 1, n, i, tmp * tb); //更新线段树

            if(tc == 1) break;
        }
    }

    for(int i = 0; i < 25; ++i)
        ans = ans * binpow(prime[i], tree[1][i]) % M; //得到结果

    cout << ans << '\n';

    return 0;
}
```

