#include<bits/stdc++.h>

using namespace std;

const int N = 5e6 + 5;

int a[N];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n, ans = 0;
    unordered_map<int, int> m;
    string s;
    cin >> n >> s;
    for(int i = 1; i <= n; ++i)
        a[i] = a[i - 1] + (int)(s[i - 1] - '0') - 1;
    for(int i = 1; i <= n; ++i) {
        if(a[i] == 0) ++ans;
        ans += m[a[i]];
        ++m[a[i]];
    }

    cout << ans << '\n';

    return 0;
}