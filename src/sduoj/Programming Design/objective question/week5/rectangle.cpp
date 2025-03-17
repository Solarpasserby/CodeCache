#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 100005;

ll num[N];

struct myStack
{
    int s[N];
    int t = 0;
    myStack() {s[0] = 0;}
    int top() {return s[t];}
    int ltop() {return s[t-1];}
    bool empty() {return t == 0;}
    void push(int a) {s[++t] = a;}
    void pop() {--t;}
};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n;
    ll ans = 0;
    myStack stk;
    cin >> n;
    for(int i = 1; i <= n; ++i)
        cin >> num[i];
    for(int i = 1; i <= n; ++i)
    {
        while(!stk.empty() && num[stk.top()] > num[i])
        {
            ans = max(ans, num[stk.top()] * (i - stk.ltop() - 1));
            stk.pop();
        }
        stk.push(i);
    }
    while(!stk.empty())
    {
        ans = max(ans, num[stk.top()] * (n - stk.ltop()));
        stk.pop();
    }

    cout << ans << '\n';

    return 0;
}