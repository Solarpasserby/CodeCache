#include<bits/stdc++.h>

using namespace std;

void func(string &s)
{
    for(int i = 0; i < s.size(); ++i)
    {
        char c = s[i];
        if(c == 'e' || c == 'i' || c == 'o' || c == 'u')
            s[i] = 'a';
    }
}

int check(const string &s, int pos)
{
    int l, r;
    int m1, m2, m3;
    m1 = m2 = m3 = 0;
    l = pos - 1, r = pos + 1;
    while(l >= 0 && r < s.size() && s[l] == s[r]) --l, ++r;
    m1 = r - l - 1;
    if(pos+1 < s.size() && s[pos] == s[pos+1])
    {
        l = pos - 1, r = pos + 2;
        while(l >= 0 && r < s.size() && s[l] == s[r]) --l, ++r;
        m2 = r - l - 1;
    }
    if(pos-1 >= 0 && s[pos-1] == s[pos])
    {
        l = pos - 2, r = pos + 1;
        while(l >= 0 && r < s.size() && s[l] == s[r]) --l, ++r;
        m3 = r - l - 1;
    }
    return max(m1, max(m2, m3));
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, ans = 0;
    string s;
    cin >> n >> s;
    func(s);
    for(int i = 0; i < n; ++i)
        ans = max(ans, check(s, i));
    cout << ans << '\n';

    return 0;
}