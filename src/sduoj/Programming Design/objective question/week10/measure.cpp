#include<bits/stdc++.h>

using namespace std;

int num[100005];

int main() 
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> num[i];
    sort(num, num + n);
    double mid = n & 1 ? num[n / 2] : (num[n / 2 - 1] + num[n / 2]) / 2.0;
    if(mid == (int)mid)
        printf("%d %d %d", num[n - 1], (int)mid, num[0]);
    else
        printf("%d %.1lf %d", num[n - 1], mid, num[0]);

    return 0;
}