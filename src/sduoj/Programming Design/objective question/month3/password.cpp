#include<bits/stdc++.h>

using namespace std;

int judgeType(const char& c)
{
    if(c >= 'a' && c <= 'z') return 1;
    if(c >= 'A' && c <= 'Z') return 2;
    return 0;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int pre, cnt;
    string s;
    cin >> s;
    if(s.size() < 6) { cout << "0\n"; exit(0); }
    pre = judgeType(s[0]);
    cnt = 1;
    for(int i = 1; i < s.size(); ++i)
    {
        if(pre != judgeType(s[i])) ++cnt;
        pre = judgeType(s[i]);
    }
    cout << cnt << '\n';

    return 0;
}