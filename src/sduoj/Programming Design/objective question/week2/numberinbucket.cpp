#include<bits/stdc++.h>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> bucket(n + 1);

    for(;m--;)
    {
        int x, bucketNum;
        cin >> x >> bucketNum;
        bucket[bucketNum].push_back(x);
    }

    for(int i = 1; i <= n; i++)
    {
        sort(bucket[i].begin(), bucket[i].end());
        for(auto it = bucket[i].begin(); it != bucket[i].end(); ++it)
            cout << *it << ' ';
        cout << '\n';
    }

    return 0;
}