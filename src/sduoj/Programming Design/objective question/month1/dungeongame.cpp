#include<iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n, a, b, c;
    cin >> n;

    for(;n--;)
    {
        cin >> a >> b >> c;
        if ((a + b + c) % 9 == 0 && (a + b + c) / 9 <= min(a, min(b, c))) cout << "YES" << '\n';
        else cout << "NO" << '\n';
    }

    return 0;
}