#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int snk[N];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i)
        cin >> snk[i];

    unordered_map<int, int> hp;
    for(int i = n; i >= 0; --i)
    {
        if(i == 0) cout << "0\n";
        else if(hp[snk[i]]) { cout << i << '\n'; break; }
        ++hp[snk[i]];
    }

    return 0;
}