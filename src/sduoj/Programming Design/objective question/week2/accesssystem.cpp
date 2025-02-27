#include<bits/stdc++.h>

using namespace std;

int student[1500];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for(;n--;)
    {
        int id;
        cin >> id;
        cout << ++student[id] << ' ';
    }
    cout << '\n';

    return 0;
}