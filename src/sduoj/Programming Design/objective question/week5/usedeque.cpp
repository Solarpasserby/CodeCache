#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n, k;
    ll num[1000005] = {0};
    deque<int> minq, maxq;

    cin >> n >> k;
    for(int i = 1; i <= n; ++i)
        cin >> num[i];
    for(int i = 1; i <= n; ++i)
    {
        while(!minq.empty() && num[minq.back()] > num[i]) minq.pop_back();
        minq.push_back(i);

        while(!minq.empty() && (i - minq.front() >= k)) minq.pop_front();
        if(i >= k) cout << num[minq.front()] << ' ';
    }
    cout << '\n';
    for(int i = 1; i <= n; ++i)
    {
        while(!maxq.empty() && num[maxq.back()] < num[i]) maxq.pop_back();
        maxq.push_back(i);

        while(!maxq.empty() && (i - maxq.front() >= k)) maxq.pop_front();
        if(i >= k) cout << num[maxq.front()] << ' ';
    }
    cout << '\n';
}