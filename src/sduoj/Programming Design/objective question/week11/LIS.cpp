#include<bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n;
    vector<int> solution;
    cin >> n;
    while(n--)
    {
        int tmp;
        cin >> tmp;
        auto it = lower_bound(solution.begin(), solution.end(), tmp);
        if(it == solution.end()) solution.push_back(tmp);
        else *it = tmp;
    }

    cout << solution.size() << '\n';

    return 0;
}