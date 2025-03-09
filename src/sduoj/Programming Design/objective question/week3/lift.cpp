#include<bits/stdc++.h>

using namespace std;

int N, A, B;
int _move[300];
int reach[300];
queue<int> q;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    while(true)
    {
        cin >> N;
        if (N == 0) break;

        cin >> A >> B;

        for(int i = 1; i <= N; i++)
        {
            cin >> _move[i];
            reach[i] = -1;
        }

        reach[A] = 0;
        while(!q.empty()) q.pop();
        q.emplace(A);

        while (!q.empty())
        {
            int t = q.front();
            if (t + _move[t] <= N && reach[t + _move[t]] == -1)
            {
                reach[t + _move[t]] = reach[t] + 1;
                q.emplace(t + _move[t]);
            }
            if (t - _move[t] > 0 && reach[t - _move[t]] == -1)
            {
                reach[t - _move[t]] = reach[t] + 1;
                q.emplace(t - _move[t]);
            }

            if (reach[B] != -1) break;

            q.pop();
        }

        cout << reach[B] << '\n';
    }

    return 0;
}