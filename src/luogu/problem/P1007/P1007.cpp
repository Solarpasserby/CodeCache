#include<iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int L, N, minT, maxT;
    cin >> L >> N;

    minT = 0, maxT = 114514;
    for(int i = 0; i < N; i++)
    {
        int x, tmp;
        cin >> x;
        tmp = min(x, L + 1 - x);
        if (tmp > minT) minT = tmp;
        if (tmp < maxT) maxT = tmp;
    }

    if (N != 0) maxT = L + 1 - maxT;
    else maxT = 0;
    cout << minT << ' ' << maxT << '\n';

    return 0;
}