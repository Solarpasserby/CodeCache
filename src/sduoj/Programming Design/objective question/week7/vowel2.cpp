#include<bits/stdc++.h>

using namespace std;

bool func(char c) { return c == 'a' | c == 'e' | c == 'i' | c == 'o' | c == 'u'; }

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n;
    bool f = true;
    string s, ans;
    cin >> n >> s;
    for(int i = 0; i < n ; ++i)
    {
        if(!func(s[i])) f = true;
        else if(f) f = false;
        else continue;
        ans += s[i];
    }

    cout << ans << '\n';

    return 0;
}