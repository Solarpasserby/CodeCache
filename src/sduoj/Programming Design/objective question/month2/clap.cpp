#include<bits/stdc++.h>

using namespace std;

int n, t;
int num[50];

int myHash(int x) {return (x - 1) % n;}
bool check(int x)
{
    if (x % 7 == 0) return true;
    while(x)
    {
        if(x % 10 == 7) return true;
        x /= 10;
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    cin >> n >> t;

    for(int i = 1; i <= t; ++i)
        if(check(i)) ++num[myHash(i)];

    for(int i = 0; i < n; ++i)
        cout << num[i] << ' ';
    cout << '\n';

    return 0;
}