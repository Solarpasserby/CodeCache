#include<bits/stdc++.h>

using namespace std;

int n;

void func(string &s)
{
    string tmp;
    int t = s.size();
    for(int i = 0; i < t && (i + t) <= n; ++i)
    {
        if(s[i] == '0') tmp.push_back('1');
        else tmp.push_back('0');
    }
    s.append(tmp);
}

int find(const string& s, const string& f)
{
    int res = 0;
    for(int i = 0; i <= s.size() - f.size(); ++i)
    {
        int j = 0;
        while(j < f.size() && f[j] == s[i + j]) ++j;
        if(j == f.size()) ++res;
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    string s, fd;
    cin >> n >> fd;
    s = "01";
    while(s.size() < n) func(s);
    cout << find(s, fd) << '\n';

    return 0;
}