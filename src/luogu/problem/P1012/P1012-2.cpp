#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

bool cmp(const string &l, const string &r)
{
    return (l + r > r + l);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n;
    string s[30];
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> s[i];
    sort(s + 1, s + n + 1, cmp);
    for(int i = 1; i <= n; i++) cout << s[i];
    cout << '\n';

    return 0;
}