#include<bits/stdc++.h>

using namespace std;

int N, K, maxReach;
int f[10000]; // 用于存储在当前牌组下，表示这个数字最少需要多少张牌
int card[20]; // 用于存储当前所选择的卡
int cardAns[20]; // 用于存储答案，即最优的卡牌选择

// 用于在给定牌组的情况下，求最大的能表示的数字
int func(int a)
{
    f[0] = 0;
    for (int i = 1; i < 10000; i++) f[i] = 10000;

    for (int i = 1; i <= a; i++)
        for (int j = card[i]; j <= card[i] * N; j++)
            f[j] = min(f[j - card[i]] + 1, f[j]);

    for (int i = 1; i <= card[a] * N; i++)
        if (f[i] <= N) continue;
        else return (i - 1);

    return (card[a] * N);
}

// 深度优先搜索，用于寻找符合条件的牌组和最大表示数
void dfs(int rLimit, int depth)
{
    if (depth != K)
    {
        for(int i = card[depth] + 1; i <= rLimit + 1; i++)
        {
            card[depth + 1] = i;
            dfs(func(depth + 1), depth + 1);
        }
    }
    else if (rLimit > maxReach)
    {
        maxReach = rLimit;
        for(int i = 1; i <= K; i++) cardAns[i] = card[i];
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> N >> K;
    card[1] = 1;

    dfs(N, 1);
    for(int i = 1; i <= K; i++)
        cout << cardAns[i] << ' ';
    cout << '\n' << "MAX=" << maxReach << '\n';

    return 0;
}