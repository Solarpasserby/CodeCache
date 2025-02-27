#include<bits/stdc++.h>

using namespace std;

int num[2000];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n, count = 0;
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> num[i];

    sort(num, num + n);
    for(int i = 0; i < n - 1; i++)
        if (num[i] + 1 == num[i + 1]) ++count;

    cout << count << '\n';

    return 0;
}