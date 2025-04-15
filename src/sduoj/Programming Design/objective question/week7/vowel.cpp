#include<bits/stdc++.h>

using namespace std;

bool func(char c) { return c == 'a' | c == 'e' | c == 'i' | c == 'o' | c == 'u'; }

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n, t, ans;
    string s;
    t = ans = 0;
    cin >> n >> s;
    for(int i = 0; i < n ; ++i)
    {
        if(func(s[i])) ++t;
        else
        {
            if(t > ans) ans = t;
            t = 0;
        }
    }

    cout << ans << '\n';

    return 0;
}